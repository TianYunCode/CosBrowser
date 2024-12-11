#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// 包含QString和QMap头文件，用于字符串和映射操作
#include <QString>
#include <QMap>

// 定义一个类型别名ErrorMap，表示一个键值对为QString的QMap
typedef QMap<QString, QString> ErrorMap;

// 定义一个基类异常类BaseException
class BaseException
{
public:
    // 构造函数，接受错误码和错误信息作为参数
    BaseException(const QString &code, const QString &msg);

    // 静态方法，用于解析错误码CSV文件并返回一个ErrorMap
    static ErrorMap parseErrorCode(const QString &csvPath);

    // 静态方法，用于生成错误码头文件
    static void generateErrorCodeHFile(const QString &csvPath, const QString &targetPath);

    // 获取错误信息的成员函数
    QString msg() const;

    // 获取错误码的成员函数
    QString code() const;

private:
    // 错误码成员变量
    QString m_code;

    // 错误信息成员变量
    QString m_msg;
};

#endif // EXCEPTIONS_H
