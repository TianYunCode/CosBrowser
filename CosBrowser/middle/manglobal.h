#ifndef MANGLOBAL_H
#define MANGLOBAL_H

// 包含必要的Qt头文件
#include <QObject>

// 包含自定义的配置头文件
#include "config/loggerproxy.h"
#include "config/errorcode.h"
#include "config/exceptions.h"

// 定义一些宏，用于简化日志记录
#define MG ManGlobal::instance()  // 获取ManGlobal单例实例
#define mLogIns MG->mLog  // 获取LoggerProxy实例
#define mTotle mLogIns->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).total  // 重置日志并获取总记录数
#define mDebug mLogIns->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug  // 重置日志并记录调试信息
#define mInfo mLogIns->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).info  // 重置日志并记录信息
#define mWarning mLogIns->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).warning  // 重置日志并记录警告
#define mError mLogIns->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).error  // 重置日志并记录错误
#define mFatal mLogIns->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).fatal  // 重置日志并记录致命错误

// 声明其他单例类的头文件，但不包含它们
// 具体哪个类引用，则哪个类再包含
// 使用对象树所属关系系统进行内存释放
class ManCloud;
class ManDB;
class ManPlugin;
class GateWay;
class ManSignals;
class LoggerProxy;
class ManModels;

/**
 * @brief ManGlobal类，继承自QObject，用于管理全局单例对象
 */
class ManGlobal : public QObject
{
    Q_OBJECT  // 使用Q_OBJECT宏，启用Qt的元对象系统

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针，默认为nullptr
     */
    explicit ManGlobal(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~ManGlobal();

    /**
     * @brief 获取ManGlobal单例实例
     * @return ManGlobal单例实例指针
     */
    static ManGlobal *instance();

    /**
     * @brief 初始化函数
     * @param argc 命令行参数数量
     * @param argv 命令行参数数组
     */
    void init(int argc, char *argv[]);

public:
    LoggerProxy *mLog = nullptr;  // 日志代理实例
    ManCloud *mCloud = nullptr;  // 云服务实例
    ManDB *mDb = nullptr;  // 数据库实例
    ManPlugin *mPlugin = nullptr;  // 插件实例
    GateWay *mGate = nullptr;  // 网关实例
    ManSignals *mSignal = nullptr;  // 信号管理实例
    ManModels *mModels = nullptr;  // 模型管理实例
};

#endif // MANGLOBAL_H
