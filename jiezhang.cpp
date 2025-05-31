#include "jiezhang.h"
#include "ui_jiezhang.h"
#include "shibie.h"
#include "mainwindow.h"
#include "moneydata.h"
jiezhang::jiezhang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jiezhang)
{
    ui->setupUi(this);

    //MoneyData::getInstace()->getPay();//获取支付金额
}

jiezhang::~jiezhang()
{
    delete ui;
}

void jiezhang::on_jiesuan_clicked()
{
    MoneyData::getInstace()->setPay(ui->label_2->text().toInt());//设置支付金额
    shibie* sbjs = new shibie;
                     sbjs->show();
                     close();
}

void jiezhang::on_quxiao_clicked()
{
    MainWindow* mw = new MainWindow;
    mw->show();
    close();
}

