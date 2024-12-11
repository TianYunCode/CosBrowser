#ifndef UIOBJECTSTABLEWIDGET_H
#define UIOBJECTSTABLEWIDGET_H

// 包含QWidget类头文件
#include <QWidget>

// 包含自定义的CloudModels头文件
#include "middle/models/cloudmodels.h"

// 定义Ui命名空间
namespace Ui
{
class UiObjectsTableWidget;
}

// 定义UiObjectsTableWidget类，继承自QWidget
class UiObjectsTableWidget : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiObjectsTableWidget(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiObjectsTableWidget();

private slots:
    /**
     * @brief 处理btnBuckets按钮点击事件
     */
    void on_btnBuckets_clicked();

    /**
     * @brief 处理tableView双击事件
     * @param index 被双击的QModelIndex对象
     */
    void on_tableView_doubleClicked(const QModelIndex &index);

    /**
     * @brief 获取对象列表成功时的处理函数
     * @param objects 对象列表
     */
    void onObjectsSuccess(const QList<MyObject> &objects);

    /**
     * @brief 处理路径改变事件
     * @param newPath 新的路径
     */
    void onPathChanged(const QString &newPath);

    /**
     * @brief 处理页码改变事件
     * @param start 起始页码
     * @param maxLen 最大长度
     */
    void onPageNumChanged(int start, int maxLen);

    /**
     * @brief 处理btnRefresh按钮点击事件
     */
    void on_btnRefresh_clicked();

    /**
     * @brief 处理btnUpload按钮点击事件
     */
    void on_btnUpload_clicked();

    /**
     * @brief 处理上传成功事件
     * @param jobId 任务ID
     */
    void onUploadSuccess(const QString &jobId);

    /**
     * @brief 处理下载成功事件
     * @param jobId 任务ID
     */
    void onDownloadSuccess(const QString &jobId);

    /**
     * @brief 处理btnDownload按钮点击事件
     */
    void on_btnDownload_clicked();

    /**
     * @brief 显示消息
     * @param title 消息标题
     * @param info 消息内容
     */
    void showMessage(const QString &title, const QString &info);

private:
    // 指向Ui::UiObjectsTableWidget的指针，用于访问UI元素
    Ui::UiObjectsTableWidget *ui;
};

#endif // UIOBJECTSTABLEWIDGET_H
