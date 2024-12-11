#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

// 包含必要的头文件
#include "bend/dao/logs/basiclogger.h"  // 包含基础日志类的头文件
#include "config/globals.h"             // 包含全局配置的头文件

// 定义LoggerProxy类，继承自QObject
class LoggerProxy : public QObject
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    // 构造函数，允许指定父对象
    explicit LoggerProxy(QObject *parent = nullptr);

    // 析构函数
    ~LoggerProxy();

    // 重置日志记录的文件名、行号和函数名
    const LoggerProxy &reset(const QString &file, int line, const QString &func);

    // 记录不同级别的日志信息
    void total(const QVariant &var, bool up = false) const;
    void debug(const QVariant &var, bool up = false) const;
    void info(const QVariant &var, bool up = false) const;
    void warning(const QVariant &var, bool up = false) const;
    void error(const QVariant &var, bool up = true) const;
    void fatal(const QVariant &var, bool up = true) const;

    // 设置日志级别
    void setLevel(GLOBAL::LOG_LEVEL newLevel);

    // 设置日志记录器
    void setLogger(BasicLogger *newLogger);

signals:
    // 日志信号，用于通知外部日志记录
    void sigLog(const QString &file, int line, const QString &func, void *tid, int level, const QVariant &var, bool up) const;

private:
    // 执行日志记录的私有方法
    void doLog(GLOBAL::LOG_LEVEL level, const QVariant &var, bool up) const;

private:
    BasicLogger *m_logger = nullptr;  // 指向基础日志记录器的指针
    GLOBAL::LOG_LEVEL m_level;        // 当前日志级别

    QString m_file;  // 当前日志记录的文件名
    int m_line;      // 当前日志记录的行号
    QString m_func;  // 当前日志记录的函数名
};

#endif // LOGGERPROXY_H
