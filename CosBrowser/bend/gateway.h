#ifndef GATEWAY_H
#define GATEWAY_H

// 引入 QObject 和 QJsonValue 头文件
#include <QObject>
#include <QJsonValue>

// 引入 apis.h 头文件
#include "config/apis.h"

// 定义一个名为 GateWay 的类，继承自 QObject
class GateWay : public QObject
{
    // 使用 Q_OBJECT 宏，启用 Qt 的元对象系统
    Q_OBJECT

public:
    // 构造函数，使用 explicit 关键字防止隐式转换，parent 参数用于指定父对象
    explicit GateWay(QObject *parent = nullptr);

    // 析构函数
    ~GateWay();

    // 发送请求的函数，api 参数表示接口编号，params 参数表示请求参数
    void send(int api, const QJsonValue &params = QJsonValue());

private:
    // 分发请求的函数，根据 api 参数调用相应的处理函数
    void dispach(int api, const QJsonValue &params);

    // 处理登录请求的函数
    void apiLogin(const QJsonValue &params);

    // 桶操作接口
    void apiGetBuckets(const QJsonValue &); // 获取所有桶
    void apiPutBucket(const QJsonValue &params); // 创建新桶
    void apiDeleteBucket(const QJsonValue &params); // 删除桶

    // 对象操作接口
    void apiGetObjects(const QJsonValue &params); // 获取所有对象
    void apiGetObject(const QJsonValue &params); // 获取单个对象
    void apiPutObject(const QJsonValue &params); // 上传对象
};

#endif // GATEWAY_H
