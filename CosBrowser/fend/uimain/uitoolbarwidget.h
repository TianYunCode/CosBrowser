#ifndef UITOOLBARWIDGET_H
#define UITOOLBARWIDGET_H

// 包含QWidget类头文件
#include <QWidget>

// 定义Ui命名空间
namespace Ui
{
class UiToolBarWidget;
}

// 定义UiToolBarWidget类，继承自QWidget
class UiToolBarWidget : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiToolBarWidget(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiToolBarWidget();

private slots:
    /**
     * @brief 处理btnQuit按钮点击事件
     */
    void on_btnQuit_clicked();

private:
    // 指向Ui::UiToolBarWidget的指针，用于访问UI元素
    Ui::UiToolBarWidget *ui;
};

#endif // UITOOLBARWIDGET_H
