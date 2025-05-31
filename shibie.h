#ifndef SHIBIE_H
#define SHIBIE_H
#include <QDialog>
#include <QMainWindow>
#include <opencv.hpp>
#include <vector>
#include <face.hpp>
#include <vector>

using namespace cv;
using namespace std;
using namespace cv::face;
namespace Ui {
class shibie;
}

class shibie : public QDialog
{
    Q_OBJECT

public:
    explicit shibie(QWidget *parent = 0);
    ~shibie();


private:
    void timerEvent(QTimerEvent* e);
    void showImage();//显示一帧图像
    void findFace();//级联分类器查找人脸
    void initRecognizer();
    void check();
private:
    VideoCapture vc;//用来截取视频图像的对象
    Mat frame;//存放一帧视频
    CascadeClassifier cc;
    vector<Rect> faces;//找到的人脸
    Ptr<FaceRecognizer> recognizer;
    Ui::shibie *ui;
    int timerId;
};

#endif // SHIBIE_H
