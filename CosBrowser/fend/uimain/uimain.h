#ifndef UIMAIN_H
#define UIMAIN_H

// 包含QJsonValue类头文件
#include <QJsonValue>

// 包含自定义的UiQosDialog头文件
#include "fend/uicom/uiqosdialog.h"

// 包含自定义的CloudModels头文件
#include "middle/models/cloudmodels.h"

// 定义Ui命名空间
namespace Ui
{
class UiMain;
}

// 声明UiTransfer类
class UiTransfer;

// 定义UiMain类，继承自UiQosDialog
class UiMain : public UiQosDialog
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiMain(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiMain();

private slots:
    /**
     * @brief 处理未登录状态
     */
    void onUnLogin();

    /**
     * @brief 获取存储桶列表成功时的处理函数
     * @param buckets 存储桶列表
     */
    void onBucketsSuccess(const QList<MyBucket> &buckets);

    /**
     * @brief 获取对象列表成功时的处理函数
     * @param objects 对象列表
     */
    void onObjectsSuccess(const QList<MyObject> &objects);

    /**
     * @brief 显示传输界面
     */
    void showTransfer();

    /**
     * @brief 处理错误信息
     * @param api API编号
     * @param msg 错误信息
     * @param req 请求的JSON值
     */
    void onError(int api, const QString &msg, const QJsonValue &req);

private:
    // 指向Ui::UiMain的指针，用于访问UI元素
    Ui::UiMain *ui;

    // 指向UiTransfer的指针，用于管理传输界面，默认为nullptr
    UiTransfer *m_transfer = nullptr;
};

#endif // UIMAIN_H
