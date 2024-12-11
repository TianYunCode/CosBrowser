#include <QJsonArray>
#include <QThread>

#include "daocloudsmock.h"
#include "config/exceptions.h"
#include "config/errorcode.h"
#include "helper/filehelper.h"
#include "middle/manglobal.h"

/**
 * @brief DaoCloudsMock类的构造函数
 * @param path 模拟数据的JSON文件路径
 * 从指定路径读取JSON文件并解析为QJsonValue对象
 */
DaoCloudsMock::DaoCloudsMock(const QString &path)
{
    m_mock = FileHelper::readAllJson(path).toJsonValue();
}

/**
 * @brief 获取所有存储桶
 * @return QList<MyBucket> 存储桶列表
 */
QList<MyBucket> DaoCloudsMock::buckets()
{
    QList<MyBucket> res;
    QJsonArray arr = m_mock["buckets"].toArray();
    for (int i = 0; i < arr.count(); ++i)
    {
        QJsonValue v = arr[i];
        MyBucket bucket;
        bucket.name = v["name"].toString();
        bucket.location = v["location"].toString();
        bucket.createDate = v["create_date"].toString();

        res.append(bucket);
        mInfo(QString::fromLocal8Bit("name[%1], location[%2], date[%3]").arg(bucket.name, bucket.location, bucket.createDate));
    }

    return res;
}

/**
 * @brief 登录并获取存储桶列表
 * @param secretId 腾讯云的SecretId
 * @param secretKey 腾讯云的SecretKey
 * @return QList<MyBucket> 存储桶列表
 * @throws BaseException 如果SecretId或SecretKey不正确，抛出异常
 */
QList<MyBucket> DaoCloudsMock::login(const QString &secretId, const QString &secretKey)
{
    QJsonArray arr = m_mock["users"].toArray();
    for (int i = 0; i < arr.count(); ++i)
    {
        QJsonValue v = arr[i];
        if (secretId == v["secretId"].toString() && secretKey == v["secretKey"].toString())
        {
            return buckets();
        }
    }

    throw BaseException(EC_211000, QString::fromLocal8Bit("请检查您的SecretId或SecretKey是否正确"));
}

/**
 * @brief 检查存储桶是否存在
 * @param bucketName 存储桶名称
 * @return bool 存储桶是否存在
 * @note 当前实现总是返回false
 */
bool DaoCloudsMock::isBucketExists(const QString &bucketName)
{
    return false;
}

/**
 * @brief 获取存储桶的地理位置
 * @param bucketName 存储桶名称
 * @return QString 存储桶的地理位置
 * @note 当前实现总是返回空字符串
 */
QString DaoCloudsMock::getBucketLocation(const QString &bucketName)
{
    return QString();
}

/**
 * @brief 创建存储桶
 * @param bucketName 存储桶名称
 * @param location 存储桶的地理位置
 * @note 当前实现为空
 */
void DaoCloudsMock::putBucket(const QString &bucketName, const QString &location)
{
}

/**
 * @brief 删除存储桶
 * @param bucketName 存储桶名称
 * @note 当前实现为空
 */
void DaoCloudsMock::deleteBucket(const QString &bucketName)
{
}

/**
 * @brief 获取存储桶中的对象列表
 * @param bucketName 存储桶名称
 * @param dir 目录路径
 * @return QList<MyObject> 对象列表
 * @note 当前实现总是返回空列表
 */
QList<MyObject> DaoCloudsMock::getObjects(const QString &bucketName, const QString &dir)
{
    return QList<MyObject>();
}

/**
 * @brief 上传对象
 * @param bucketName 存储桶名称
 * @param key 对象的键（路径）
 * @param localPath 本地文件路径
 * @param callback 上传进度回调函数
 * @note 当前实现为空
 */
void DaoCloudsMock::putObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
}

/**
 * @brief 下载对象
 * @param bucketName 存储桶名称
 * @param key 对象的键（路径）
 * @param localPath 本地文件路径
 * @param callback 下载进度回调函数
 * @note 当前实现为空
 */
void DaoCloudsMock::getObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
}
