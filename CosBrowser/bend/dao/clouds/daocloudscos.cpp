#include <QDebug>

#include "daocloudscos.h"
#include "config/exceptions.h"
#include "config/errorcode.h"

// 此头文件要放到最后，否则可能会报错
#include "cos_api.h"

using namespace qcloud_cos;

/**
 * @brief DaoCloudsCos类的构造函数
 * 初始化CosConfig对象，用于配置腾讯云COS服务
 */
DaoCloudsCos::DaoCloudsCos()
{
    m_config = new CosConfig("./cosconfig.json");
}

/**
 * @brief DaoCloudsCos类的析构函数
 * 释放CosConfig对象的内存，并将指针置为nullptr
 */
DaoCloudsCos::~DaoCloudsCos()
{
    delete m_config;
    m_config = nullptr;
}

/**
 * @brief 获取所有存储桶
 * @return QList<MyBucket> 存储桶列表
 */
QList<MyBucket> DaoCloudsCos::buckets()
{
    QList<MyBucket> res;

    GetServiceReq req;
    GetServiceResp resp;
    CosAPI cos = CosAPI(*m_config);
    CosResult result = cos.GetService(req, &resp);

    if (!result.IsSucc())
    {
        throwError(EC_211000, result);
    }

    std::vector<Bucket> bs = resp.GetBuckets();
    for (std::vector<Bucket>::const_iterator itr = bs.begin(); itr != bs.end(); ++itr)
    {
        const Bucket &v = *itr;

        MyBucket b;
        b.name = QString(v.m_name.c_str());
        b.location = QString(v.m_location.c_str());
        b.createDate = QString(v.m_create_date.c_str());
        res.append(b);
    }

    return res;
}

/**
 * @brief 登录并获取存储桶列表
 * @param secretId 腾讯云的SecretId
 * @param secretKey 腾讯云的SecretKey
 * @return QList<MyBucket> 存储桶列表
 */
QList<MyBucket> DaoCloudsCos::login(const QString &secretId, const QString &secretKey)
{
    m_config->SetAccessKey(secretId.toStdString());
    m_config->SetSecretKey(secretKey.toStdString());
    m_config->SetRegion("ap-shanghai");

    return buckets();
}

/**
 * @brief 检查存储桶是否存在
 * @param bucketName 存储桶名称
 * @return bool 存储桶是否存在
 */
bool DaoCloudsCos::isBucketExists(const QString &bucketName)
{
    MyBucket bucket = getBucketByName(bucketName);

    return bucket.isValid();
}

/**
 * @brief 获取存储桶的地理位置
 * @param bucketName 存储桶名称
 * @return QString 存储桶的地理位置
 * @throws BaseException 如果获取失败，抛出异常
 */
QString DaoCloudsCos::getBucketLocation(const QString &bucketName)
{
    CosAPI cos = CosAPI(*m_config);
    QString location(cos.GetBucketLocation(bucketName.toStdString()).c_str());
    if (location != "")
    {
        return location;
    }

    MyBucket bucket = getBucketByName(bucketName);
    if (bucket.isValid())
    {
        return bucket.location;
    }

    throw BaseException(EC_332000, QString::fromLocal8Bit("获取桶位置失败 %1").arg(bucketName));
}

/**
 * @brief 创建存储桶
 * @param bucketName 存储桶名称
 * @param location 存储桶的地理位置
 */
void DaoCloudsCos::putBucket(const QString &bucketName, const QString &location)
{
    if (isBucketExists(bucketName))
    {
        return;
    }

    PutBucketReq req(bucketName.toLocal8Bit().data());
    PutBucketResp resp;

    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    CosResult result = cos.PutBucket(req, &resp);
    if (!result.IsSucc())
    {
        throwError(EC_331100, result);
    }
}

/**
 * @brief 删除存储桶
 * @param bucketName 存储桶名称
 */
void DaoCloudsCos::deleteBucket(const QString &bucketName)
{
    if (!isBucketExists(bucketName))
    {
        return;
    }

    DeleteBucketReq req(bucketName.toLocal8Bit().data());
    DeleteBucketResp resp;
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    CosResult result = cos.DeleteBucket(req, &resp);
    if (!result.IsSucc())
    {
        throwError(EC_331300, result);
    }
}

/**
 * @brief 获取存储桶中的对象列表
 * @param bucketName 存储桶名称
 * @param dir 目录路径
 * @return QList<MyObject> 对象列表
 * @throws BaseException 如果获取失败，抛出异常
 */
QList<MyObject> DaoCloudsCos::getObjects(const QString &bucketName, const QString &dir)
{
    GetBucketReq req(bucketName.toLocal8Bit().data());
    if (dir != "")
    {
        req.SetPrefix(dir.toLocal8Bit().data());
    }

    req.SetDelimiter("/");

    GetBucketResp resp;
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    CosResult result = cos.GetBucket(req, &resp);

    if (!result.IsSucc())
    {
        throwError(EC_331200, result);
    }

    return getDirList(resp, dir) + getFileList(resp, dir);
}

