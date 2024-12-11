#ifndef UIQOSDIALOG_H
#define UIQOSDIALOG_H

// 包含基类对话框的头文件
#include "uibasedialog.h"

// 命名空间Ui，用于定义UiQosDialog类
namespace Ui
{
class UiQosDialog;
}

// 定义UiQosDialog类，继承自UiBaseDialog
class UiQosDialog : public UiBaseDialog
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiQosDialog(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiQosDialog();

private:
    /**
     * @brief 指向UiQosDialog的用户界面对象
     * 该指针用于访问和操作对话框的用户界面元素
     */
    Ui::UiQosDialog *ui;
};

#endif // UIQOSDIALOG_H
