#include <QStandardItemModel>  // 包含QStandardItemModel类，用于管理列表视图的数据模型
#include <QJsonObject>         // 包含QJsonObject类，用于处理JSON对象

#include "uibucketslistwidget.h"  // 包含UiBucketsListWidget类的定义
#include "config/common.h"        // 包含一些通用的配置和定义
#include "ui_uibucketslistwidget.h"  // 包含UiBucketsListWidget的UI定义

// UiBucketsListWidget类的构造函数
UiBucketsListWidget::UiBucketsListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UiBucketsListWidget)
{
    // 设置UI界面
    ui->setupUi(this);

    // 设置列表视图的模型为存储桶模型
    ui->listView->setModel(MG->mModels->modelBuckets());

    // 连接存储桶成功信号到槽函数onBucketsSuccess
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &UiBucketsListWidget::onBucketsSuccess);

    // 连接输入框的选中信号到槽函数showBucketObjects
    connect(ui->lineEdit, &UiComboLine::itemSelected, this, &UiBucketsListWidget::showBucketObjects);

    // 连接输入框的文本编辑信号到槽函数onTextEdited
    connect(ui->lineEdit, &UiComboLine::textEdited, this, &UiBucketsListWidget::onTextEdited);
}

// UiBucketsListWidget类的析构函数
UiBucketsListWidget::~UiBucketsListWidget()
{
    // 释放UI资源
    delete ui;
}

// 处理存储桶成功事件的槽函数
void UiBucketsListWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    QStringList words;
    // 遍历存储桶列表，将存储桶名称添加到字符串列表中
    for (const auto &bucket : qAsConst(buckets))
    {
        words.append(bucket.name);
    }

    // 设置输入框的自动补全列表
    ui->lineEdit->setWords(words);
}

// 处理列表视图的双击事件的槽函数
void UiBucketsListWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    // 显示选中的存储桶对象
    showBucketObjects(index.data().toString());
}

// 显示存储桶对象的槽函数
void UiBucketsListWidget::showBucketObjects(const QString &bucketName)
{
    // 创建请求参数的JSON对象
    QJsonObject params;
    params["bucketName"] = bucketName;
    params["dir"] = "";

    // 发送获取存储桶对象的请求
    MG->mGate->send(API::OBJECTS::LIST, params);
}

// 处理输入框文本编辑事件的槽函数
void UiBucketsListWidget::onTextEdited(const QString &text)
{
    // 获取存储桶模型
    QStandardItemModel *model = MG->mModels->modelBuckets();

    // 遍历模型中的每一行
    for (int i = 0; i < model->rowCount(); ++i)
    {
        // 判断当前行的数据是否包含输入的文本
        bool hidden = !(model->index(i, 0).data().toString().contains(text));

        // 设置当前行是否隐藏
        ui->listView->setRowHidden(i, hidden);
    }
}
