#ifndef MANDB_H
#define MANDB_H

// 引入 QObject 头文件
#include <QObject>

// 引入 dbsqlite.h 和 daologininfosqlite.h 头文件
#include "helper/dbsqlite.h"
#include "bend/dao/dbs/daologininfosqlite.h"

// 定义一个名为 ManDB 的类，继承自 QObject
class ManDB : public QObject
{
    // 使用 Q_OBJECT 宏，启用 Qt 的元对象系统
    Q_OBJECT

public:
    // 构造函数，使用 explicit 关键字防止隐式转换，parent 参数用于指定父对象
    explicit ManDB(QObject *parent = nullptr);

    // 析构函数
    ~ManDB();

    // 初始化函数
    void init();

    // 保存登录信息
    void saveLoginInfo(const QString &name, const QString &id, const QString &key, const QString &remark);

    // 删除登录信息
    void removeLoginInfo(const QString &id);

    // 根据 secretId 查找登录信息的索引
    int indexOfLoginInfo(const QString &secretId);

    // 获取所有登录名称的列表
    QStringList loginNameList();

    // 根据名称获取登录信息
    LoginInfo loginInfoByName(const QString &name);

private:
    // 数据访问对象，用于操作登录信息
    DaoLoginInfoSqlite m_daoLoginInfo;

    // 登录信息列表
    QList<LoginInfo> m_loginInfoList;
};

#endif // MANDB_H
