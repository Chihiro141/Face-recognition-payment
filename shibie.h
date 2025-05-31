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
    void showImage();//��ʾһ֡ͼ��
    void findFace();//������������������
    void initRecognizer();
    void check();
private:
    VideoCapture vc;//������ȡ��Ƶͼ��Ķ���
    Mat frame;//���һ֡��Ƶ
    CascadeClassifier cc;
    vector<Rect> faces;//�ҵ�������
    Ptr<FaceRecognizer> recognizer;
    Ui::shibie *ui;
    int timerId;
};

#endif // SHIBIE_H
