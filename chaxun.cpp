#include "chaxun.h"
#include "ui_chaxun.h"
#include "mainwindow.h"
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
chaxun::chaxun(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chaxun)
{
    ui->setupUi(this);
}

chaxun::~chaxun()
{
    delete ui;
}

void chaxun::on_chaxun_2_clicked()
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

void chaxun::on_fanhui_clicked()
{
    MainWindow* mw = new MainWindow;
    mw->show();
    close();
}

void chaxun::on_chongzhi_clicked()
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
        // 获取当前用户在数据库中的余额
              int currentBalance = query.record().value("yue").toInt();
              // 获取界面上显示的充值金额，将其文本转换为整数
              int rechargeAmount = ui->jine->text().toInt();
              // 计算充值后的余额
              int newBalance = currentBalance + rechargeAmount;

              // 更新数据库中该用户的余额信息
              query.prepare("update user set yue =? where name =? and password =?");
              query.bindValue(0, newBalance);
              query.bindValue(1, name);
              query.bindValue(2, password);
              if (query.exec()) {
                  ui->xianshi->setText(QString("The recharge is successful, and the current balance is%1").arg(newBalance));
              } else {
                  ui->xianshi->setText("Failed to recharge");
              }



    }
    else
    {
    ui->xianshi->setText("Fail，The account password is incorrect and cannot be queried");
    }
}
