#include "mansignals.h"

// ManSignals 类的构造函数
ManSignals::ManSignals(QObject *parent) : QObject(parent)
{
    // 注册自定义类型 QList<MyBucket> 以便在信号和槽机制中使用
    qRegisterMetaType<QList<MyBucket>>("QList<MyBucket>");

    // 注册自定义类型 QList<MyObject> 以便在信号和槽机制中使用
    qRegisterMetaType<QList<MyObject>>("QList<MyObject>");
}

// ManSignals 类的析构函数
ManSignals::~ManSignals()
{
    // 输出调试信息，表示 ManSignals 对象即将被删除
    qDebug("delete ManSignals");
}
