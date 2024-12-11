#ifndef UIMESSAGEBOX_H
#define UIMESSAGEBOX_H

// 包含必要的Qt头文件
#include <QWidget>

// 包含自定义的对话框基类头文件
#include "uiqosdialog.h"

// 定义Ui命名空间
namespace Ui
{
class UiMessageBox;
}

// 定义UiMessageBox类，继承自UiQosDialog
class UiMessageBox : public UiQosDialog
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiMessageBox(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiMessageBox();

    /**
     * @brief 显示消息框
     * @param title 消息框的标题
     * @param text 消息框的文本内容
     * @param btnTextList 按钮文本列表，默认为包含一个&ldquo;确定&rdquo;按钮的QStringList
     * @return 用户点击的按钮文本
     */
    QString showMessage(const QString &title, const QString &text, const QStringList &btnTextList = QStringList(QString::fromLocal8Bit("确定")));

private:
    /**
     * @brief 创建按钮
     * @param textList 按钮文本列表
     */
    void createBtns(const QStringList &textList);

private:
    Ui::UiMessageBox *ui;  // UI指针，用于访问UI元素
    QString m_text;        // 消息框的文本内容
};

#endif // UIMESSAGEBOX_H
