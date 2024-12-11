#include <QtConcurrent>

#include "gateway.h"
#include "bend/man/mancloud.h"
#include "config/apis.h"
#include "config/loggerproxy.h"
#include "middle/manglobal.h"
#include "middle/signals/mansignals.h"

/**
 * @brief GateWay类的构造函数
 *
 * 该构造函数用于初始化GateWay对象。
 *
 * @param parent 父对象指针，默认为nullptr
 */
GateWay::GateWay(QObject *parent) : QObject{parent}
{
    // 构造函数为空，因为不需要额外的初始化操作
}

/**
 * @brief GateWay类的析构函数
 *
 * 该析构函数用于清理资源，并在控制台输出一条调试信息。
 */
GateWay::~GateWay()
{
    qDebug("delete GateWay ");
}

/**
 * @brief 发送API请求的函数
 *
 * 该函数用于异步发送API请求，并在请求处理过程中捕获异常。
 *
 * @param api API的标识符
 * @param params API请求的参数
 */
void GateWay::send(int api, const QJsonValue &params)
{
    // 使用QtConcurrent::run异步执行API请求
    QtConcurrent::run([=]()
                      {
                          try {
                              // 调用dispach函数处理API请求
                              this->dispach(api, params);
                          }
                          catch(BaseException e) {
                              // 捕获自定义异常并记录错误信息
                              mError(e.msg());
                              // 发出错误信号
                              emit MG->mSignal->error(api, e.msg(), params);
                          }
                          catch(...){
                              // 捕获未知异常并记录错误信息
                              BaseException e = BaseException(EC_100000, QString::fromLocal8Bit("未知错误"));
                              mError(e.msg());
                              // 发出错误信号
                              emit MG->mSignal->error(api, e.msg(), params);
                          } });
}

/**
 * @brief 分发API请求的函数
 *
 * 该函数根据API的标识符分发具体的API请求处理函数。
 *
 * @param api API的标识符
 * @param params API请求的参数
 */
void GateWay::dispach(int api, const QJsonValue &params)
{
    // 根据API标识符调用相应的处理函数
    switch (api)
    {
    case API::LOGIN::NORMAL:
        apiLogin(params);
        break;

        // 桶操作接口
    case API::BUCKETS::LIST:
        apiGetBuckets(params);
        break;
    case API::BUCKETS::PUT:
        apiPutBucket(params);
        break;
    case API::BUCKETS::DEL:
        apiDeleteBucket(params);
        break;

        // 对象操作接口
    case API::OBJECTS::LIST:
        apiGetObjects(params);
        break;
    case API::OBJECTS::GET:
        apiGetObject(params);
        break;
    case API::OBJECTS::PUT:
        apiPutObject(params);
        break;
    default:
        break;
    }
}

/**
 * @brief 处理登录API请求的函数
 *
 * 该函数用于处理登录API请求，并调用云服务进行登录操作。
 *
 * @param params API请求的参数
 */
void GateWay::apiLogin(const QJsonValue &params)
{
    // 从参数中提取secretId和secretKey
    QString secretId = params["secretId"].toString();
    QString secretKey = params["secretKey"].toString();

    // 调用云服务的登录函数
    MG->mCloud->login(secretId, secretKey);
}

/**
 * @brief 处理获取桶列表API请求的函数
 *
 * 该函数用于处理获取桶列表API请求，并调用云服务获取桶列表。
 *
 * @param params API请求的参数
 */
void GateWay::apiGetBuckets(const QJsonValue &)
{
    // 调用云服务的获取桶列表函数
    MG->mCloud->getBuckets();
}

/**
 * @brief 处理创建桶API请求的函数
 *
 * 该函数用于处理创建桶API请求，并调用云服务创建桶。
 *
 * @param params API请求的参数
 */
void GateWay::apiPutBucket(const QJsonValue &params)
{
    // 从参数中提取桶名称和位置
    QString bucketName = params["bucketName"].toString();
    QString location = params["location"].toString();

    // 调用云服务的创建桶函数
    MG->mCloud->putBucket(bucketName, location);
}

/**
 * @brief 处理删除桶API请求的函数
 *
 * 该函数用于处理删除桶API请求，并调用云服务删除桶。
 *
 * @param params API请求的参数
 */
void GateWay::apiDeleteBucket(const QJsonValue &params)
{
    // 从参数中提取桶名称
    QString bucketName = params["bucketName"].toString();

    // 调用云服务的删除桶函数
    MG->mCloud->deleteBucket(bucketName);
}

/**
 * @brief 处理获取对象列表API请求的函数
 *
 * 该函数用于处理获取对象列表API请求，并调用云服务获取对象列表。
 *
 * @param params API请求的参数
 */
void GateWay::apiGetObjects(const QJsonValue &params)
{
    // 从参数中提取桶名称和目录
    QString bucketName = params["bucketName"].toString();
    QString dir = params["dir"].toString();

    // 调用云服务的获取对象列表函数
    MG->mCloud->getObjects(bucketName, dir);
}

/**
 * @brief 处理获取对象API请求的函数
 *
 * 该函数用于处理获取对象API请求，并调用云服务获取对象。
 *
 * @param params API请求的参数
 */
void GateWay::apiGetObject(const QJsonValue &params)
{
    // 从参数中提取任务ID、桶名称、对象键和本地路径
    QString jobId = params["jobId"].toString(); // 用于更新下载进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();

    // 调用云服务的获取对象函数
    MG->mCloud->getObject(jobId, bucketName, key, localPath);
}

/**
 * @brief 处理上传对象API请求的函数
 *
 * 该函数用于处理上传对象API请求，并调用云服务上传对象。
 *
 * @param params API请求的参数
 */
void GateWay::apiPutObject(const QJsonValue &params)
{
    // 从参数中提取任务ID、桶名称、对象键和本地路径
    QString jobId = params["jobId"].toString(); // 用于更新上传进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();

    // 调用云服务的上传对象函数
    MG->mCloud->putObject(jobId, bucketName, key, localPath);
}
