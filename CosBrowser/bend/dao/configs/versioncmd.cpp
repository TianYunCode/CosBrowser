#include "versioncmd.h"

/**
 * @brief VersionCmd类的构造函数
 * @param argc 命令行参数的数量
 * @param argv 命令行参数的数组
 *
 * 构造函数会检查命令行参数的数量，如果只有一个参数，则将其按点号分割成多个部分，并存储在m_argv中。
 */
VersionCmd::VersionCmd(int argc, char *argv[])
{
    if (argc == 2)
    {
        QString args = argv[1];
        m_argv = args.split(".");
    }
}

/**
 * @brief 设置版本信息
 *
 * 该方法会检查命令行参数是否有效，如果有效，则将参数分别设置为主版本号、环境、v1、v2和v3。
 * 如果参数无效，则抛出一个包含错误信息的QString异常。
 */
void VersionCmd::setVersion()
{
    if (!isValid())
    {
        throw QString::fromLocal8Bit("命令行格式错误 %1").arg(m_argv.join("."));
    }

    m_major = m_argv[0];
    m_env = m_argv[1];
    m_v1 = m_argv[2].toInt();
    m_v2 = m_argv[3].toInt();
    m_v3 = m_argv[4].toInt();
}

/**
 * @brief 检查命令行参数是否有效
 * @return bool 如果命令行参数的数量为5，则返回true，否则返回false
 */
bool VersionCmd::isValid()
{
    return m_argv.size() == 5;
}
