#include <QKeyEvent>

#include "uilineedit.h"

// UiLineEdit 类构造函数，接受一个父窗口部件参数
UiLineEdit::UiLineEdit(QWidget *parent) : QLineEdit(parent)
{
}

// 重写 keyPressEvent 函数，处理按键事件
void UiLineEdit::keyPressEvent(QKeyEvent *event)
{
    // 检查是否按下了 Ctrl 键
    if (event->modifiers() == Qt::ControlModifier)
    {
        // 检查是否按下了 C 或 V 键
        if (event->key() == Qt::Key_C || event->key() == Qt::Key_V)
        {
            // 如果按下了 Ctrl+C 或 Ctrl+V，直接返回，不做任何处理
            return;
        }
    }

    // 如果不是 Ctrl+C 或 Ctrl+V，调用 QLineEdit 的 keyPressEvent 函数处理其他按键事件
    QLineEdit::keyPressEvent(event);
}
