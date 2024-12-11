#ifndef UIPUSHBUTTON_H
#define UIPUSHBUTTON_H

// 包含必要的Qt头文件
#include <QPushButton>  // 包含Qt的按钮类

// 定义UiPushButton类，继承自QPushButton
class UiPushButton : public QPushButton
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    UiPushButton(QWidget *parent = nullptr);

protected:
    /**
     * @brief 鼠标进入事件处理函数
     * @param event 事件指针
     * 当鼠标进入按钮区域时，会触发此事件
     */
    virtual void enterEvent(QEvent *event);

    /**
     * @brief 鼠标离开事件处理函数
     * @param event 事件指针
     * 当鼠标离开按钮区域时，会触发此事件
     */
    virtual void leaveEvent(QEvent *event);
};

#endif // UIPUSHBUTTON_H
