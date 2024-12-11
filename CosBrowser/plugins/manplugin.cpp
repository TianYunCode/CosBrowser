#include "manplugin.h"
#include "config/globals.h"
#include "middle/manglobal.h"
#include "bend/dao/clouds/daocloudsmock.h"
#include "bend/dao/configs/versioncmd.h"
#include "bend/dao/configs/versionjson.h"
#include "bend/dao/logs/loggerqdebug.h"
#include "bend/dao/clouds/daocloudscos.h"

using namespace GLOBAL;

// ManPlugin 类的构造函数
ManPlugin::ManPlugin(QObject *parent) : QObject(parent)
{
    // 构造函数初始化代码
}

// ManPlugin 类的析构函数
ManPlugin::~ManPlugin()
{
    // 删除云存储对象
    delete m_clouds;
    // 删除版本信息对象
    delete m_version;
    // 输出调试信息，表示 ManPlugin 对象已被删除
    qDebug("delete ManPlugins ");
}

// 安装插件
void ManPlugin::installPlugins(int argc, char *argv[])
{
    // 创建 VersionCmd 对象来处理命令行参数
    VersionCmd version(argc, argv);

    // 检查命令行参数是否有效
    if (version.isValid())
    {
        // 如果命令行参数有效，使用命令行参数创建 VersionCmd 对象
        m_version = new VersionCmd(argc, argv);
    }
    else
    {
        // 如果命令行参数无效，使用配置文件中的配置信息创建 VersionJson 对象
        m_version = new VersionJson(VERSION::JSON_PATH);
    }

    // 设置版本信息
    m_version->setVersion();

    // 安装日志插件，使用 LoggerQDebug 作为日志记录器
    mLogIns->setLogger(new LoggerQDebug());

    // 根据版本主版本号选择云存储插件
    if (m_version->major() == VERSION::MAJOR_BUSINESS)
    {
        // 如果主版本号为业务版本，使用 DaoCloudsCos 作为云存储插件
        m_clouds = new DaoCloudsCos();
    }
    else
    {
        // 否则使用 DaoCloudsMock 作为云存储插件，并加载测试配置文件
        m_clouds = new DaoCloudsMock(":/static/testing/custom.json");
    }
}

// 获取云存储插件对象
DaoClouds *ManPlugin::clouds() const
{
    return m_clouds;
}
