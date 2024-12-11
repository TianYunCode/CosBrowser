#ifndef DAOCLOUDSMOCK_H
#define DAOCLOUDSMOCK_H

// 引入 QJsonValue 头文件，用于处理 JSON 数据
#include <QJsonValue>

// 引入父类 DaoClouds 的头文件
#include "daoclouds.h"

// 定义一个名为 DaoCloudsMock 的类，继承自 DaoClouds
class DaoCloudsMock : public DaoClouds
{
public:
    // 构造函数，接受一个 QString 类型的参数 path，表示模拟数据的路径
    DaoCloudsMock(const QString &path);

    // 实现父类的纯虚函数，用于获取所有存储桶（bucket）
    // 返回值是一个包含 MyBucket 对象的 QList
    virtual QList<MyBucket> buckets();

    // 实现父类的纯虚函数，用于用户登录
    // 参数：secretId 和 secretKey 是用户的密钥信息
    // 返回值是一个包含 MyBucket 对象的 QList，表示登录后获取的存储桶列表
    virtual QList<MyBucket> login(const QString &secretId, const QString &secretKey);

    // 实现父类的纯虚函数，用于检查指定的存储桶是否存在
    // 参数：bucketName 是存储桶的名称
    // 返回值是一个布尔值，表示存储桶是否存在
    virtual bool isBucketExists(const QString &bucketName);

    // 实现父类的纯虚函数，用于获取指定存储桶的地理位置
    // 参数：bucketName 是存储桶的名称
    // 返回值是一个 QString，表示存储桶的地理位置
    virtual QString getBucketLocation(const QString &bucketName);

    // 实现父类的纯虚函数，用于创建一个新的存储桶
    // 参数：bucketName 是存储桶的名称，location 是存储桶的地理位置
    virtual void putBucket(const QString &bucketName, const QString &location);

    // 实现父类的纯虚函数，用于删除指定的存储桶
    // 参数：bucketName 是存储桶的名称
    virtual void deleteBucket(const QString &bucketName);

    // 实现父类的纯虚函数，用于获取指定存储桶中的对象列表
    // 参数：bucketName 是存储桶的名称，dir 是目录路径
    // 返回值是一个包含 MyObject 对象的 QList，表示存储桶中的对象列表
    virtual QList<MyObject> getObjects(const QString &bucketName, const QString &dir);

    // 实现父类的纯虚函数，用于上传对象到指定的存储桶
    // 参数：bucketName 是存储桶的名称，key 是对象的键（路径），localPath 是本地文件路径，callback 是传输进度回调函数
    virtual void putObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback);

    // 实现父类的纯虚函数，用于从指定的存储桶下载对象
    // 参数：bucketName 是存储桶的名称，key 是对象的键（路径），localPath 是本地文件路径，callback 是传输进度回调函数
    virtual void getObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback);

private:
    // 用于存储模拟数据的 QJsonValue 对象
    QJsonValue m_mock;
};

#endif // DAOCLOUDSMOCK_H
