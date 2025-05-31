#include "zhuce.h"
#include "ui_zhuce.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QVariant>
#include <QFile>
#include <QMessageBox>
#include "userdao.h"
#include "jiezhang.h"
#define FACE_MODEL "face_model.xml"
zhuce::zhuce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);
    startTimer(50);
    vc.open(0);//打开电脑的第一个摄像头
    initRecognizer();
}
void zhuce::timerEvent(QTimerEvent *e)
{
    vc>>frame;//读取一帧视频放到frame对象
    flip(frame, frame, 1);//翻转图片
    findFace();
    showImage();
}

void zhuce::showImage()
{
    Mat rgb;
    cvtColor(frame, rgb, COLOR_BGR2RGB);
    QImage img(rgb.data, rgb.cols, rgb.rows, rgb.cols*rgb.channels(), QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(QSize(rgb.cols, rgb.rows));
}

void zhuce::findFace()
{
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    cc.detectMultiScale(gray, faces, 1.1, 5, 0, Size(100, 100), Size(300, 300));
    for(int i = 0;i < faces.size();i++)
    {
        rectangle(frame, faces[i], Scalar(123, 112, 221), 2);
    }
}

zhuce::~zhuce()
{
    delete ui;
}

void zhuce::initRecognizer()
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

void zhuce::on_queren_clicked()
{
    if(faces.size() == 0)
    {
        QMessageBox::warning(this, "警告", "请正视摄像头");
        return;
    }
    Mat face = frame(faces[0]);
    cvtColor(face, face, COLOR_BGR2GRAY);
    cv::resize(face, face, Size(80, 80));

    QString name = ui->name->text();
    QString password = ui->password->text();
    int yue = ui->yue->text().toInt();
    if(name.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请输入名字");
        return;
    }

    //插入数据库
    UserEntity e;
    e.name = name;
    e.password = password;
    e.yue = yue;
    UserDao::getInstance()->insertUser(e);
    vector<Mat> studyFaces;
    vector<int> studyLabel;
    studyFaces.push_back(face);
    studyLabel.push_back(e.id);
    recognizer->update(studyFaces, studyLabel);
    recognizer->save(FACE_MODEL);
    QMessageBox::information(this,"Tips","Registration is successful");

}

void zhuce::on_fanhui_clicked()
{
    MainWindow* mw = new MainWindow;
    mw->show();
    close();
}

void zhuce::on_denglu_clicked()
{
    QString password = ui->password->text();
    QString name = ui->name->text();
    QSqlQuery query;
    query.prepare("select * from user where name = ? and password = ?");
    query.bindValue(0, name);
    query.bindValue(1, password);
    bool ok = query.exec();
    qDebug()<<ok;
    if(query.next())
    {
       jiezhang* jz = new jiezhang;
                        jz->show();
                        close();

    }
    else
    {
    ui->xianshi->setText("fail");
    }
}

void zhuce::on_chaxun_clicked()
{
    QString password = ui->password->text();
    QString name = ui->name->text();
    QSqlQuery query;
    query.prepare("select * from user where name = ? and password = ?");
    query.bindValue(0, name);
    query.bindValue(1, password);
    bool ok = query.exec();
    qDebug()<<ok;
    if(query.next())
    {
        int balance = query.record().value("yue").toInt();// 将余额信息显示在控件上，也可以按照需求格式化显示内容，比如添加提示文字等
        ui->yue_2->setText(QString("%1").arg(balance));


    }
    else
    {
    ui->xianshi->setText("Fail，The account password is incorrect and cannot be queried");
    }
}
