#ifndef DAOCLOUDSCOS_H
#define DAOCLOUDSCOS_H

// 引入父类 DaoClouds 的头文件
#include "daoclouds.h"

// 引入自定义的云模型头文件
#include "middle/models/cloudmodels.h"

// 引入腾讯云 COS 相关的头文件
namespace qcloud_cos
{
class CosConfig;  // 腾讯云 COS 配置类
class CosResult;  // 腾讯云 COS 操作结果类
class GetBucketResp;  // 获取存储桶响应类
}

// 定义一个名为 DaoCloudsCos 的类，继承自 DaoClouds
class DaoCloudsCos : public DaoClouds
{
public:
    // 默认构造函数
    DaoCloudsCos();

    // 析构函数
    ~DaoCloudsCos();

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
    QList<MyObject> getObjects(const QString &bucketName, const QString &dir);

    // 检查指定的对象是否存在于存储桶中
    // 参数：bucketName 是存储桶的名称，key 是对象的键（路径）
    // 返回值是一个布尔值，表示对象是否存在
    bool isObjectExists(const QString &bucketName, const QString &key);

    // 实现父类的纯虚函数，用于上传对象到指定的存储桶
    // 参数：bucketName 是存储桶的名称，key 是对象的键（路径），localPath 是本地文件路径，callback 是传输进度回调函数
    virtual void putObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback);

    // 实现父类的纯虚函数，用于从指定的存储桶下载对象
    // 参数：bucketName 是存储桶的名称，key 是对象的键（路径），localPath 是本地文件路径，callback 是传输进度回调函数
    virtual void getObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback);

private:
    // 获取指定目录下的对象列表
    // 参数：resp 是获取存储桶响应对象，dir 是目录路径
    // 返回值是一个包含 MyObject 对象的 QList，表示目录下的对象列表
    QList<MyObject> getDirList(qcloud_cos::GetBucketResp &resp, const QString &dir);

    // 获取指定目录下的文件列表
    // 参数：resp 是获取存储桶响应对象，dir 是目录路径
    // 返回值是一个包含 MyObject 对象的 QList，表示目录下的文件列表
    QList<MyObject> getFileList(qcloud_cos::GetBucketResp &resp, const QString &dir);

    // 抛出错误信息
    // 参数：code 是错误代码，result 是腾讯云 COS 操作结果对象
    void throwError(const QString &code, qcloud_cos::CosResult &result);

    // 根据存储桶名称获取存储桶对象
    // 参数：bucketName 是存储桶的名称
    // 返回值是一个 MyBucket 对象，表示对应的存储桶
    MyBucket getBucketByName(const QString &bucketName);

private:
    // 腾讯云 COS 配置对象指针
    qcloud_cos::CosConfig *m_config = nullptr;
};

#endif // DAOCLOUDSCOS_H
