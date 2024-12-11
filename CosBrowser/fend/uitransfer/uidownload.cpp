#include "uidownload.h"
#include "config/common.h"
#include "ui_uidownload.h"
#include "fend/uicom/uiprogresswidget.h"
#include "fend/uidelegates/uitableitemdelegate.h"

// UiDownload 构造函数
UiDownload::UiDownload(QWidget *parent) : QWidget(parent), ui(new Ui::UiDownload)
{
    ui->setupUi(this);  // 初始化界面组件

    initHeader();  // 初始化表格表头

    // 连接信号和槽函数
    connect(MG->mSignal, &ManSignals::startDownload, this, &UiDownload::onStartDownload);
    connect(MG->mSignal, &ManSignals::downloadProcess, this, &UiDownload::onDownloadProcess);
    connect(MG->mSignal, &ManSignals::downloadSuccess, this, &UiDownload::onDownloadSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiDownload::onError);

    // 设置表格项代理
    ui->tableWidget->setItemDelegate(new UiTableItemDelegate(ui->tableWidget));
}

// UiDownload 析构函数
UiDownload::~UiDownload()
{
    delete ui;  // 释放界面组件
}

// 槽函数：处理开始下载信号
void UiDownload::onStartDownload(const QString &jobId, const QString &key, const QString &localPath, qulonglong total)
{
    ui->tableWidget->insertRow(0);  // 在表格顶部插入新行
    ui->tableWidget->setRowHeight(0, 40);  // 设置新行的高度

    // 创建并设置表格项
    QTableWidgetItem *item = new QTableWidgetItem(key);
    item->setData(Qt::UserRole, jobId);  // 将 jobId 存储在 UserRole 中
    ui->tableWidget->setItem(0, 0, item);  // 设置第一列（云端路径）
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(localPath));  // 设置第二列（本地路径）

    // 创建进度条控件
    UiProgressWidget *bar = new UiProgressWidget();
    bar->setRange(0, total);  // 设置进度条范围
    ui->tableWidget->setCellWidget(0, 2, bar);  // 将进度条放置在第三列
}

// 槽函数：处理下载进度信号
void UiDownload::onDownloadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize)
{
    UiProgressWidget *w = findTableWidgetItem(jobId);  // 查找对应的进度条控件
    w->setValue(transferedSize);  // 更新进度条值
}

// 槽函数：处理下载成功信号
void UiDownload::onDownloadSuccess(const QString &jobId)
{
    UiProgressWidget *w = findTableWidgetItem(jobId);  // 查找对应的进度条控件
    w->setFinished(STR("下载成功"));  // 设置进度条为完成状态，并显示&ldquo;下载成功&rdquo;
}

// 槽函数：处理错误信号
void UiDownload::onError(int api, const QString &msg, const QJsonValue &req)
{
    if (api != API::OBJECTS::GET)
    {
        return;  // 如果不是 GET 请求，直接返回
    }

    UiProgressWidget *w = findTableWidgetItem(req["jobId"].toString());  // 查找对应的进度条控件
    w->setError(STR("下载失败"));  // 设置进度条为错误状态，并显示&ldquo;下载失败&rdquo;
    w->setToolTip(msg);  // 设置工具提示信息为错误消息
}

// 函数：根据 jobId 查找对应的 UiProgressWidget
UiProgressWidget *UiDownload::findTableWidgetItem(const QString &jobId)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);  // 获取第一列的表格项
        QString itemId = item->data(Qt::UserRole).toString();  // 获取存储的 jobId
        if (itemId == jobId)
        {
            return dynamic_cast<UiProgressWidget *>(ui->tableWidget->cellWidget(i, 2));  // 返回对应的进度条控件
        }
    }

    return nullptr;  // 如果未找到，返回 nullptr
}

// 函数：初始化表格表头
void UiDownload::initHeader()
{
    QStringList headers;
    headers << STR("云端路径") << STR("本地路径") << STR("下载状态");  // 定义表头文本
    ui->tableWidget->setColumnCount(headers.size());  // 设置列数
    ui->tableWidget->setHorizontalHeaderLabels(headers);  // 设置表头标签
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);  // 使最后一列自适应宽度
}
