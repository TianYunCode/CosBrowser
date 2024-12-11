#ifndef MANSIGNALS_H
#define MANSIGNALS_H

// 包含必要的Qt头文件
#include <QObject>

// 包含自定义的云模型头文件
#include "middle/models/cloudmodels.h"

/**
 * @brief ManSignals类，继承自QObject，用于管理信号的发送和接收
 */
class ManSignals : public QObject
{
    Q_OBJECT  // 使用Q_OBJECT宏，启用Qt的元对象系统

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针，默认为nullptr
     */
    explicit ManSignals(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~ManSignals();

signals:
    /**
     * @brief 登录成功信号
     */
    void loginSuccess();

    /**
     * @brief 错误信号
     * @param api API编号
     * @param msg 错误信息
     * @param req 请求的JSON数据
     */
    void error(int api, const QString &msg, const QJsonValue &req);

    /**
     * @brief 未登录信号
     */
    void unLogin();

    /**
     * @brief 获取存储桶列表成功信号
     * @param buckets 存储桶列表
     */
    void bucketsSuccess(const QList<MyBucket> &buckets);

    /**
     * @brief 获取对象列表成功信号
     * @param objects 对象列表
     */
    void objectsSuccess(const QList<MyObject> &objects);

    /**
     * @brief 开始下载信号
     * @param jobId 任务ID
     * @param key 对象的键
     * @param localPath 本地路径
     * @param total 总大小
     */
    void startDownload(const QString &jobId, const QString &key, const QString &localPath, qulonglong total);

    /**
     * @brief 下载对象进度信号
     * @param jobId 任务ID
     * @param transferred 已传输的大小
     * @param total 总大小
     */
    void downloadProcess(const QString &jobId, qulonglong transferred, qulonglong total);

    /**
     * @brief 下载对象成功信号
     * @param jobId 任务ID
     */
    void downloadSuccess(const QString &jobId);

    /**
     * @brief 开始上传信号
     * @param jobId 任务ID
     * @param key 对象的键
     * @param localPath 本地路径
     */
    void startUpload(const QString &jobId, const QString &key, const QString &localPath);

    /**
     * @brief 上传对象进度信号
     * @param jobId 任务ID
     * @param transferred 已传输的大小
     * @param total 总大小
     */
    void uploadProcess(const QString &jobId, qulonglong transferred, qulonglong total);

    /**
     * @brief 上传对象成功信号
     * @param jobId 任务ID
     */
    void uploadSuccess(const QString &jobId);
};

#endif // MANSIGNALS_H
