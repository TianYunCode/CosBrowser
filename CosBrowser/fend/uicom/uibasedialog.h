#ifndef UIBASEDIALOG_H
#define UIBASEDIALOG_H

// 包含必要的Qt头文件
#include <QDialog>

// 开始Qt命名空间
QT_BEGIN_NAMESPACE

// 定义Ui命名空间
namespace Ui
{
class UiBaseDialog;
}

// 结束Qt命名空间
QT_END_NAMESPACE

// 定义UiBaseDialog类，继承自QDialog
class UiBaseDialog : public QDialog
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    // 构造函数，允许指定父窗口
    UiBaseDialog(QWidget *parent = nullptr);

    // 析构函数
    ~UiBaseDialog();

    /**
     * @brief 设置对话框的标题
     * @param title 标题文本
     */
    void setTitle(const QString &title);

    /**
     * @brief 设置对话框的logo
     * @param path logo图片路径
     */
    void setLogo(const QString &path);

    /**
     * @brief 添加最小化按钮
     * @param path 按钮图片路径
     * @param hoverPath 按钮悬浮图片路径
     */
    void addMinButton(const QString &path, const QString &hoverPath);

    /**
     * @brief 添加最大化按钮
     * @param maxPath 最大化按钮图片路径
     * @param maxPathHover 最大化按钮悬浮图片路径
     * @param normalPath 还原按钮图片路径
     * @param normalPathHover 还原按钮悬浮图片路径
     */
    void addMaxButton(const QString &maxPath, const QString &maxPathHover, const QString &normalPath, const QString &normalPathHover);

    /**
     * @brief 添加一个新的按钮
     * @param path 按钮图片路径
     * @param hoverPath 按钮悬浮图片路径
     * @return 新增的按钮指针
     */
    QPushButton *addButton(const QString &path, const QString &hoverPath);

    /**
     * @brief 设置按钮图片
     * @param btn 按钮指针
     * @param path 按钮图片路径
     * @param hoverPath 按钮悬浮图片路径
     */
    void setButtonImage(QPushButton *btn, const QString &path, const QString &hoverPath);

    /**
     * @brief 设置所有按钮为统一大小
     * @param w 大小
     */
    void setAllButtonSize(int w = 20);

    /**
     * @brief 禁用键盘事件
     */
    void setKeyDisabled();

    /**
     * @brief 添加标题栏分割线
     * @param w 宽度
     */
    void addTitleLine(int w = 2);

protected:
    // 鼠标按下事件处理函数
    void mousePressEvent(QMouseEvent *event);

    // 鼠标移动事件处理函数
    void mouseMoveEvent(QMouseEvent *event);

    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event);

    // 获取对话框的主体部分
    QWidget *body();

private:
    // 添加关闭按钮
    void addCloseButton(const QString &path, const QString &hoverPath);

    // 添加一个QWidget到对话框
    void addWidget(QWidget *w);

protected:
    Ui::UiBaseDialog *m_ui;  // 指向UiBaseDialog的用户界面指针

private:
    QPoint m_start;  // 鼠标按下时的起始点
    int m_sz = 20;   // 按钮的默认大小
};

#endif // UIBASEDIALOG_H
