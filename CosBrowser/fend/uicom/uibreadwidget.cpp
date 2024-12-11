#include <QLabel>
#include <QDebug>

#include "uibreadwidget.h"
#include "ui_uibreadwidget.h"

// 构造函数，初始化面包屑导航控件
UiBreadWidget::UiBreadWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UiBreadWidget)
{
    ui->setupUi(this); // 设置UI界面
    ui->listView->setModel(m_model); // 设置列表视图的模型
    ui->listView->setFlow(QListView::LeftToRight); // 设置列表视图的布局方向为从左到右
    setPath(""); // 初始化路径
    connect(ui->listView, &QListView::clicked, this, &UiBreadWidget::onItemClicked); // 连接列表视图的点击信号到槽函数
    setFixedHeight(30); // 设置固定高度

    ui->listView->setCursor(Qt::PointingHandCursor); // 设置鼠标悬停时的光标样式为手型
}

// 析构函数，释放资源
UiBreadWidget::~UiBreadWidget()
{
    delete ui; // 删除UI对象
}

// 设置路径，接受一个字符串路径
void UiBreadWidget::setPath(const QString &path)
{
    setPath(path.split("/", Qt::SkipEmptyParts)); // 将路径字符串按"/"分割成列表
}

// 设置路径，接受一个字符串列表
void UiBreadWidget::setPath(const QStringList &names)
{
    // 传入的目录名称不能为空
    if (names.size() == 0)
    {
        return;
    }

    clear(); // 清空当前路径
    m_rootName = names[0]; // 设置根目录名称
    for (const QString &name : names)
    {
        addNameButton(name.trimmed()); // 添加目录名称按钮
    }
}

// 清空当前路径
void UiBreadWidget::clear()
{
    m_model->clear(); // 清空模型
}

// 获取当前路径
QString UiBreadWidget::currentPath() const
{
    return getPath(); // 返回当前路径
}

// 获取根目录名称
QString UiBreadWidget::rootName() const
{
    return m_rootName; // 返回根目录名称
}

// 判断当前路径是否为空
bool UiBreadWidget::isEmpty() const
{
    return ui->listView->model()->rowCount() == 0; // 判断模型行数是否为0
}

// 判断当前路径是否为根目录
bool UiBreadWidget::isRoot() const
{
    return getPath() == m_rootName; // 判断当前路径是否等于根目录名称
}

// 添加目录名称按钮
void UiBreadWidget::addNameButton(const QString &name)
{
    if (name == "")
    {
        return;
    }

    QStandardItem *item = new QStandardItem; // 创建标准项
    item->setText(name); // 设置项的文本
    if (!isEmpty())
    {
        item->setIcon(QIcon(":/static/imgs/right.png")); // 设置项的图标为向右箭头
    }

    m_model->appendRow(item); // 将项添加到模型中
}

// 处理列表视图项点击事件
void UiBreadWidget::onItemClicked(const QModelIndex &index)
{
    QStandardItem *newItem = m_model->itemFromIndex(index); // 获取点击的项
    QStandardItem *oldItem = currentItem(); // 获取当前项

    if (newItem == oldItem) // 如果点击的是当前项
    {
        QString oldPath = getPath(oldItem); // 获取当前路径
        emit refresh(oldPath); // 发送刷新信号
        qDebug() << "refresh" << oldPath; // 输出调试信息
    }
    else // 如果点击的是其他项
    {
        QString newPath = getPath(newItem); // 获取新路径
        emit pathChanged(newPath); // 发送路径改变信号
        qDebug() << "pathChange" << newPath; // 输出调试信息
    }
}

// 获取当前项
QStandardItem *UiBreadWidget::currentItem() const
{
    return m_model->item(m_model->rowCount() - 1); // 返回模型中的最后一项
}

// 获取路径
QString UiBreadWidget::getPath(QStandardItem *item) const
{
    if (!item) // 如果项为空
    {
        item = currentItem(); // 获取当前项
    }

    int idx = item->row(); // 获取项的行号
    QStringList pathList; // 创建路径列表
    for (int i = 0; i <= idx; i++) // 遍历到当前项的所有项
    {
        QStandardItem *b = m_model->item(i); // 获取项
        if (b)
        {
            pathList << b->text(); // 将项的文本添加到路径列表
        }
    }

    return pathList.join("/"); // 将路径列表拼接成字符串并返回
}
