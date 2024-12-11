#include "uicreatebucketdialog.h"
#include "ui_uicreatebucketdialog.h"

// UiCreateBucketDialog 构造函数
UiCreateBucketDialog::UiCreateBucketDialog(QWidget *parent) : UiQosDialog(parent), ui(new Ui::UiCreateBucketDialog)
{
    ui->setupUi(body());  // 初始化界面组件
    ui->btnOk->setProperty("style_button", "main");  // 设置确认按钮的样式

    // 连接确认按钮的点击信号到接受对话框的槽
    connect(ui->btnOk, &QPushButton::clicked, this, &UiCreateBucketDialog::accept);

    // 连接取消按钮的点击信号到拒绝对话框的槽
    connect(ui->btnCancel, &QPushButton::clicked, this, &UiCreateBucketDialog::reject);
}

// UiCreateBucketDialog 析构函数
UiCreateBucketDialog::~UiCreateBucketDialog()
{
    delete ui;  // 释放界面组件
}

// 获取用户输入的桶信息
MyBucket UiCreateBucketDialog::getBucket()
{
    MyBucket bucket;

    // 获取输入的桶名称并去除前后空格
    bucket.name = ui->lineName->text().trimmed();

    // 获取输入的桶位置并去除前后空格
    bucket.location = ui->lineLocation->text().trimmed();

    return bucket;  // 返回桶信息
}
