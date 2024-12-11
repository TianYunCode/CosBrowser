#include "version.h"

/**
 * @brief Version类的构造函数
 * 初始化Version对象
 */
Version::Version()
{
}

/**
 * @brief 获取完整的版本字符串
 * @return QString 完整的版本字符串，格式为 "主版本号.环境.版本号"
 */
QString Version::version()
{
    return QString("%1.%2.%3").arg(m_major, m_env, versionNum());
}

/**
 * @brief 获取版本号字符串
 * @return QString 版本号字符串，格式为 "v1.v2.v3"
 */
QString Version::versionNum()
{
    return QString("%1.%2.%3").arg(m_v1).arg(m_v2).arg(m_v3);
}

/**
 * @brief 获取主版本号
 * @return QString 主版本号
 */
QString Version::major() const
{
    return m_major;
}
