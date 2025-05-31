#ifndef USERDAO_H
#define USERDAO_H

#include <QSqlDatabase>

//这个结构体对应了数据库的一行数据，每个成员对应了数据库的一个字段
struct UserEntity
{
    int id;
    QString name;
    QString password;
    int yue;
    int getYue()
    {
            return yue;
    }
};

class UserDao
{
public:
    static UserDao* getInstance();//创建对象的函数
    bool insertUser(UserEntity &user);//插入数据
    bool selectUser(UserEntity &user);//查询用户
    bool updateUser(UserEntity &user);

private:
    UserDao();
    UserDao(const UserDao& other);
    ~UserDao();

    static UserDao* instance;
    QSqlDatabase db;
};

#endif // USERDAO_H

