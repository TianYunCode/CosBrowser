#ifndef DAOLOGININFO_H
#define DAOLOGININFO_H

// 引入 SQLite 数据库操作辅助类头文件
#include "helper/dbsqlite.h"

// 引入数据库模型类头文件
#include "middle/models/dbmodels.h"

// 定义一个名为 DaoLoginInfo 的类
class DaoLoginInfo
{
public:
    // 构造函数
    DaoLoginInfo();

    // 纯虚函数，用于检查指定 secretId 的登录信息是否存在
    virtual bool exists(const QString &secretId) = 0;

    // 纯虚函数，用于插入新的登录信息
    virtual void insert(const LoginInfo &info) = 0;

    // 纯虚函数，用于更新登录信息
    virtual void update(const LoginInfo &info) = 0;

    // 纯虚函数，用于删除指定 secretId 的登录信息
    virtual void remove(const QString &secretId) = 0;

    // 纯虚函数，用于选择所有登录信息
    virtual QList<LoginInfo> select() = 0;

    // 纯虚函数，用于连接数据库
    virtual void connect() = 0;

    // 纯虚函数，用于创建登录信息表
    virtual void createTable() = 0;
};

#endif // DAOLOGININFO_H
