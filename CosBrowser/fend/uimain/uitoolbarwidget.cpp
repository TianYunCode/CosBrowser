#include <QFileDialog>
#include <QSignalMapper>
#include <QJsonObject>
#include <QInputDialog>

#include "uitoolbarwidget.h"
#include "config/common.h"
#include "ui_uitoolbarwidget.h"

// UiToolBarWidget 构造函数
UiToolBarWidget::UiToolBarWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UiToolBarWidget)
{
    ui->setupUi(this);  // 初始化界面组件
}

// UiToolBarWidget 析构函数
UiToolBarWidget::~UiToolBarWidget()
{
    delete ui;  // 释放界面组件
}

// 槽函数：处理&ldquo;退出&rdquo;按钮点击事件
void UiToolBarWidget::on_btnQuit_clicked()
{
    emit MG->mSignal->unLogin();  // 发送注销登录信号
}
