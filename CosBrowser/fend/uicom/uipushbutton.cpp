#include "uipushbutton.h"

// 构造函数，初始化按钮并设置父窗口
UiPushButton::UiPushButton(QWidget *parent) : QPushButton(parent)
{
    // 调用父类QPushButton的构造函数，并传递父窗口指针
}

// 鼠标进入按钮区域时的事件处理函数
void UiPushButton::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor); // 设置鼠标指针为手型，表示按钮可点击
}

// 鼠标离开按钮区域时的事件处理函数
void UiPushButton::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor); // 恢复鼠标指针为默认的箭头形状
}
