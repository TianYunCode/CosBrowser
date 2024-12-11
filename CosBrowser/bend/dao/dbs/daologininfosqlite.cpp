#include "daologininfosqlite.h"
#include "config/globals.h"

/**
 * @brief DaoLoginInfoSqlite类的构造函数
 *
 * 该构造函数用于初始化DaoLoginInfoSqlite对象。由于构造函数中没有显式的初始化操作，因此它只是一个默认构造函数。
 */
DaoLoginInfoSqlite::DaoLoginInfoSqlite()
{
    // 构造函数体为空，没有显式的初始化操作
}

/**
 * @brief 检查指定secretId的记录是否存在
 *
 * @param secretId 要检查的secretId
 * @return 如果记录存在则返回true，否则返回false
 */
bool DaoLoginInfoSqlite::exists(const QString &secretId)
{
    // 构建SQL查询语句，查询指定secretId的记录是否存在
    QString sql = QString("select id from %1 where secret_id = '%2';").arg(GLOBAL::TABLES::LOGIN_INFO, secretId);
    // 执行查询并返回结果
    return m_db.exists(sql);
}

/**
 * @brief 插入一条新的LoginInfo记录
 *
 * @param info 要插入的LoginInfo对象
 */
void DaoLoginInfoSqlite::insert(const LoginInfo &info)
{
    // 构建SQL插入语句，插入新的LoginInfo记录
    QString sql = QString("insert into %1 (name, secret_id, secret_key, remark, timestamp) values (?, ?, ?, ?, ?)").arg(GLOBAL::TABLES::LOGIN_INFO);
    // 构建参数列表
    QVariantList varList;
    varList << info.name << info.secret_id << info.secret_key << info.remark << info.timestamp;
    // 执行插入操作
    m_db.exec(sql, varList);
}

/**
 * @brief 更新指定secretId的LoginInfo记录
 *
 * @param info 包含更新信息的LoginInfo对象
 */
void DaoLoginInfoSqlite::update(const LoginInfo &info)
{
    // 构建SQL更新语句，更新指定secretId的记录
    QString sql = QString("update %1 set name=?, secret_key=?, remark=?, timestamp=? where secret_id = ?").arg(GLOBAL::TABLES::LOGIN_INFO);
    // 构建参数列表
    QVariantList varList;
    varList << info.name << info.secret_key << info.remark << info.timestamp << info.secret_id;
    // 执行更新操作
    m_db.exec(sql, varList);
}

/**
 * @brief 删除指定secretId的LoginInfo记录
 *
 * @param secretId 要删除的记录的secretId
 */
void DaoLoginInfoSqlite::remove(const QString &secretId)
{
    // 构建SQL删除语句，删除指定secretId的记录
    QString sql = QString("delete from %1 where secret_id = ?;").arg(GLOBAL::TABLES::LOGIN_INFO);
    // 构建参数列表
    QVariantList varList;
    varList << secretId;
    // 执行删除操作
    m_db.exec(sql, varList);
}

/**
 * @brief 查询所有LoginInfo记录
 *
 * @return 包含所有LoginInfo记录的列表
 */
QList<LoginInfo> DaoLoginInfoSqlite::select()
{
    // 构建SQL查询语句，查询所有记录并按timestamp降序排列
    QString sql = QString("select name, secret_id, secret_key, remark from %1 order by timestamp desc;").arg(GLOBAL::TABLES::LOGIN_INFO);

    QList<LoginInfo> retList;
    // 执行查询操作，获取记录列表
    QList<RECORD> recordList = m_db.select(sql);
    // 遍历记录列表，将每条记录转换为LoginInfo对象并添加到返回列表中
    for (const auto &record : recordList)
    {
        LoginInfo info;
        info.name = record["name"].toString();
        info.secret_id = record["secret_id"].toString();
        info.secret_key = record["secret_key"].toString();
        info.remark = record["remark"].toString();

        retList.append(info);
    }

    return retList;
}

/**
 * @brief 连接到SQLite数据库
 */
void DaoLoginInfoSqlite::connect()
{
    // 连接到指定的SQLite数据库
    m_db.connect(GLOBAL::SQLITE::NAME);
}

/**
 * @brief 创建LoginInfo表
 */
void DaoLoginInfoSqlite::createTable()
{
    // 从文件中读取创建表的SQL语句
    QString sql = FileHelper::readAllTxt(GLOBAL::SQL::LOGIN_INFO_TABLE);
    // 执行创建表的操作
    m_db.exec(sql);
}
