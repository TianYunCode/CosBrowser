#ifndef GLOBALS_H
#define GLOBALS_H

// 包含必要的头文件
#include <QString>
#include <QDir>

// 包含自定义的文件辅助类头文件
#include "helper/filehelper.h"

// 定义全局命名空间GLOBAL
namespace GLOBAL
{
// 定义路径相关的命名空间PATH
namespace PATH
{
// 当前工作目录路径
static const QString WORK = QDir::currentPath();

// 临时文件目录路径，由当前工作目录和"temp"子目录组成
static const QString TMP = FileHelper::joinPath(WORK, "temp");

// 日志目录路径，由系统临时目录和"qos/logs"子目录组成
static const QString LOG_DIR = FileHelper::joinPath(QDir::tempPath(), "qos/logs");

// 错误码CSV文件路径，使用资源文件路径
static const QString ERROR_CODE_PATH = ":/static/docs/errorcode.csv";

// 以下是一些图片资源的路径
static const QString LOGO_PATH = ":/static/imgs/logo.png";
static const QString MAX_PATH = ":/static/imgs/Maximize-1.png";
static const QString MAX_HOVER_PATH = ":/static/imgs/Maximize-2.png";
static const QString NORMAL_PATH = ":/static/imgs/Maximize-3.png";
static const QString NORMAL_HOVER_PATH = ":/static/imgs/Maximize-4.png";
static const QString MIN_PATH = ":/static/imgs/Minimize-1.png";
static const QString MIN_HOVER_PATH = ":/static/imgs/Minimize-2.png";

static const QString QUIT = ":/static/imgs/Quit-1.png";
static const QString QUIT_HOVER = ":/static/imgs/Quit-2.png";
static const QString TRANS = ":/static/imgs/Trans-1.png";
static const QString TRANS_HOVER = ":/static/imgs/Trans-2.png";

static const QString BUCKET = ":/static/imgs/bucket.png";
static const QString FILE = ":/static/imgs/file.png";
static const QString DIR = ":/static/imgs/dir.png";
};

// 定义SQLite数据库相关的命名空间SQLITE
namespace SQLITE
{
// SQLite数据库文件路径，由临时文件目录和"cos.db"文件名组成
static const QString NAME = FileHelper::joinPath(PATH::TMP, "cos.db");
};

// 定义SQL脚本相关的命名空间SQL
namespace SQL
{
// 登录信息表的SQL脚本路径，使用资源文件路径
static const QString LOGIN_INFO_TABLE = ":/static/sql/login_info.sql";
};

// 定义数据库表名相关的命名空间TABLES
namespace TABLES
{
// 登录信息表的表名
static const QString LOGIN_INFO = "login_info";
};

// 定义版本相关的命名空间VERSION
namespace VERSION
{
// 自定义版本标识
static const QString MAJOR_CUSTOM = "custom";

// 业务版本标识
static const QString MAJOR_BUSINESS = "business";

// 版本配置文件路径，使用资源文件路径
static const QString JSON_PATH = ":/static/versions/config_default.json";
};

// 定义环境相关的命名空间ENV
namespace ENV
{
// 开发环境标识
static const QString ENV_DEV = "dev";

// Alpha测试环境标识
static const QString ENV_ALPHA = "alpha";

// Beta测试环境标识
static const QString ENV_BETA = "beta";

// 预发布环境标识
static const QString ENV_PRE = "pre";

// 生产环境标识
static const QString ENV_PROD = "prod";
}

// 定义日志级别枚举
enum LOG_LEVEL
{
    TOTAL = 0,    // 总日志级别
    DEBUG = 1,    // 调试日志级别
    INFO = 2,     // 信息日志级别
    WARNING = 3,  // 警告日志级别
    ERROR = 4,    // 错误日志级别
    FATAL = 5     // 致命错误日志级别
};

// 定义日志级别名称列表
static const QStringList LOG_NAMES = QStringList() << "TOTAL" << "DEBUG" << "INFO" << "WARNING" << "ERROR" << "FATAL";
}

#endif // GLOBALS_H
