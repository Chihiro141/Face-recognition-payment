#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "denglu.h"
#include "zhuce.h"
#include "chaxun.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_zhuce_clicked()
{
   zhuce* zc = new zhuce;
   zc->show();
   close();
}

void MainWindow::on_button_clicked()
{
    chaxun* cx = new chaxun;
    cx->show();
    close();
}
