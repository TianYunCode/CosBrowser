#ifndef UILOGINDIALOG_H
#define UILOGINDIALOG_H

// 包含自定义的UiQosDialog头文件
#include "fend/uicom/uiqosdialog.h"

// 使用Qt的命名空间
QT_BEGIN_NAMESPACE

// 定义Ui命名空间
namespace Ui
{
class UiLoginDialog;
}

QT_END_NAMESPACE

// 定义UiLoginDialog类，继承自UiQosDialog
class UiLoginDialog : public UiQosDialog
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    UiLoginDialog(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiLoginDialog();

    /**
     * @brief 更新登录信息
     */
    void updateLoginInfo();

protected:
    /**
     * @brief 重写eventFilter方法，用于事件过滤
     * @param watched 被监视的对象
     * @param event 事件对象
     * @return 如果事件被处理，返回true；否则返回false
     */
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    /**
     * @brief 处理登录按钮点击事件
     */
    void onBtnLoginClicked();

    /**
     * @brief 处理登录成功事件
     */
    void onLoginSucceed();

    /**
     * @brief 处理登录错误事件
     * @param api 错误相关的API编号
     * @param msg 错误信息
     * @param req 请求的JSON数据
     */
    void onLoginError(int api, const QString &msg, const QJsonValue &req);

private:
    // 指向Ui::UiLoginDialog的指针，用于访问UI元素
    Ui::UiLoginDialog *ui;
};

#endif // UILOGINDIALOG_H
