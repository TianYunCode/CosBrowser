#include "versionjson.h"
#include "helper/filehelper.h"

/**
 * @brief VersionJson类的构造函数
 * @param path JSON文件的路径
 *
 * 构造函数会初始化VersionJson对象，并将传入的JSON文件路径存储在m_path中。
 */
VersionJson::VersionJson(const QString &path)
{
    m_path = path;
}

/**
 * @brief 设置版本信息
 *
 * 该方法会读取指定路径的JSON文件，并从中提取版本信息，分别设置为主版本号、环境、v1、v2和v3。
 */
void VersionJson::setVersion()
{
    // 使用FileHelper类读取JSON文件，并将其转换为QJsonObject对象
    QJsonObject obj = FileHelper::readAllJson(m_path).toJsonObject();

    // 从JSON对象中提取"version"对象
    obj = obj["version"].toObject();

    // 从"version"对象中提取各个版本信息并设置到成员变量中
    m_major = obj["major"].toString();
    m_env = obj["env"].toString();
    m_v1 = obj["v1"].toInt();
    m_v2 = obj["v2"].toInt();
    m_v3 = obj["v3"].toInt();
}
