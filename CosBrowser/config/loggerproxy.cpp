#include "qthread.h"

#include "loggerproxy.h"
#include "middle/manglobal.h"

/**
 * @brief 基础日志类，派生出该类来实现具体的日志记录
 */
LoggerProxy::LoggerProxy(QObject *parent) : QObject{parent}
{
    // 构造函数，初始化父对象
}

/**
 * @brief 析构函数
 *
 * 在析构函数中，删除m_logger对象，并输出调试信息。
 */
LoggerProxy::~LoggerProxy()
{
    if (m_logger)
    {
        delete m_logger;
        m_logger = nullptr;
    }

    qDebug("delete LoggerProxy ");
}

/**
 * @brief 重置日志记录的位置信息
 *
 * 该函数用于重置日志记录的文件名、行号和函数名。
 *
 * @param file 文件名
 * @param line 行号
 * @param func 函数名
 * @return 返回当前LoggerProxy对象的引用
 */
const LoggerProxy &LoggerProxy::reset(const QString &file, int line, const QString &func)
{
    m_file = file;
    m_line = line;
    m_func = func;
    return *this;
}

/**
 * @brief 记录总日志
 *
 * 该函数用于记录总日志信息。
 *
 * @param var 日志内容
 * @param up 是否向上传递日志信息
 */
void LoggerProxy::total(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::TOTAL, var, up);
}

/**
 * @brief 记录调试日志
 *
 * 该函数用于记录调试日志信息。
 *
 * @param var 日志内容
 * @param up 是否向上传递日志信息
 */
void LoggerProxy::debug(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::DEBUG, var, up);
}

/**
 * @brief 记录信息日志
 *
 * 该函数用于记录信息日志信息。
 *
 * @param var 日志内容
 * @param up 是否向上传递日志信息
 */
void LoggerProxy::info(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::INFO, var, up);
}

/**
 * @brief 记录警告日志
 *
 * 该函数用于记录警告日志信息。
 *
 * @param var 日志内容
 * @param up 是否向上传递日志信息
 */
void LoggerProxy::warning(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::WARNING, var, up);
}

/**
 * @brief 记录错误日志
 *
 * 该函数用于记录错误日志信息。
 *
 * @param var 日志内容
 * @param up 是否向上传递日志信息
 */
void LoggerProxy::error(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::ERROR, var, up);
}

/**
 * @brief 记录致命错误日志
 *
 * 该函数用于记录致命错误日志信息。
 *
 * @param var 日志内容
 * @param up 是否向上传递日志信息
 */
void LoggerProxy::fatal(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::FATAL, var, up);
}

/**
 * @brief 执行日志记录的函数
 *
 * 该函数用于根据日志级别记录日志信息。
 *
 * @param level 日志级别
 * @param var 日志内容
 * @param up 是否向上传递日志信息
 */
void LoggerProxy::doLog(GLOBAL::LOG_LEVEL level, const QVariant &var, bool up) const
{
    if (!m_logger)
    {
        return;
    }

    // 如果日志级别大于等于当前设置的日志级别，则记录日志
    if (level >= m_level)
    {
        emit sigLog(m_file, m_line, m_func, QThread::currentThreadId(), level, var, up);
    }
}

/**
 * @brief 设置日志记录器
 *
 * 该函数用于设置具体的日志记录器，并连接信号和槽。
 *
 * @param newLogger 新的日志记录器
 */
void LoggerProxy::setLogger(BasicLogger *newLogger)
{
    if (!m_logger)
    {
        m_logger = newLogger;
        connect(this, &LoggerProxy::sigLog, m_logger, &BasicLogger::onLog);
    }
}

/**
 * @brief 设置日志级别
 *
 * 该函数用于设置日志记录的级别。
 *
 * @param newLevel 新的日志级别
 */
void LoggerProxy::setLevel(GLOBAL::LOG_LEVEL newLevel)
{
    m_level = newLevel;
}
