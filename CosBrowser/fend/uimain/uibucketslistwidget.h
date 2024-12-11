#ifndef UIBUCKETSLISTWIDGET_H
#define UIBUCKETSLISTWIDGET_H

// 包含Qt的QWidget类头文件
#include <QWidget>

// 包含自定义的CloudModels头文件
#include "middle/models/cloudmodels.h"

// 定义Ui命名空间
namespace Ui
{
class UiBucketsListWidget;
}

// 定义UiBucketsListWidget类，继承自QWidget
class UiBucketsListWidget : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiBucketsListWidget(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiBucketsListWidget();

private slots:
    /**
     * @brief 处理获取存储桶成功的事件
     * @param buckets 存储桶列表
     */
    void onBucketsSuccess(const QList<MyBucket> &buckets);

    /**
     * @brief 处理列表视图双击事件
     * @param index 双击的模型索引
     */
    void on_listView_doubleClicked(const QModelIndex &index);

    /**
     * @brief 显示指定存储桶的对象
     * @param bucketName 存储桶名称
     */
    void showBucketObjects(const QString &bucketName);

    /**
     * @brief 处理文本编辑事件
     * @param text 编辑的文本内容
     */
    void onTextEdited(const QString &text);

private:
    // 指向Ui::UiBucketsListWidget的指针，用于访问UI元素
    Ui::UiBucketsListWidget *ui;
};

#endif // UIBUCKETSLISTWIDGET_H
