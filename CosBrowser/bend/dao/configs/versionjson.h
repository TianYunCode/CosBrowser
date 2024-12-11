#ifndef VERSIONJSON_H
#define VERSIONJSON_H

// 引入自定义的 Version 类头文件
#include "version.h"

// 定义一个名为 VersionJson 的类，继承自 Version 类
class VersionJson : public Version
{
public:
    // 构造函数，接受一个表示 JSON 文件路径的字符串
    VersionJson(const QString &path);

    // 实现基类中的纯虚函数，用于设置版本信息
    void setVersion();

private:
    // 存储 JSON 文件路径的字符串
    QString m_path;
};

#endif // VERSIONJSON_H
