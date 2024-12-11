#ifndef MANMODELS_H
#define MANMODELS_H

// 包含必要的Qt头文件
#include <QObject>
#include <QStandardItemModel>

// 包含自定义的中间层模型头文件
#include "middle/models/cloudmodels.h"

/**
 * @brief ManModels类，继承自QObject，用于管理模型对象
 */
class ManModels : public QObject
{
    Q_OBJECT  // 使用Q_OBJECT宏，启用Qt的元对象系统

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针，默认为nullptr
     */
    explicit ManModels(QObject *parent = nullptr);

    /**
     * @brief 获取存储桶表格模型
     * @return QStandardItemModel指针，指向存储桶表格模型
     */
    QStandardItemModel *modelBuckets() const;

    /**
     * @brief 获取对象表格模型
     * @return QStandardItemModel指针，指向对象表格模型
     */
    QStandardItemModel *modelObjects() const;

signals:
         // 信号部分暂时为空

private slots:
    /**
     * @brief 设置存储桶数据
     * @param buckets 存储桶列表
     */
    void setBuckets(const QList<MyBucket> &buckets);

    /**
     * @brief 设置对象数据
     * @param objects 对象列表
     */
    void setObjects(const QList<MyObject> &objects);

private:
    /**
     * @brief 初始化存储桶表格
     */
    void initBucketsTable();

    /**
     * @brief 初始化对象表格
     */
    void initObjectsTable();

private:
    QStandardItemModel *m_modelBuckets = nullptr; // 存储桶表格模型
    QStandardItemModel *m_modelObjects = nullptr; // 对象表格模型
};

#endif // MANMODELS_H
