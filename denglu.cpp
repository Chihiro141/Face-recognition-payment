#include "denglu.h"
#include "ui_denglu.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QVariant>
#include "jiezhang.h"

denglu::denglu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::denglu)
{
    ui->setupUi(this);
}

denglu::~denglu()
{
    delete ui;
}

void denglu::on_queren_clicked()
{

    QString password = ui->password->text();
    QString name = ui->name->text();
    QSqlQuery query;
    query.prepare("select * from user where name = ? and password = ?");
    query.bindValue(0, name);
    query.bindValue(1, password);
    query.exec();
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
