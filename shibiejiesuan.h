#ifndef SHIBIEJIESUAN_H
#define SHIBIEJIESUAN_H

#include <QDialog>

namespace Ui {
class shibiejiesuan;
}

class shibiejiesuan : public QDialog
{
    Q_OBJECT

public:
    explicit shibiejiesuan(QWidget *parent = 0);
    ~shibiejiesuan();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::shibiejiesuan *ui;
};

#endif // SHIBIEJIESUAN_H
