#ifndef UIDOWNLOAD_H
#define UIDOWNLOAD_H

// 包含QWidget类头文件
#include <QWidget>
// 包含QJsonObject类头文件
#include <QJsonObject>

// 定义Ui命名空间
namespace Ui
{
class UiDownload;
}

// 前向声明UiProgressWidget类
class UiProgressWidget;

// 定义UiDownload类，继承自QWidget
class UiDownload : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiDownload(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiDownload();

private slots:
    /**
     * @brief 处理开始下载的槽函数
     * @param jobId 任务ID
     * @param key 下载密钥
     * @param localPath 本地保存路径
     * @param total 总文件大小
     */
    void onStartDownload(const QString &jobId, const QString &key, const QString &localPath, qulonglong total);

    /**
     * @brief 处理下载进度的槽函数
     * @param jobId 任务ID
     * @param transferedSize 已传输的文件大小
     * @param totalSize 总文件大小
     */
    void onDownloadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize);

    /**
     * @brief 处理下载成功的槽函数
     * @param jobId 任务ID
     */
    void onDownloadSuccess(const QString &jobId);

    /**
     * @brief 处理错误的槽函数
     * @param api API编号
     * @param msg 错误信息
     * @param req 请求的JSON数据
     */
    void onError(int api, const QString &msg, const QJsonValue &req);

private:
    /**
     * @brief 查找指定任务ID的进度条控件
     * @param jobId 任务ID
     * @return 返回找到的进度条控件指针，如果没有找到则返回nullptr
     */
    UiProgressWidget *findTableWidgetItem(const QString &jobId);

    /**
     * @brief 初始化表头
     */
    void initHeader();

private:
    // 指向Ui::UiDownload的指针，用于访问UI元素
    Ui::UiDownload *ui;
};

#endif // UIDOWNLOAD_H
