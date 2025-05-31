#ifndef JIEZHANG_H
#define JIEZHANG_H

#include <QDialog>

namespace Ui {
class jiezhang;
}

class jiezhang : public QDialog
{
    Q_OBJECT

public:
    explicit jiezhang(QWidget *parent = 0);
    ~jiezhang();

private slots:
    void on_jiesuan_clicked();

    void on_quxiao_clicked();

private:
    Ui::jiezhang *ui;
};

#endif // JIEZHANG_H
