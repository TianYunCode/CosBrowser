#ifndef UIPROGRESSWIDGET_H
#define UIPROGRESSWIDGET_H

// 包含必要的Qt头文件
#include <QElapsedTimer>  // 用于测量时间
#include <QWidget>        // 包含Qt的窗口基类

// 定义Ui命名空间
namespace Ui
{
class UiProgressWidget;
}

// 定义UiProgressWidget类，继承自QWidget
class UiProgressWidget : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiProgressWidget(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiProgressWidget();

    /**
     * @brief 设置进度条的范围
     * @param minValue 最小值
     * @param maxValue 最大值
     */
    void setRange(qulonglong minValue, qulonglong maxValue);

    /**
     * @brief 设置当前进度值
     * @param value 当前进度值
     */
    void setValue(qulonglong value);

    /**
     * @brief 停止进度条
     */
    void stop();

    /**
     * @brief 设置进度条为完成状态，并显示完成消息
     * @param msg 完成消息
     */
    void setFinished(const QString &msg);

    /**
     * @brief 设置进度条为错误状态，并显示错误消息
     * @param msg 错误消息
     */
    void setError(const QString &msg);

private:
    Ui::UiProgressWidget *ui;  // UI指针，用于访问UI元素
    QElapsedTimer m_time;      // 用于测量时间的计时器
};

#endif // UIPROGRESSWIDGET_H
