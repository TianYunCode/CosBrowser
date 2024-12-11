#include <QSqlError>
#include <QSqlRecord>
#include "dbsqlite.h"

#include "middle/manglobal.h"

// 构造函数，初始化数据库连接
DbSqlite::DbSqlite()
{
    // 添加一个 SQLite 数据库连接
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

// 析构函数，关闭数据库连接
DbSqlite::~DbSqlite()
{
    // 如果数据库连接已打开，则关闭它
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

// 连接到指定路径的数据库
void DbSqlite::connect(const QString &dbPath)
{
    // 设置数据库名称（即数据库文件的路径）
    m_db.setDatabaseName(dbPath);
    // 尝试打开数据库
    if (!m_db.open())
    {
        // 如果打开失败，抛出异常并包含错误信息
        throw QString::fromLocal8Bit("打开数据库失败：%1 %2").arg(dbPath, m_db.lastError().text());
    }
}

// 执行一条 SQL 语句
QSqlQuery DbSqlite::exec(const QString &sql)
{
    QSqlQuery query;
    // 执行 SQL 语句
    if (!query.exec(sql))
    {
        // 如果执行失败，抛出异常并包含错误信息
        throw QString::fromLocal8Bit("执行sql失败：%1 %2").arg(sql, query.lastError().text());
    }

    // 返回执行后的查询对象
    return query;
}

// 执行一条带有绑定参数的 SQL 语句
QSqlQuery DbSqlite::exec(const QString &sql, const QVariantList &variantList)
{
    QSqlQuery query;
    // 预编译 SQL 语句
    if (!query.prepare(sql))
    {
        // 如果预编译失败，抛出异常并包含错误信息
        throw QString::fromLocal8Bit("预编译sql失败：%1 %2").arg(sql, query.lastError().text());
    }

    // 绑定参数到 SQL 语句
    for (const auto &var : variantList)
    {
        query.addBindValue(var);
    }

    // 执行带有绑定参数的 SQL 语句
    if (!query.exec())
    {
        // 如果执行失败，抛出异常并包含错误信息
        throw QString::fromLocal8Bit("执行sql bindvalue失败：%1 %2").arg(sql, query.lastError().text());
    }

    // 返回执行后的查询对象
    return query;
}

// 检查是否存在满足 SQL 条件的记录
bool DbSqlite::exists(const QString &sql)
{
    // 执行 SQL 查询
    QSqlQuery query = exec(sql);
    // 检查是否有下一条记录，如果有则返回 true，否则返回 false
    return query.next();
}

// 执行 SELECT 语句并返回结果列表
QList<RECORD> DbSqlite::select(const QString &sql)
{
    QList<RECORD> retList;
    // 执行 SQL 查询
    QSqlQuery query = exec(sql);

    // 遍历查询结果集
    while (query.next())
    {
        RECORD ret; // 创建一个记录对象

        QSqlRecord record = query.record(); // 获取当前行的记录
        // 遍历记录中的每个字段
        for (int i = 0; i < record.count(); ++i)
        {
            QString name = record.fieldName(i); // 获取字段名
            QVariant value = record.value(i);   // 获取字段值
            ret[name] = value;                // 将字段名和值存入记录对象
        }

        // 输出调试信息
        mInfo(QString::fromLocal8Bit("查询出结果如下: "));
        mError(ret);
        retList.append(ret); // 将记录对象添加到结果列表中
    }

    // 返回结果列表
    return retList;
}
