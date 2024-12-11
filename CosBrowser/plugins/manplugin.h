#ifndef MANPLUGIN_H
#define MANPLUGIN_H

// 包含必要的Qt头文件
#include <QObject>

// 前向声明两个类，避免直接包含头文件
class DaoClouds;
class Version;

/**
 * @brief ManPlugin类，继承自QObject，用于管理插件
 */
class ManPlugin : public QObject
{
    Q_OBJECT  // 使用Q_OBJECT宏，启用Qt的元对象系统

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针，默认为nullptr
     */
    explicit ManPlugin(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~ManPlugin();

    /**
     * @brief 获取DaoClouds对象
     * @return DaoClouds指针，指向DaoClouds对象
     */
    DaoClouds *clouds() const;

    /**
     * @brief 安装插件
     * @param argc 命令行参数数量
     * @param argv 命令行参数数组
     */
    void installPlugins(int argc, char *argv[]);

private:
    DaoClouds *m_clouds; // 注意：不能使用派生类作为它的类型
    Version *m_version;
};

#endif // MANPLUGIN_H
