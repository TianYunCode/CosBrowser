#ifndef UIUPLOAD_H
#define UIUPLOAD_H

// 包含QJsonValue类头文件
#include <QJsonValue>
// 包含QWidget类头文件
#include <QWidget>

// 定义Ui命名空间
namespace Ui
{
class UiUpload;
}

// 声明UiProgressWidget类
class UiProgressWidget;

// 定义UiUpload类，继承自QWidget
class UiUpload : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiUpload(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiUpload();

private slots:
    /**
     * @brief 开始上传的槽函数
     * @param jobId 任务ID
     * @param key 上传的键值
     * @param localPath 本地文件路径
     */
    void onStartUpload(const QString &jobId, const QString &key, const QString &localPath);

    /**
     * @brief 上传进度的槽函数
     * @param jobId 任务ID
     * @param transferedSize 已传输的字节数
     * @param totalSize 总字节数
     */
    void onUploadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize);

    /**
     * @brief 上传成功的槽函数
     * @param jobId 任务ID
     */
    void onUploadSuccess(const QString &jobId);

    /**
     * @brief 上传错误的槽函数
     * @param api API编号
     * @param msg 错误信息
     * @param req 请求的JSON值
     */
    void onError(int api, const QString &msg, const QJsonValue &req);

private:
    /**
     * @brief 查找表格部件项
     * @param jobId 任务ID
     * @return 返回找到的UiProgressWidget指针，如果没有找到则返回nullptr
     */
    UiProgressWidget *findTableWidgetItem(const QString &jobId);

    /**
     * @brief 初始化表头
     */
    void initHeader();

private:
    // 指向Ui::UiUpload的指针，用于访问UI元素
    Ui::UiUpload *ui;
};

#endif // UIUPLOAD_H
