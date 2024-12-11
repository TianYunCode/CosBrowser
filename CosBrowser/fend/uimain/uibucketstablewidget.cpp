#include <QStandardItemModel>
#include <QJsonObject>
#include <QAction>
#include <QMessageBox>

#include "fend/uidelegates/uitableitemdelegate.h"
#include "uibucketstablewidget.h"
#include "ui_uibucketstablewidget.h"
#include "uicreatebucketdialog.h"
#include "config/common.h"

// UiBucketsTableWidget 构造函数
UiBucketsTableWidget::UiBucketsTableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UiBucketsTableWidget)
{
    ui->setupUi(this);  // 初始化界面组件
    ui->tableView->setModel(MG->mModels->modelBuckets());  // 设置表格模型

    // 设置列宽度
    ui->tableView->setColumnWidth(0, 200);  // 第一列宽度为200像素
    ui->tableView->setColumnWidth(1, 120);  // 第二列宽度为120像素
    ui->tableView->horizontalHeader()->setStretchLastSection(true);  // 最后一列自动拉伸填充剩余空间

    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);

    // 启用鼠标点击排序
    ui->tableView->setSortingEnabled(true);

    // 初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 10 << 50 << 100);  // 设置每页显示的最大行数列表
    connect(ui->widgetPage, &UiPageWidget::pageNumChanged, this, &UiBucketsTableWidget::onPageNumChanged);  // 连接分页按钮的信号和槽

    // 连接信号和槽，处理桶数据成功接收后的操作
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &UiBucketsTableWidget::onBucketsSuccess);

    // 添加右键菜单项
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *delAction = new QAction(QString::fromLocal8Bit("删除"), this);
    connect(delAction, &QAction::triggered, this, &UiBucketsTableWidget::onDelBucket);
    ui->tableView->addAction(delAction);

    // 设置单元格委托
    ui->tableView->setItemDelegate(new UiTableItemDelegate(ui->tableView));

    // 设置按钮样式
    ui->btnCreateBucket->setProperty("style_button", "main");
}

// UiBucketsTableWidget 析构函数
UiBucketsTableWidget::~UiBucketsTableWidget()
{
    delete ui;
}

// 双击事件处理函数
void UiBucketsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        // 获取桶名称并发送请求
        QJsonObject params;
        params["bucketName"] = index.data().toString();
        params["dir"] = "";
        MG->mGate->send(API::OBJECTS::LIST, params);
    }
}

// 桶数据成功接收后的处理函数
void UiBucketsTableWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    // 更新总行数
    ui->widgetPage->setTotalRow(buckets.size());

    // 设置行高
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for (int i = 0; i < model->rowCount(); ++i)
    {
        ui->tableView->setRowHeight(i, 40);
    }
}

// 分页按钮的页码改变时的处理函数
void UiBucketsTableWidget::onPageNumChanged(int start, int maxLen)
{
    // 根据页码设置行隐藏状态
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for (int i = 0; i < model->rowCount(); ++i)
    {
        bool hidden = (i < start || i >= (start + maxLen));
        ui->tableView->setRowHidden(i, hidden);
    }
}

// 创建桶按钮点击事件处理函数
void UiBucketsTableWidget::on_btnCreateBucket_clicked()
{
    UiCreateBucketDialog dialog(this);
    int ret = dialog.exec();

    if (ret == QDialog::Accepted)
    {
        // 获取对话框中的桶信息
        MyBucket bucket = dialog.getBucket();

        if (bucket.isValid())
        {
            // 发送创建桶请求
            QJsonObject params;
            params["bucketName"] = bucket.name;
            params["location"] = bucket.location;
            MG->mGate->send(API::BUCKETS::PUT, params);
        }
    }
}

// 删除桶按钮点击事件处理函数
void UiBucketsTableWidget::onDelBucket()
{
    QModelIndex idx = ui->tableView->currentIndex();

    if (idx.isValid())
    {
        QString name = idx.data().toString();

        // 显示确认对话框
        QMessageBox box(QMessageBox::Question, QString::fromLocal8Bit("删除桶"),
                        QString::fromLocal8Bit("是否确认删除桶【%1】吗？").arg(name),
                        QMessageBox::Yes | QMessageBox::No);

        box.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit("删除"));
        box.setButtonText(QMessageBox::No, QString::fromLocal8Bit("取消"));

        int ret = box.exec();

        if (ret == QMessageBox::Yes)
        {
            // 发送删除桶请求
            QJsonObject params;
            params["bucketName"] = name;
            MG->mGate->send(API::BUCKETS::DEL, params);
        }
    }
}

// 刷新按钮点击事件处理函数
void UiBucketsTableWidget::on_btnRefresh_clicked()
{
    MG->mGate->send(API::BUCKETS::LIST);  // 发送刷新请求
}
