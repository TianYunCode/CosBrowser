#ifndef VERSIONCMD_H
#define VERSIONCMD_H

// 引入 QStringList 头文件，用于处理字符串列表
#include <QStringList>

// 引入自定义的 Version 类头文件
#include "version.h"

// 定义一个名为 VersionCmd 的类，继承自 Version 类
class VersionCmd : public Version
{
public:
    // 构造函数，接受命令行参数的数量和参数数组
    VersionCmd(int argc, char *argv[]);

    // 实现基类中的纯虚函数，用于设置版本信息
    void setVersion();

    // 检查版本信息是否有效
    bool isValid();

private:
    // 存储命令行参数的字符串列表
    QStringList m_argv;
};

#endif // VERSIONCMD_H
