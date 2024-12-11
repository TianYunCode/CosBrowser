#include <QMessageBox>
#include "qpushbutton.h"

#include "uimain.h"
#include "ui_uimain.h"
#include "config/common.h"
#include "fend/uicom/uimessagebox.h"
#include "fend/uitransfer/uitransfer.h"

// UiMain 构造函数
UiMain::UiMain(QWidget *parent) : UiQosDialog(parent), ui(new Ui::UiMain)
{
    ui->setupUi(body());  // 初始化界面组件

    // 设置分割器的拉伸因子，第一个子部件拉伸因子为1，第二个子部件拉伸因子为4
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 4);

    // 添加传输按钮，并设置其点击事件处理函数
    QPushButton *transBtn = addButton(GLOBAL::PATH::TRANS, GLOBAL::PATH::TRANS_HOVER);
    connect(transBtn, &QPushButton::clicked, this, &UiMain::showTransfer);

    // 添加退出按钮，并设置其点击事件处理函数
    QPushButton *quitBtn = addButton(GLOBAL::PATH::QUIT, GLOBAL::PATH::QUIT_HOVER);
    connect(quitBtn, &QPushButton::clicked, MG->mSignal, &ManSignals::unLogin);

    addTitleLine();  // 添加标题线

    // 添加最小化按钮
    addMinButton(GLOBAL::PATH::MIN_PATH, GLOBAL::PATH::MIN_HOVER_PATH);

    // 添加最大化/还原按钮
    addMaxButton(GLOBAL::PATH::MAX_PATH, GLOBAL::PATH::MAX_HOVER_PATH, GLOBAL::PATH::NORMAL_PATH, GLOBAL::PATH::NORMAL_HOVER_PATH);

    setTitle(STR("Qos Browser"));  // 设置窗口标题
    resize(1080, 640);  // 设置窗口大小
    setKeyDisabled();  // 禁用ESC或回车键关闭窗口

    // 连接信号与槽函数
    connect(MG->mSignal, &ManSignals::loginSuccess, this, &UiMain::show);
    connect(MG->mSignal, &ManSignals::unLogin, this, &UiMain::onUnLogin);
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &UiMain::onBucketsSuccess);
    connect(MG->mSignal, &ManSignals::objectsSuccess, this, &UiMain::onObjectsSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiMain::onError);

    m_transfer = new UiTransfer(this);  // 创建传输界面实例
}

// UiMain 析构函数
UiMain::~UiMain()
{
    delete ui;  // 释放界面组件
}

// 处理未登录事件
void UiMain::onUnLogin()
{
    hide();  // 隐藏窗口
}

// 处理桶列表成功加载事件
void UiMain::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    ui->stackedWidget->setCurrentIndex(0);  // 切换到第一个页面
}

// 处理对象列表成功加载事件
void UiMain::onObjectsSuccess(const QList<MyObject> &objects)
{
    ui->stackedWidget->setCurrentIndex(1);  // 切换到第二个页面
}

// 显示传输界面
void UiMain::showTransfer()
{
    m_transfer->show();  // 显示传输界面
}

// 处理错误事件
void UiMain::onError(int api, const QString &msg, const QJsonValue &req)
{
    // 如果窗口可见且错误API大于基础API，显示错误消息
    if (isVisible() && api > API::BUCKETS::BASE)
    {
        UiMessageBox().showMessage(STR("错误"), msg);
    }
}
