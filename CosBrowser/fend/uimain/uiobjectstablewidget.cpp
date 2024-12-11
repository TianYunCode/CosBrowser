#include <QStandardItemModel>
#include <QJsonObject>
#include <QFileDialog>
#include <QMessageBox>

#include "middle/signals/mansignals.h"
#include "fend/uidelegates/uitableitemdelegate.h"
#include "bend/gateway.h"
#include "bend/man/mancloud.h"
#include "uiobjectstablewidget.h"
#include "ui_uiobjectstablewidget.h"
#include "middle/manmodels.h"
#include "middle/manglobal.h"

// UiObjectsTableWidget 构造函数
UiObjectsTableWidget::UiObjectsTableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UiObjectsTableWidget)
{
    ui->setupUi(this);  // 初始化界面组件
    ui->btnBuckets->setProperty("style_button", "main");  // 设置按钮样式属性

    // 设置表格视图的数据模型
    ui->tableView->setModel(MG->mModels->modelObjects());

    // 设置列宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); // 设置最后一列占满整个表

    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);

    // 启用鼠标点击排序功能
    ui->tableView->setSortingEnabled(true);

    // 初始化翻页控件，设置每页显示行数选项
    ui->widgetPage->setMaxRowList(QList<int>() << 10 << 50 << 100);
    connect(ui->widgetPage, &UiPageWidget::pageNumChanged, this, &UiObjectsTableWidget::onPageNumChanged);

    // 连接路径变化信号与槽函数
    connect(ui->widgetBread, &UiBreadWidget::pathChanged, this, &UiObjectsTableWidget::onPathChanged);
    connect(MG->mSignal, &ManSignals::objectsSuccess, this, &UiObjectsTableWidget::onObjectsSuccess);

    // 连接上传和下载成功的信号与槽函数
    connect(MG->mSignal, &ManSignals::uploadSuccess, this, &UiObjectsTableWidget::onUploadSuccess);
    connect(MG->mSignal, &ManSignals::downloadSuccess, this, &UiObjectsTableWidget::onDownloadSuccess);

    // 设置表格项代理
    ui->tableView->setItemDelegate(new UiTableItemDelegate(ui->tableView));
}

// UiObjectsTableWidget 析构函数
UiObjectsTableWidget::~UiObjectsTableWidget()
{
    delete ui;  // 释放界面组件
}

// 槽函数：处理&ldquo;桶&rdquo;按钮点击事件
void UiObjectsTableWidget::on_btnBuckets_clicked()
{
    MG->mGate->send(API::BUCKETS::LIST);  // 发送请求获取桶列表
}

// 槽函数：处理表格视图双击事件
void UiObjectsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    MyObject obj = index.data(Qt::UserRole).value<MyObject>();  // 获取选中的对象
    if (obj.isDir())  // 如果是目录
    {
        QJsonObject params;
        params["bucketName"] = MG->mCloud->currentBucketName();  // 设置当前桶名称
        params["dir"] = obj.key;  // 设置目录路径
        MG->mGate->send(API::OBJECTS::LIST, params);  // 发送请求获取目录下的对象列表
    }
}

// 槽函数：处理对象列表加载成功事件
void UiObjectsTableWidget::onObjectsSuccess(const QList<MyObject> &objects)
{
    QString path = MG->mCloud->currentBucketName() + "/" + MG->mCloud->currentDir();  // 获取当前路径
    ui->widgetBread->setPath(path);  // 设置面包屑路径
    ui->widgetPage->setTotalRow(objects.size());  // 设置总行数

    QStandardItemModel *model = MG->mModels->modelObjects();  // 获取数据模型
    for (int i = 0; i < model->rowCount(); ++i)
    {
        ui->tableView->setRowHeight(i, 40);  // 设置每行高度
    }
}

// 槽函数：处理路径变化事件
void UiObjectsTableWidget::onPathChanged(const QString &newPath)
{
    // newPath=file-1300416378/test/bll
    // 需要将newPath 转化为 test/bll/
    QString key = newPath + "/";
    key = key.mid(key.indexOf("/") + 1);  // 提取实际路径

    QJsonObject params;
    params["bucketName"] = MG->mCloud->currentBucketName();  // 设置当前桶名称
    params["dir"] = key;  // 设置目录路径
    MG->mGate->send(API::OBJECTS::LIST, params);  // 发送请求获取目录下的对象列表
}

