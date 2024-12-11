#include <QFileInfo>

#include "uiupload.h"
#include "config/common.h"
#include "ui_uiupload.h"
#include "fend/uicom/uiprogresswidget.h"
#include "fend/uidelegates/uitableitemdelegate.h"

// UiUpload 构造函数
UiUpload::UiUpload(QWidget *parent) : QWidget(parent), ui(new Ui::UiUpload)
{
    ui->setupUi(this);  // 初始化界面组件

    initHeader();  // 初始化表格头

    // 连接信号和槽
    connect(MG->mSignal, &ManSignals::startUpload, this, &UiUpload::onStartUpload);
    connect(MG->mSignal, &ManSignals::uploadProcess, this, &UiUpload::onUploadProcess);
    connect(MG->mSignal, &ManSignals::uploadSuccess, this, &UiUpload::onUploadSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiUpload::onError);

    // 设置表格项委托
    ui->tableWidget->setItemDelegate(new UiTableItemDelegate(ui->tableWidget));
}

// UiUpload 析构函数
UiUpload::~UiUpload()
{
    delete ui;  // 释放界面组件
}

// 处理开始上传信号的槽函数
void UiUpload::onStartUpload(const QString &jobId, const QString &key, const QString &localPath)
{
    ui->tableWidget->insertRow(0);  // 在表格顶部插入一行
    ui->tableWidget->setRowHeight(0, 40);  // 设置新行的高度为 40 像素

    QTableWidgetItem *item = new QTableWidgetItem(key);  // 创建一个表格项，显示云端路径
    item->setData(Qt::UserRole, jobId);  // 将 jobId 存储在表格项的 UserRole 中
    ui->tableWidget->setItem(0, 0, item);  // 将表格项放置在第 0 行第 0 列

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(localPath));  // 创建并放置本地路径的表格项

    QFileInfo info(localPath);  // 获取本地文件信息
    UiProgressWidget *bar = new UiProgressWidget();  // 创建进度条部件
    bar->setRange(0, info.size());  // 设置进度条的范围为文件大小
    ui->tableWidget->setCellWidget(0, 2, bar);  // 将进度条部件放置在第 0 行第 2 列
}

// 处理上传进度信号的槽函数
void UiUpload::onUploadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize)
{
    UiProgressWidget *w = findTableWidgetItem(jobId);  // 根据 jobId 查找对应的进度条部件
    w->setValue(transferedSize);  // 更新进度条的当前值
}

// 处理上传成功信号的槽函数
void UiUpload::onUploadSuccess(const QString &jobId)
{
    UiProgressWidget *w = findTableWidgetItem(jobId);  // 根据 jobId 查找对应的进度条部件
    w->setFinished(STR("上传成功"));  // 设置进度条为完成状态，并显示&ldquo;上传成功&rdquo;
}

// 处理错误信号的槽函数
void UiUpload::onError(int api, const QString &msg, const QJsonValue &req)
{
    if (api != API::OBJECTS::PUT)
    {
        return;  // 如果不是 PUT 请求，则忽略
    }

    UiProgressWidget *w = findTableWidgetItem(req["jobId"].toString());  // 根据 jobId 查找对应的进度条部件
    w->setError(STR("上传失败"));  // 设置进度条为错误状态，并显示&ldquo;上传失败&rdquo;
    w->setToolTip(msg);  // 设置工具提示为错误消息
}

// 根据 jobId 查找对应的进度条部件
UiProgressWidget *UiUpload::findTableWidgetItem(const QString &jobId)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);  // 获取第 i 行第 0 列的表格项
        QString itemId = item->data(Qt::UserRole).toString();  // 获取表格项中存储的 jobId
        if (itemId == jobId)
        {
            return dynamic_cast<UiProgressWidget *>(ui->tableWidget->cellWidget(i, 2));  // 返回对应的进度条部件
        }
    }

    return nullptr;  // 如果未找到对应的进度条部件，返回 nullptr
}

// 初始化表格头
void UiUpload::initHeader()
{
    QStringList headers;
    headers << STR("云端路径") << STR("本地路径") << STR("上传状态");  // 定义表格头标签
    ui->tableWidget->setColumnCount(headers.size());  // 设置表格列数
    ui->tableWidget->setHorizontalHeaderLabels(headers);  // 设置水平表头标签
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);  // 使最后一列自动扩展以填充可用空间
}
