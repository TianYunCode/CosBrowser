#include "manmodels.h"
#include "middle/manglobal.h"
#include "middle/signals/mansignals.h"
#include "helper/bytehelper.h"

// ManModels 类的构造函数
ManModels::ManModels(QObject *parent) : QObject(parent)
{
    // 创建存储桶数据模型
    m_modelBuckets = new QStandardItemModel(this);
    // 创建对象数据模型
    m_modelObjects = new QStandardItemModel(this);

    // 初始化存储桶表格
    initBucketsTable();
    // 初始化对象表格
    initObjectsTable();

    // 连接信号和槽，当存储桶数据成功获取时，调用 setBuckets 函数
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &ManModels::setBuckets);
    // 连接信号和槽，当对象数据成功获取时，调用 setObjects 函数
    connect(MG->mSignal, &ManSignals::objectsSuccess, this, &ManModels::setObjects);
}

// 设置存储桶数据
void ManModels::setBuckets(const QList<MyBucket> &buckets)
{
    // 设置存储桶数据模型的行数为存储桶列表的大小
    m_modelBuckets->setRowCount(buckets.size());

    // 遍历存储桶列表并设置数据
    for (int i = 0; i < buckets.size(); ++i)
    {
        const MyBucket &bucket = buckets[i];

        // 设置存储桶名称
        QModelIndex index0 = m_modelBuckets->index(i, 0);
        m_modelBuckets->setData(index0, bucket.name);
        // 设置存储桶名称的工具提示
        m_modelBuckets->setData(index0, QString::fromLocal8Bit("存储桶名称：%1").arg(bucket.name), Qt::ToolTipRole);
        // 设置存储桶图标的装饰角色
        m_modelBuckets->setData(index0, QIcon(GLOBAL::PATH::BUCKET), Qt::DecorationRole);

        // 设置存储桶位置
        QModelIndex index1 = m_modelBuckets->index(i, 1);
        m_modelBuckets->setData(index1, bucket.location);

        // 设置存储桶创建日期
        QModelIndex index2 = m_modelBuckets->index(i, 2);
        m_modelBuckets->setData(index2, bucket.createDate);
    }

    // 按创建时间降序排序
    m_modelBuckets->sort(2, Qt::DescendingOrder);
}

// 设置对象数据
void ManModels::setObjects(const QList<MyObject> &objects)
{
    // 设置对象数据模型的行数为对象列表的大小
    m_modelObjects->setRowCount(objects.size());

    // 遍历对象列表并设置数据
    for (int i = 0; i < objects.size(); ++i)
    {
        const MyObject &obj = objects[i];

        // 设置对象名称
        QModelIndex index0 = m_modelObjects->index(i, 0);
        m_modelObjects->setData(index0, obj.name);

        // 将对象数据存储在 UserRole 中
        QVariant var;
        var.setValue(obj);
        m_modelObjects->setData(index0, var, Qt::UserRole);

        // 根据对象是否为目录设置不同的图标
        if (obj.isDir())
        {
            m_modelObjects->setData(index0, QIcon(GLOBAL::PATH::DIR), Qt::DecorationRole);
        }
        else
        {
            m_modelObjects->setData(index0, QIcon(GLOBAL::PATH::FILE), Qt::DecorationRole);
        }

        // 设置对象大小
        QModelIndex index1 = m_modelObjects->index(i, 1);
        QString sizeStr = ByteHelper::toBeautifulStr(obj.size);
        m_modelObjects->setData(index1, sizeStr);

        // 设置对象最后修改时间
        QModelIndex index2 = m_modelObjects->index(i, 2);
        m_modelObjects->setData(index2, obj.lastmodified);
    }
}

// 初始化存储桶表格
void ManModels::initBucketsTable()
{
    // 设置表格的列标题
    QStringList labels;
    labels << QString::fromLocal8Bit("桶名称") << QString::fromLocal8Bit("地区") << QString::fromLocal8Bit("创建时间");

    // 设置存储桶数据模型的列数
    m_modelBuckets->setColumnCount(labels.size());
    // 设置存储桶数据模型的水平表头标签
    m_modelBuckets->setHorizontalHeaderLabels(labels);
}

// 初始化对象表格
void ManModels::initObjectsTable()
{
    // 设置表格的列标题
    QStringList labels;
    labels << QString::fromLocal8Bit("对象名称") << QString::fromLocal8Bit("大小") << QString::fromLocal8Bit("更新时间");

    // 设置对象数据模型的列数
    m_modelObjects->setColumnCount(labels.size());
    // 设置对象数据模型的水平表头标签
    m_modelObjects->setHorizontalHeaderLabels(labels);
}

// 获取对象数据模型
QStandardItemModel *ManModels::modelObjects() const
{
    return m_modelObjects;
}

// 获取存储桶数据模型
QStandardItemModel *ManModels::modelBuckets() const
{
    return m_modelBuckets;
}
