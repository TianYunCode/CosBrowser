#ifndef MANCLOUD_H
#define MANCLOUD_H

// 引入 QObject 头文件
#include <QObject>

// 引入 cloudmodels.h 头文件
#include "middle/models/cloudmodels.h"

// 定义一个名为 ManCloud 的类，继承自 QObject
class ManCloud : public QObject
{
    // 使用 Q_OBJECT 宏，启用 Qt 的元对象系统
    Q_OBJECT

public:
    // 构造函数，使用 explicit 关键字防止隐式转换，parent 参数用于指定父对象
    explicit ManCloud(QObject *parent = nullptr);

    // 析构函数
    ~ManCloud();

    // 登录接口，传入 secretId 和 secretKey 进行身份验证
    void login(QString secretId, QString secretKey);

    // 桶操作接口
    void getBuckets(); // 获取所有存储桶
    void putBucket(const QString &bucketName, const QString &location); // 创建新的存储桶
    void deleteBucket(const QString &bucketName); // 删除指定的存储桶

    // 对象操作接口
    void getObjects(const QString &bucketName, const QString &dir = ""); // 获取指定存储桶中的对象列表
    void getObject(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath); // 下载指定对象到本地
    void putObject(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath); // 上传本地文件到指定存储桶
    QString currentBucketName() const; // 获取当前存储桶名称

    QString currentDir() const; // 获取当前对象所在的父目录

private:
    // 私有成员函数，用于处理已有的存储桶列表
    void bucketsAlready(const QList<MyBucket> &buckets);

private:
    QString m_currentBucketName; // 记录当前对象所在存储桶名称
    QString m_currentDir;        // 记录当前对象所在的父目录
};

#endif // MANCLOUD_H
