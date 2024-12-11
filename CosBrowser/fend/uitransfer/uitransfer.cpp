#include "uitransfer.h"
#include "config/common.h"
#include "ui_uitransfer.h"

// UiTransfer 构造函数
UiTransfer::UiTransfer(QWidget *parent) : UiQosDialog(parent), ui(new Ui::UiTransfer)
{
    ui->setupUi(body());  // 初始化界面组件

    setTitle(STR("传输列表"));  // 设置对话框标题为&ldquo;传输列表&rdquo;

    setFixedSize(600, 450);  // 设置对话框的固定大小为 600x450 像素
}

// UiTransfer 析构函数
UiTransfer::~UiTransfer()
{
    delete ui;  // 释放界面组件
}
