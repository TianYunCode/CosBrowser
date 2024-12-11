#ifndef VERSION_H
#define VERSION_H

// 引入 QString 和 QJsonObject 头文件，用于处理字符串和 JSON 对象
#include <QString>
#include <QJsonObject>

// 定义一个名为 Version 的类
class Version
{
public:
    // 构造函数，初始化 Version 对象
    Version();

    // 纯虚函数，用于设置版本信息
    // 子类必须实现此函数
    virtual void setVersion() = 0;

    // 返回版本信息的字符串表示
    QString version();

    // 返回版本号的字符串表示
    QString versionNum();

    // 返回主版本的字符串表示
    // const 修饰符表示此函数不会修改类的成员变量
    QString major() const;

protected:
    // 主版本类型，可以是 "business"（商用版）或 "custom"（个人版）
    QString m_major;

    // 环境类型，可以是 "dev"（开发环境）、"alpha"（测试环境）、"beta"（预发布环境）或 "prod"（生产环境）
    QString m_env;

    // 版本号的三个部分，分别表示主版本号、次版本号和修订版本号
    int m_v1;
    int m_v2;
    int m_v3;
};

#endif // VERSION_H
