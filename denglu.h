#ifndef DENGLU_H
#define DENGLU_H

#include <QDialog>

namespace Ui {
class denglu;
}

class denglu : public QDialog
{
    Q_OBJECT

public:
    explicit denglu(QWidget *parent = 0);
    ~denglu();

private slots:
    void on_queren_clicked();

private:
    Ui::denglu *ui;
};

#endif // DENGLU_H