/**
 * @brief 检查对象是否存在
 * @param bucketName 存储桶名称
 * @param key 对象的键（路径）
 * @return bool 对象是否存在
 */
bool DaoCloudsCos::isObjectExists(const QString &bucketName, const QString &key)
{
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    return cos.IsObjectExist(bucketName.toStdString(), key.toLocal8Bit().data());
}

/**
 * @brief 上传对象
 * @param bucketName 存储桶名称
 * @param key 对象的键（路径）
 * @param localPath 本地文件路径
 * @param callback 上传进度回调函数
 * @throws BaseException 如果上传失败，抛出异常
 */
void DaoCloudsCos::putObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
    // 初始化上传
    SharedAsyncContext context;
    // 异步上传
    AsyncPutObjectReq put_req(bucketName.toLocal8Bit().data(), key.toLocal8Bit().data(), localPath.toLocal8Bit().data());
    // 设置上传进度回调
    if (callback)
    {
        put_req.SetTransferProgressCallback(callback);
    }

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    // 开始上传对象
    context = cos.AsyncPutObject(put_req);
    context->WaitUntilFinish(); // 等待上传结束
    CosResult result = context->GetResult();

    if (!result.IsSucc())
    {
        throwError(EC_332400, result);
    }
}

/**
 * @brief 下载对象
 * @param bucketName 存储桶名称
 * @param key 对象的键（路径）
 * @param localPath 本地文件路径
 * @param callback 下载进度回调函数
 * @throws BaseException 如果下载失败，抛出异常
 */
void DaoCloudsCos::getObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
    // 下载初始化
    SharedAsyncContext context;
    // 异步下载
    AsyncGetObjectReq get_req(bucketName.toLocal8Bit().data(), key.toLocal8Bit().data(), localPath.toLocal8Bit().data());
    // 设置下载回调
    if (callback)
    {
        get_req.SetTransferProgressCallback(callback);
    }

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    // 开始下载对象
    context = cos.AsyncGetObject(get_req);
    context->WaitUntilFinish();
    CosResult result = context->GetResult();
    if (!result.IsSucc())
    {
        throwError(EC_332500, result);
    }
}

/**
 * @brief 获取目录列表
 * @param resp GetBucketResp对象
 * @param dir 目录路径
 * @return QList<MyObject> 目录列表
 */
QList<MyObject> DaoCloudsCos::getDirList(GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    // 获取目录列表
    std::vector<std::string> cs = resp.GetCommonPrefixes();
    for (int i = 0; i < cs.size(); i++)
    {
        QString key(cs[i].c_str());
        // qDebug() << "dir: " << key;
        MyObject object;
        object.dir = dir;
        object.name = key.mid(dir.size());
        object.lastmodified = "-";
        object.key = key;
        res.append(object);
        // qDebug() << "dirName: " << object.name;
    }

    return res;
}

/**
 * @brief 获取文件列表
 * @param resp GetBucketResp对象
 * @param dir 目录路径
 * @return QList<MyObject> 文件列表
 */
QList<MyObject> DaoCloudsCos::getFileList(GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    // 获取文件列表
    const std::vector<Content> &contents = resp.GetContents();
    for (std::vector<Content>::const_iterator itr = contents.begin(); itr != contents.end(); ++itr)
    {
        const Content &content = *itr;
        QString key(content.m_key.c_str());
        // qDebug() << "file: " << key;
        QString name = key.mid(dir.size());
        if (key != dir)
        {
            MyObject object;
            object.name = name;
            object.lastmodified = QString(content.m_last_modified.c_str());
            object.size = QString(content.m_size.c_str()).toULongLong();
            object.dir = dir;
            object.key = key;
            res.append(object);
            // qDebug() << "fileName: " << name;
        }
    }

    return res;
}

/**
 * @brief 抛出错误
 * @param code 错误码
 * @param result CosResult对象
 * @throws BaseException 抛出异常
 */
void DaoCloudsCos::throwError(const QString &code, qcloud_cos::CosResult &result)
{
    QString msg = QString::fromLocal8Bit("腾讯云错误码【%1】： %2").arg(result.GetErrorCode().c_str(), result.GetErrorMsg().c_str());
    qDebug() << msg;
    throw BaseException(code, msg);
}

/**
 * @brief 根据名称获取存储桶
 * @param bucketName 存储桶名称
 * @return MyBucket 存储桶对象
 */
MyBucket DaoCloudsCos::getBucketByName(const QString &bucketName)
{
    QList<MyBucket> bs = buckets();
    for (const auto &b : qAsConst(bs))
    {
        if (b.name == bucketName)
        {
            return b;
        }
    }

    return MyBucket();
}
