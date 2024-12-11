#include <QApplication>

#include "manglobal.h"
#include "bend/gateway.h"
#include "middle/manmodels.h"
#include "middle/signals/mansignals.h"
#include "plugins/manplugin.h"
#include "bend/man/mancloud.h"
#include "bend/man/mandb.h"

// 使用 Q_GLOBAL_STATIC 创建一个全局静态实例 ins，类型为 ManGlobal
Q_GLOBAL_STATIC(ManGlobal, ins)

// ManGlobal 类的构造函数
ManGlobal::ManGlobal(QObject *parent) : QObject(parent)
{
    // 初始化日志代理对象
    mLog = new LoggerProxy(this);

    // 初始化云服务对象
    mCloud = new ManCloud(this);

    // 初始化数据库对象
    mDb = new ManDB(this);

    // 初始化信号处理对象
    mSignal = new ManSignals(this);

    // 初始化插件管理对象
    mPlugin = new ManPlugin(this);

    // 初始化网关对象
    mGate = new GateWay(this);

    // 注意：mModels 的初始化被注释掉了，可能需要在 init 函数中初始化
    // mModels = new ManModels(this);
}

// ManGlobal 类的析构函数
ManGlobal::~ManGlobal()
{
    // 输出调试信息，表示 ManGlobal 对象即将被删除
    qDebug("delete ManGlobal");
}

// 获取 ManGlobal 的单例实例
ManGlobal *ManGlobal::instance()
{
    return ins();
}

// 初始化函数，用于设置应用程序的各种组件
void ManGlobal::init(int argc, char *argv[])
{
    // 初始化模型对象
    mModels = new ManModels(this);

    // 创建日志目录
    FileHelper::mkPath(GLOBAL::PATH::LOG_DIR);

    // 创建临时目录
    FileHelper::mkPath(GLOBAL::PATH::TMP);

    // 安装插件
    mPlugin->installPlugins(argc, argv);

    // 读取并设置应用程序的样式表
    QString qssStr = FileHelper::readAllTxt(":/static/qss/default.qss");
    qApp->setStyleSheet(qssStr);

    // 初始化数据库
    mDb->init();
}
