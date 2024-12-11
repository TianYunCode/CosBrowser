#include <QDebug>

#include "mancloud.h"
#include "middle/manglobal.h"
#include "middle/signals/mansignals.h"
#include "plugins/manplugin.h"
#include "bend/dao/clouds/daocloudsmock.h"

/**
 * @brief ManCloud类的构造函数
 *
 * 该构造函数用于初始化ManCloud对象。
 *
 * @param parent 父对象指针，默认为nullptr
 */
ManCloud::ManCloud(QObject *parent) : QObject{parent}
{
    // 构造函数为空，因为不需要额外的初始化操作
}

/**
 * @brief ManCloud类的析构函数
 *
 * 该析构函数用于清理资源，并在控制台输出一条调试信息。
 */
ManCloud::~ManCloud()
{
    qDebug("delete ManCloud ");
}

/**
 * @brief 登录云服务的函数
 *
 * 该函数用于使用提供的secretId和secretKey登录云服务，并获取存储桶列表。
 *
 * @param secretId 云服务的secretId
 * @param secretKey 云服务的secretKey
 */
void ManCloud::login(QString secretId, QString secretKey)
{
    // 调用插件的登录方法，获取存储桶列表
    QList<MyBucket> buckets = MG->mPlugin->clouds()->login(secretId, secretKey);

    // 发出登录成功的信号
    emit MG->mSignal->loginSuccess();

    // 处理获取到的存储桶列表
    bucketsAlready(buckets);
}

/**
 * @brief 获取存储桶列表的函数
 *
 * 该函数用于获取当前用户的所有存储桶列表。
 */
void ManCloud::getBuckets()
{
    // 调用插件的方法，获取存储桶列表
    QList<MyBucket> buckets = MG->mPlugin->clouds()->buckets();

    // 处理获取到的存储桶列表
    bucketsAlready(buckets);
}

/**
 * @brief 创建存储桶的函数
 *
 * 该函数用于创建一个新的存储桶。
 *
 * @param bucketName 存储桶的名称
 * @param location 存储桶的地理位置
 */
void ManCloud::putBucket(const QString &bucketName, const QString &location)
{
    // 调用插件的方法，创建存储桶
    MG->mPlugin->clouds()->putBucket(bucketName, location);

    // 获取并更新存储桶列表
    getBuckets();
}

/**
 * @brief 删除存储桶的函数
 *
 * 该函数用于删除指定的存储桶。
 *
 * @param bucketName 存储桶的名称
 */
void ManCloud::deleteBucket(const QString &bucketName)
{
    // 调用插件的方法，删除存储桶
    MG->mPlugin->clouds()->deleteBucket(bucketName);

    // 获取并更新存储桶列表
    getBuckets();
}

/**
 * @brief 获取存储桶中对象的函数
 *
 * 该函数用于获取指定存储桶中的对象列表。
 *
 * @param bucketName 存储桶的名称
 * @param dir 对象所在的目录
 */
void ManCloud::getObjects(const QString &bucketName, const QString &dir)
{
    // 调用插件的方法，获取对象列表
    QList<MyObject> objs = MG->mPlugin->clouds()->getObjects(bucketName, dir);

    // 更新当前存储桶名称和目录
    m_currentBucketName = bucketName;
    m_currentDir = dir;

    // 发出获取对象成功的信号
    emit MG->mSignal->objectsSuccess(objs);
}

/**
 * @brief 下载对象的函数
 *
 * 该函数用于从云存储中下载指定对象。
 *
 * @param jobId 任务ID
 * @param bucketName 存储桶的名称
 * @param key 对象的键（路径）
 * @param localPath 本地保存路径
 */
void ManCloud::getObject(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath)
{
    // 定义下载进度回调函数
    auto callback = [=](qulonglong transferred_size, qulonglong total_size, void *)
    {
        // 确保已传输的大小不超过总大小
        assert(transferred_size <= total_size);

        // 每传输512KB，发出一次进度信号
        if (0 == transferred_size % (1024 * 512))
        {
            emit MG->mSignal->downloadProcess(jobId, transferred_size, total_size);
        }
    };

    // 调用插件的方法，下载对象
    MG->mPlugin->clouds()->getObject(bucketName, key, localPath, callback);

    // 发出下载成功的信号
    emit MG->mSignal->downloadSuccess(jobId);
}

/**
 * @brief 上传对象的函数
 *
 * 该函数用于将本地对象上传到云存储。
 *
 * @param jobId 任务ID
 * @param bucketName 存储桶的名称
 * @param key 对象的键（路径）
 * @param localPath 本地文件路径
 */
void ManCloud::putObject(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath)
{
    // 定义上传进度回调函数
    auto callback = [=](qulonglong transferred_size, qulonglong total_size, void *)
    {
        // 确保已传输的大小不超过总大小
        assert(transferred_size <= total_size);

        // 每传输512KB，发出一次进度信号
        if (0 == transferred_size % (1024 * 512))
        {
            emit MG->mSignal->uploadProcess(jobId, transferred_size, total_size);
        }
    };

    // 调用插件的方法，上传对象
    MG->mPlugin->clouds()->putObject(bucketName, key, localPath, callback);

    // 发出上传成功的信号
    emit MG->mSignal->uploadSuccess(jobId);
}

/**
 * @brief 处理存储桶列表的函数
 *
 * 该函数用于处理获取到的存储桶列表，并发出相应的信号。
 *
 * @param buckets 存储桶列表
 */
void ManCloud::bucketsAlready(const QList<MyBucket> &buckets)
{
    // 清空当前存储桶名称和目录
    m_currentBucketName.clear();
    m_currentDir.clear();

    // 发出存储桶列表获取成功的信号
    emit MG->mSignal->bucketsSuccess(buckets);
}

/**
 * @brief 获取当前目录的函数
 *
 * 该函数用于获取当前操作的目录。
 *
 * @return 当前目录
 */
QString ManCloud::currentDir() const
{
    return m_currentDir;
}

/**
 * @brief 获取当前存储桶名称的函数
 *
 * 该函数用于获取当前操作的存储桶名称。
 *
 * @return 当前存储桶名称
 */
QString ManCloud::currentBucketName() const
{
    return m_currentBucketName;
}
