#include <QDateTime>

#include "mandb.h"

/**
 * @brief ManDB类的构造函数
 *
 * 该构造函数用于初始化ManDB对象。
 *
 * @param parent 父对象指针，默认为nullptr
 */
ManDB::ManDB(QObject *parent) : QObject{parent}
{
    // 构造函数为空，因为不需要额外的初始化操作
}

/**
 * @brief ManDB类的析构函数
 *
 * 该析构函数用于清理资源，并在控制台输出一条调试信息。
 */
ManDB::~ManDB()
{
    qDebug("delete ManDB ");
}

/**
 * @brief 初始化数据库的函数
 *
 * 该函数用于初始化数据库连接，创建表，并加载登录信息列表。
 */
void ManDB::init()
{
    // 连接数据库
    m_daoLoginInfo.connect();

    // 创建登录信息表
    m_daoLoginInfo.createTable();

    // 从数据库中选择所有登录信息并加载到列表中
    m_loginInfoList = m_daoLoginInfo.select();
}

/**
 * @brief 保存登录信息的函数
 *
 * 该函数用于保存或更新登录信息到数据库。
 *
 * @param name 登录名称
 * @param id 登录ID
 * @param key 登录密钥
 * @param remark 备注信息
 */
void ManDB::saveLoginInfo(const QString &name, const QString &id, const QString &key, const QString &remark)
{
    // 创建一个新的登录信息对象
    LoginInfo info;

    // 如果名称未提供，则使用ID作为名称
    info.name = (name == "" ? id : name);

    // 去除ID和密钥的前后空格
    info.secret_id = id.trimmed();
    info.secret_key = key.trimmed();

    // 去除备注信息的前后空格
    info.remark = remark.trimmed();

    // 设置当前时间戳
    info.timestamp = QDateTime::currentDateTimeUtc().toTime_t();

    // 检查数据库中是否已存在该登录信息
    if (m_daoLoginInfo.exists(info.secret_id))
    {
        // 更新数据库中的登录信息
        m_daoLoginInfo.update(info);

        // 更新内存中的登录信息列表
        m_loginInfoList[indexOfLoginInfo(info.secret_id)] = info;
    }
    else
    {
        // 插入新的登录信息到数据库
        m_daoLoginInfo.insert(info);

        // 将新的登录信息添加到内存中的列表
        m_loginInfoList.append(info);
    }
}

/**
 * @brief 删除登录信息的函数
 *
 * 该函数用于从数据库和内存中删除指定的登录信息。
 *
 * @param id 登录ID
 */
void ManDB::removeLoginInfo(const QString &id)
{
    // 检查数据库中是否存在该登录信息
    if (m_daoLoginInfo.exists(id))
    {
        // 从数据库中删除登录信息
        m_daoLoginInfo.remove(id);

        // 从内存中的列表中删除登录信息
        m_loginInfoList.removeAt(indexOfLoginInfo(id));
    }
}

/**
 * @brief 获取登录信息索引的函数
 *
 * 该函数用于获取指定登录ID在内存列表中的索引。
 *
 * @param secretId 登录ID
 * @return 登录信息在列表中的索引
 * @throws 如果未找到登录信息，则抛出异常
 */
int ManDB::indexOfLoginInfo(const QString &secretId)
{
    // 遍历登录信息列表
    for (int i = 0; i < m_loginInfoList.size(); ++i)
    {
        // 如果找到匹配的登录ID，返回索引
        if (m_loginInfoList[i].secret_id == secretId)
        {
            return i;
        }
    }

    // 如果未找到登录信息，抛出异常
    throw QString::fromLocal8Bit("获取登录信息索引失败 %1").arg(secretId);
}

/**
 * @brief 获取登录名称列表的函数
 *
 * 该函数用于获取所有登录信息的名称列表。
 *
 * @return 登录名称列表
 */
QStringList ManDB::loginNameList()
{
    // 创建一个空的字符串列表
    QStringList words;

    // 遍历登录信息列表，将每个登录信息的名称添加到列表中
    for (int i = 0; i < m_loginInfoList.size(); ++i)
    {
        words.append(m_loginInfoList[i].name);
    }

    // 返回登录名称列表
    return words;
}

/**
 * @brief 通过名称获取登录信息的函数
 *
 * 该函数用于通过登录名称获取对应的登录信息。
 *
 * @param name 登录名称
 * @return 对应的登录信息
 * @throws 如果未找到登录信息，则抛出异常
 */
LoginInfo ManDB::loginInfoByName(const QString &name)
{
    // 遍历登录信息列表
    for (int i = 0; i < m_loginInfoList.size(); ++i)
    {
        // 如果找到匹配的登录名称，返回对应的登录信息
        if (m_loginInfoList[i].name == name)
        {
            return m_loginInfoList[i];
        }
    }

    // 如果未找到登录信息，抛出异常
    throw QString::fromLocal8Bit("通过名称查找登录信息失败 %1").arg(name);
}
