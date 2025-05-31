#include "shibie.h"
#include "ui_shibie.h"
#include <QFile>
#include <QMessageBox>
#include "UserDao.h"
#include "moneydata.h"
#include "jiezhang.h"
#include "zhuce.h"
#include "chaxun.h"
#define FACE_MODEL "face_model.xml"
shibie::shibie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shibie)
{
    ui->setupUi(this);
    timerId = startTimer(1000);
    vc.open(0);//打开电脑的第一个摄像头
    initRecognizer();
}

shibie::~shibie()
{
    delete ui;
}
//打开摄像头并将照片转换为灰度图
void shibie::timerEvent(QTimerEvent *e)
{
    vc>>frame;//读取一帧视频放到frame对象
    flip(frame, frame, 1);//翻转图片
    findFace();
    check();
    showImage();
}

void shibie::showImage()
{
    Mat rgb;
    cvtColor(frame, rgb, COLOR_BGR2RGB);
    QImage img(rgb.data, rgb.cols, rgb.rows, rgb.cols*rgb.channels(), QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(QSize(rgb.cols, rgb.rows));
}

void shibie::findFace()
{
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    cc.detectMultiScale(gray, faces, 1.1, 5, 0, Size(150, 150), Size(200, 200));
    for(int i = 0;i < faces.size();i++)
    {
        rectangle(frame, faces[i], Scalar(123, 112, 221), 2);
    }
}
//人脸识别
void shibie::initRecognizer()
{
    QFile file(FACE_MODEL);//人脸模型
    if(file.exists())
    {
        recognizer = FaceRecognizer::load<LBPHFaceRecognizer>(FACE_MODEL);
    }
    else
    {
        recognizer = LBPHFaceRecognizer::create();
    }
    recognizer->setThreshold(100);//设置阈值
    cc.load("haarcascade_frontalface_alt2.xml");//加载级联分类器
}



//结账
void shibie::check()
{
    if(faces.size() == 0)
    {
        return;
    }
    Mat face = frame(faces[0]);
    cvtColor(face, face, COLOR_BGR2GRAY);
    cv::resize(face, face, Size(80, 80));

    int label;
    double cf;
    if(recognizer->empty())//人脸识别器没有模型，不可以识别
    {
        QMessageBox::warning(this, "警告", "还没有机器学习");
        return;
    }
    recognizer->predict(face, label, cf);
    if(label != -1)//-1表示识别失败
    {
        UserDao* userDao = UserDao::getInstance();
                UserEntity user;
                user.id = label;
                // 增加判断selectUser操作是否成功
                if (userDao->selectUser(user)) {
                    int payAmount = MoneyData::getInstace()->getPay();
                    int balance = user.getYue();
                    if (payAmount <= balance) {
                        int remainingBalance = balance - payAmount;
                        QMessageBox::information(this, "Successful", QString("This consumption:%1,balbnce:%2").arg(payAmount).arg(remainingBalance));
                        user.yue = remainingBalance;
                        killTimer(timerId);
                        chaxun* cx = new chaxun;
                        cx->show();
                        close();
                        if (!userDao->updateUser(user)) {
                            QMessageBox::warning(this, "ERROR", "Updating the balance to the database failed");
                            killTimer(timerId);

                        }
                    }
                    else {
                        QMessageBox::warning(this, "Pay Fail", "The balance is insufficient");
                        jiezhang* jz = new jiezhang;
                                         jz->show();
                                         close();
                        killTimer(timerId);
                    }
                }
                else {
                    QMessageBox::warning(this, "ERROR", "Failed to obtain user information, check whether the user ID is correct or contact the administrator");
                     killTimer(timerId);
                }
       }

}

