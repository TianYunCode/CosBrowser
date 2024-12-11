#ifndef UICREATEBUCKETDIALOG_H
#define UICREATEBUCKETDIALOG_H

// 包含Qt的QWidget类头文件
#include <QWidget>

// 包含自定义的UiQosDialog头文件
#include "fend/uicom/uiqosdialog.h"

// 包含自定义的CloudModels头文件
#include "middle/models/cloudmodels.h"

// 定义Ui命名空间
namespace Ui
{
class UiCreateBucketDialog;
}

// 定义UiCreateBucketDialog类，继承自UiQosDialog
class UiCreateBucketDialog : public UiQosDialog
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiCreateBucketDialog(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiCreateBucketDialog();

    /**
     * @brief 获取创建的存储桶对象
     * @return 存储桶对象
     */
    MyBucket getBucket();

private:
    // 指向Ui::UiCreateBucketDialog的指针，用于访问UI元素
    Ui::UiCreateBucketDialog *ui;
};

#endif // UICREATEBUCKETDIALOG_H
