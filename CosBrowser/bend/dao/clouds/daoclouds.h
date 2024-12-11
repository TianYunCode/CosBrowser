#ifndef DAOCLOUDS_H
#define DAOCLOUDS_H

// 引入必要的头文件
#include <QList>  // 用于存储列表数据
#include <functional>  // 用于定义回调函数
#include <QString>  // 用于处理字符串

// 引入自定义的云模型头文件
#include "middle/models/cloudmodels.h"

// 定义一个类型别名，用于表示传输进度回调函数
// 该回调函数接收三个参数：已传输的大小、总大小和一个void指针
using TransProgressCallback = std::function<void(uint64_t transferred_size, uint64_t total_size, void *)>;

// 定义一个名为 DaoClouds 的类
class DaoClouds
{
public:
    // 默认构造函数
    DaoClouds() {};

    // 纯虚函数，用于获取所有存储桶（bucket）
    // 返回值是一个包含 MyBucket 对象的 QList
    virtual QList<MyBucket> buckets() = 0;

    // 纯虚函数，用于用户登录
    // 参数：secretId 和 secretKey 是用户的密钥信息
    // 返回值是一个包含 MyBucket 对象的 QList，表示登录后获取的存储桶列表
    virtual QList<MyBucket> login(const QString &secretId, const QString &secretKey) = 0;

    // 纯虚函数，用于检查指定的存储桶是否存在
    // 参数：bucketName 是存储桶的名称
    // 返回值是一个布尔值，表示存储桶是否存在
    virtual bool isBucketExists(const QString &bucketName) = 0;

    // 纯虚函数，用于获取指定存储桶的地理位置
    // 参数：bucketName 是存储桶的名称
    // 返回值是一个 QString，表示存储桶的地理位置
    virtual QString getBucketLocation(const QString &bucketName) = 0;

    // 纯虚函数，用于创建一个新的存储桶
    // 参数：bucketName 是存储桶的名称，location 是存储桶的地理位置
    virtual void putBucket(const QString &bucketName, const QString &location) = 0;

    // 纯虚函数，用于删除指定的存储桶
    // 参数：bucketName 是存储桶的名称
    virtual void deleteBucket(const QString &bucketName) = 0;

    // 纯虚函数，用于获取指定存储桶中的对象列表
    // 参数：bucketName 是存储桶的名称，dir 是目录路径
    // 返回值是一个包含 MyObject 对象的 QList，表示存储桶中的对象列表
    virtual QList<MyObject> getObjects(const QString &bucketName, const QString &dir) = 0;

    // 纯虚函数，用于上传对象到指定的存储桶
    // 参数：bucketName 是存储桶的名称，key 是对象的键（路径），localPath 是本地文件路径，callback 是传输进度回调函数
    virtual void putObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback) = 0;

    // 纯虚函数，用于从指定的存储桶下载对象
    // 参数：bucketName 是存储桶的名称，key 是对象的键（路径），localPath 是本地文件路径，callback 是传输进度回调函数
    virtual void getObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback) = 0;
};

#endif // DAOCLOUDS_H
