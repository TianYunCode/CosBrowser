#ifndef UITRANSFER_H
#define UITRANSFER_H

// 包含QWidget类头文件
#include <QWidget>

// 包含自定义的UiQosDialog类头文件
#include "fend/uicom/uiqosdialog.h"

// 定义Ui命名空间
namespace Ui
{
class UiTransfer;
}

// 定义UiTransfer类，继承自UiQosDialog
class UiTransfer : public UiQosDialog
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiTransfer(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiTransfer();

private:
    // 指向Ui::UiTransfer的指针，用于访问UI元素
    Ui::UiTransfer *ui;
};

#endif // UITRANSFER_H
