#ifndef CHAXUN_H
#define CHAXUN_H

#include <QDialog>

namespace Ui {
class chaxun;
}

class chaxun : public QDialog
{
    Q_OBJECT

public:
    explicit chaxun(QWidget *parent = 0);
    ~chaxun();

private slots:
    void on_chaxun_2_clicked();

    void on_fanhui_clicked();

    void on_chongzhi_clicked();

private:
    Ui::chaxun *ui;
};

#endif // CHAXUN_H
