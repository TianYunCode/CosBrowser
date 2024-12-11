#ifndef DAOLOGININFOSQLITE_H
#define DAOLOGININFOSQLITE_H

// 引入 DaoLoginInfo 基类头文件
#include "daologininfo.h"

// 定义一个名为 DaoLoginInfoSqlite 的类，继承自 DaoLoginInfo
class DaoLoginInfoSqlite : public DaoLoginInfo
{
public:
    // 构造函数
    DaoLoginInfoSqlite();

    // 实现 exists 方法，用于检查指定 secretId 的登录信息是否存在
    bool exists(const QString &secretId) override;

    // 实现 insert 方法，用于插入新的登录信息
    void insert(const LoginInfo &info) override;

    // 实现 update 方法，用于更新登录信息
    void update(const LoginInfo &info) override;

    // 实现 remove 方法，用于删除指定 secretId 的登录信息
    void remove(const QString &secretId) override;

    // 实现 select 方法，用于选择所有登录信息
    QList<LoginInfo> select() override;

    // 实现 connect 方法，用于连接数据库
    void connect() override;

    // 实现 createTable 方法，用于创建登录信息表
    void createTable() override;

private:
    // 私有成员变量，用于操作 SQLite 数据库
    DbSqlite m_db;
};

#endif // DAOLOGININFOSQLITE_H
