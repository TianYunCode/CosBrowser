#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QCompleter>
#include <QJsonObject>

#include "uilogindialog.h"
#include "bend/man/mandb.h"
#include "config/common.h"
#include "ui_uilogindialog.h"

// 构造函数，初始化登录对话框
UiLoginDialog::UiLoginDialog(QWidget *parent) : UiQosDialog(parent), ui(new Ui::UiLoginDialog)
{
    // 设置UI界面
    ui->setupUi(body());

    // 设置对话框标题
    setTitle(STR("登录"));

    // 设置登录按钮为默认按钮
    ui->btnLogin->setDefault(true);

    // 设置标签的字体样式
    ui->labelLoginName->setProperty("style_font", "h5");
    ui->labelSecretId->setProperty("style_font", "h5");
    ui->labelSecretKey->setProperty("style_font", "h5");
    ui->labelRemark->setProperty("style_font", "h5");

    // 设置登录按钮的字体样式和按钮样式
    ui->btnLogin->setProperty("style_font", "h5");
    ui->btnLogin->setProperty("style_button", "main");

    // 连接登录按钮的点击信号到槽函数
    connect(ui->btnLogin, &QPushButton::clicked, this, &UiLoginDialog::onBtnLoginClicked);

    // 连接登录成功信号到槽函数
    connect(MG->mSignal, &ManSignals::loginSuccess, this, &UiLoginDialog::onLoginSucceed);

    // 连接未登录信号到槽函数
    connect(MG->mSignal, &ManSignals::unLogin, this, &UiLoginDialog::show);

    // 连接登录错误信号到槽函数
    connect(MG->mSignal, &ManSignals::error, this, &UiLoginDialog::onLoginError);

    // 更新登录信息
    updateLoginInfo();

    // 设置对话框的大小
    resize(400, 450);
}

// 析构函数，释放UI资源
UiLoginDialog::~UiLoginDialog()
{
    delete ui;
}

// 更新登录信息
void UiLoginDialog::updateLoginInfo()
{
    // 获取登录名称列表
    QStringList words = MG->mDb->loginNameList();

    // 设置登录名称输入框的自动补全列表
    ui->lineLoginName->setWords(words);

    // 连接登录名称输入框的选中信号到槽函数
    connect(ui->lineLoginName, &UiComboLine::itemSelected,
            [=](const QString &name)
            {
                // 根据选中的登录名称获取登录信息
                LoginInfo info = MG->mDb->loginInfoByName(name);

                // 设置密钥ID、密钥和备注信息
                ui->lineSecretId->setText(info.secret_id);
                ui->lineSecretKey->setText(info.secret_key);
                ui->lineRemark->setText(info.remark);

                // 设置保存登录信息复选框为选中状态
                ui->checkSaveSection->setChecked(true);
            });
}

// 事件过滤器，处理特定控件的事件
bool UiLoginDialog::eventFilter(QObject *watched, QEvent *event)
{
    // 如果关注的控件是密钥输入框
    if (watched == ui->lineSecretKey)
    {
        // 如果事件类型是按键事件
        if (event->type() == QEvent::KeyPress)
        {
            // 获取按键事件
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

            // 如果按下了Ctrl键
            if (keyEvent->modifiers() == Qt::ControlModifier)
            {
                // 如果按下了C或V键（复制或粘贴）
                if (keyEvent->key() == Qt::Key_C || keyEvent->key() == Qt::Key_V)
                {
                    return true; // 事件已经被处理，不再往下传递
                }
            }
        }
    }

    // 调用父类的事件过滤器
    return QDialog::eventFilter(watched, event);
}

// 处理登录按钮点击事件
void UiLoginDialog::onBtnLoginClicked()
{
    // 创建登录参数的JSON对象
    QJsonObject params;
    params["secretId"] = ui->lineSecretId->text().trimmed();
    params["secretKey"] = ui->lineSecretKey->text().trimmed();

    // 发送登录请求 
    MG->mGate->send(API::LOGIN::NORMAL, params);
}

// 处理登录成功事件
void UiLoginDialog::onLoginSucceed()
{
    // 如果保存登录信息复选框被选中
    if (ui->checkSaveSection->isChecked())
    {
        // 保存登录信息
        MG->mDb->saveLoginInfo(ui->lineLoginName->text(), ui->lineSecretId->text(), ui->lineSecretKey->text(), ui->lineRemark->text());

        // 更新登录信息
        updateLoginInfo();
    }
    else
    {
        // 删除登录信息
        MG->mDb->removeLoginInfo(ui->lineSecretId->text());
    }

    // 接受对话框
    accept();
}

// 处理登录错误事件
void UiLoginDialog::onLoginError(int api, const QString &msg, const QJsonValue &req)
{
    Q_UNUSED(req)

    // 如果不是登录API的错误，直接返回
    if (api != API::LOGIN::NORMAL)
    {
        return;
    }

    // 显示登录失败的警告信息
    QMessageBox::warning(this, STR("登录失败"), STR("登录失败：%1").arg(msg));
}