// 槽函数：处理翻页变化事件
void UiObjectsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel *model = MG->mModels->modelObjects();  // 获取数据模型
    for (int i = 0; i < model->rowCount(); i++)
    {
        bool hidden = (i < start || (i >= start + maxLen));  // 计算是否隐藏
        ui->tableView->setRowHidden(i, hidden);  // 设置行的隐藏状态
    }
}

// 槽函数：处理刷新按钮点击事件
void UiObjectsTableWidget::on_btnRefresh_clicked()
{
    onPathChanged(ui->widgetBread->currentPath());  // 刷新当前路径的对象列表
}

// 槽函数：处理上传按钮点击事件
void UiObjectsTableWidget::on_btnUpload_clicked()
{
    static QString lastDir = "./";  // 记录上次选择的目录
    // 获取本地文件路径
    QString filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("上传文件"), lastDir);
    QFileInfo info(filePath);
    if (info.isFile() && info.exists())  // 检查文件是否存在
    {
        QString jobId = QUuid::createUuid().toString();  // 生成任务ID

        filePath = filePath.replace("\\\\", "/");  // 替换反斜杠为正斜杠
        QJsonObject params;
        QString key = MG->mCloud->currentDir() + info.fileName();  // 构建对象键
        params["jobId"] = jobId;
        params["bucketName"] = MG->mCloud->currentBucketName();  // 设置当前桶名称
        params["key"] = key;  // 设置对象键
        params["localPath"] = filePath;  // 设置本地文件路径
        MG->mGate->send(API::OBJECTS::PUT, params);  // 发送上传请求
        lastDir = info.dir().absolutePath();  // 更新上次选择的目录
        emit MG->mSignal->startUpload(jobId, key, filePath);  // 发送开始上传信号
    }
}

// 槽函数：处理上传成功事件
void UiObjectsTableWidget::onUploadSuccess(const QString &jobId)
{
    on_btnRefresh_clicked();  // 刷新对象列表
    showMessage(QString::fromLocal8Bit("上传文件"), QString::fromLocal8Bit("上传文件成功"));  // 显示成功消息
}

// 槽函数：处理下载成功事件
void UiObjectsTableWidget::onDownloadSuccess(const QString &jobId)
{
    showMessage(QString::fromLocal8Bit("下载文件"), QString::fromLocal8Bit("下载文件成功"));  // 显示成功消息
}

// 槽函数：处理下载按钮点击事件
void UiObjectsTableWidget::on_btnDownload_clicked()
{
    QModelIndex idx = ui->tableView->currentIndex();  // 获取当前选中的索引
    if (!idx.isValid())  // 检查索引是否有效
    {
        showMessage(QString::fromLocal8Bit("下载文件"), QString::fromLocal8Bit("请选择要下载的文件"));  // 显示提示信息
        return;
    }

    MyObject obj = idx.data(Qt::UserRole).value<MyObject>();  // 获取选中的对象
    if (obj.isDir())  // 如果是目录
    {
        showMessage(QString::fromLocal8Bit("下载文件"), QString::fromLocal8Bit("只能选择文件进行下载"));  // 显示提示信息
        return;
    }

    QString name = idx.data().toString();  // 获取文件名
    static QString lastDir = "./";  // 记录上次选择的目录
    // 获取保存文件路径
    QString filePath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("下载文件"), FileHelper::joinPath(lastDir, name));
    if (filePath.isEmpty())  // 检查文件路径是否为空
    {
        return;
    }

    QFileInfo info(filePath);
    QString jobId = QUuid::createUuid().toString();  // 生成任务ID

    filePath = filePath.replace("\\\\", "/");  // 替换反斜杠为正斜杠
    QJsonObject params;
    QString key = MG->mCloud->currentDir() + name;  // 构建对象键
    params["jobId"] = jobId;
    params["bucketName"] = MG->mCloud->currentBucketName();  // 设置当前桶名称
    params["key"] = key;  // 设置对象键
    params["localPath"] = filePath;  // 设置本地文件路径
    MG->mGate->send(API::OBJECTS::GET, params);  // 发送下载请求
    lastDir = info.dir().absolutePath();  // 更新上次选择的目录
    emit MG->mSignal->startDownload(jobId, key, filePath, obj.size);  // 发送开始下载信号
}

// 显示消息框
void UiObjectsTableWidget::showMessage(const QString &title, const QString &info)
{
    QMessageBox box(QMessageBox::Information, title, info, QMessageBox::Ok);  // 创建消息框
    box.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));  // 设置按钮文本
    box.exec();  // 显示消息框
}
