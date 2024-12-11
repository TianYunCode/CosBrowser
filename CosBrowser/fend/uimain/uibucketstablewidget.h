#ifndef UIBUCKETSTABLEWIDGET_H
#define UIBUCKETSTABLEWIDGET_H

// 包含Qt的QWidget类头文件
#include <QWidget>

// 包含自定义的CloudModels头文件
#include "middle/models/cloudmodels.h"

// 定义Ui命名空间
namespace Ui
{
class UiBucketsTableWidget;
}

// 定义UiBucketsTableWidget类，继承自QWidget
class UiBucketsTableWidget : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiBucketsTableWidget(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiBucketsTableWidget();

private slots:
    /**
     * @brief 处理表格视图双击事件
     * @param index 双击的模型索引
     */
    void on_tableView_doubleClicked(const QModelIndex &index);

    /**
     * @brief 处理获取存储桶成功的事件
     * @param buckets 存储桶列表
     */
    void onBucketsSuccess(const QList<MyBucket> &buckets);

    /**
     * @brief 处理页面编号变化的事件
     * @param start 起始位置
     * @param maxLen 最大长度
     */
    void onPageNumChanged(int start, int maxLen);

    /**
     * @brief 处理创建存储桶按钮点击事件
     */
    void on_btnCreateBucket_clicked();

    /**
     * @brief 处理删除存储桶的事件
     */
    void onDelBucket();

    /**
     * @brief 处理刷新按钮点击事件
     */
    void on_btnRefresh_clicked();

private:
    // 指向Ui::UiBucketsTableWidget的指针，用于访问UI元素
    Ui::UiBucketsTableWidget *ui;
};

#endif // UIBUCKETSTABLEWIDGET_H
