#ifndef UILINEEDIT_H
#define UILINEEDIT_H

// 包含必要的Qt头文件
#include <QLineEdit>

// 定义UiLineEdit类，继承自QLineEdit
class UiLineEdit : public QLineEdit
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    UiLineEdit(QWidget *parent = nullptr);

protected:
    /**
     * @brief 键盘按键事件处理函数
     * @param event 键盘事件
     */
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // UILINEEDIT_H
