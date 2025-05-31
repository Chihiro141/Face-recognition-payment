#include "UserDao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

UserDao* UserDao::instance = 0;

UserDao *UserDao::getInstance()
{
    if(instance == 0)
    {
        instance = new UserDao;
    }
    return instance;
}

bool UserDao::insertUser(UserEntity &payname)
{
    //插入数据
    QSqlQuery query;
    query.prepare("insert into user(name,password,yue) values(?,?,?)");
    query.bindValue(0, payname.name);
    query.bindValue(1, payname.password);
    query.bindValue(2, payname.yue);
    bool ok = query.exec();
    //查询这个人的id
    query.exec("SELECT LAST_INSERT_ROWID()");//获得最后一次插入数据的主键
    if(query.next())
    {
        payname.id = query.record().value(0).toInt();
    }
    return ok;
}

bool UserDao::selectUser(UserEntity &e)
{
    QSqlQuery query;
    query.prepare("select * from user where id = ?");
    query.bindValue(0, e.id);
    bool ok = query.exec();

    if(query.next())
    {
        e.yue = query.record().value("yue").toInt();
    }
    return ok;
}

UserDao::UserDao()
{
    db = QSqlDatabase::addDatabase("QSQLITE");//加载sqlite数据库驱动，返回数据库对象
    /*
    sqlite数据库在硬盘上就是一个.db文件，所以数据库的名字对于sqlite数据库而言，就是一个文件名
    */
    db.setDatabaseName("user.db");
    db.open();//打开数据库

    QSqlQuery query;
    //在user表不存在的情况下创建一个user表，字段分别是userid password nickname headid
    query.exec("create table if not exists user(\
                      id integer primary key autoincrement,\
                      name char(20),\
                      password char(20),\
                      yue integer\
                      )");
}
bool UserDao::updateUser(UserEntity &user)
{
    QSqlQuery query;
    query.prepare("update user set yue =? where id =?");
    query.bindValue(0, user.yue);
    query.bindValue(1, user.id);
    return query.exec();
}
UserDao::UserDao(const UserDao &other)
{

}

UserDao::~UserDao()
{
    db.close();//关闭数据库
}

