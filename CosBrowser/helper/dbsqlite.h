#ifndef DBSQLITE_H
#define DBSQLITE_H

// 包含必要的Qt头文件
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

// 定义一个类型别名，用于表示数据库记录
typedef QMap<QString, QVariant> RECORD;

/**
 * @brief DbSqlite类，用于管理SQLite数据库连接和操作
 */
class DbSqlite
{
public:
    /**
     * @brief 构造函数，初始化DbSqlite对象
     */
    DbSqlite();

    /**
     * @brief 析构函数，释放资源
     */
    ~DbSqlite();

    /**
     * @brief 连接到SQLite数据库
     * @param dbPath 数据库文件的路径
     */
    void connect(const QString &dbPath);

    /**
     * @brief 执行SQL语句
     * @param sql 要执行的SQL语句
     * @return 返回执行结果的QSqlQuery对象
     */
    QSqlQuery exec(const QString &sql);

    /**
     * @brief 执行带参数的SQL语句
     * @param sql 要执行的SQL语句
     * @param variantList SQL语句中的参数列表
     * @return 返回执行结果的QSqlQuery对象
     */
    QSqlQuery exec(const QString &sql, const QVariantList &variantList);

    /**
     * @brief 检查是否存在满足条件的记录
     * @param sql 用于检查的SQL语句
     * @return 如果存在满足条件的记录，返回true；否则返回false
     */
    bool exists(const QString &sql);

    /**
     * @brief 执行SELECT查询，并返回结果列表
     * @param sql 要执行的SELECT语句
     * @return 返回查询结果的记录列表
     */
    QList<RECORD> select(const QString &sql);

private:
    /**
     * @brief 数据库连接对象
     */
    QSqlDatabase m_db;
};

#endif // DBSQLITE_H
