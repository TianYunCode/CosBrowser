#ifndef UIPAGEWIDGET_H
#define UIPAGEWIDGET_H

// 包含必要的Qt头文件
#include <QWidget>

// 定义Ui命名空间
namespace Ui
{
class UiPageWidget;
}

// 定义UiPageWidget类，继承自QWidget
class UiPageWidget : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit UiPageWidget(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UiPageWidget();

    // 获取属性值，相关方法

    /**
     * @brief 获取总行数
     * @return 总行数
     */
    int totalRow() const;

    /**
     * @brief 获取每页最大行数
     * @return 每页最大行数
     */
    int maxRow() const;

    /**
     * @brief 获取当前页码
     * @return 当前页码
     */
    int currentPage() const;

    /**
     * @brief 获取总页数
     * @return 总页数
     */
    int pageCount() const;

    /**
     * @brief 判断是否是第一页
     * @return 如果是第一页返回1，否则返回0
     */
    int isFirstPage() const;

    /**
     * @brief 判断是否是最后一页
     * @return 如果是最后一页返回1，否则返回0
     */
    int isLastPage() const;

    // 设置属性值，相关方法，如下两个方法会触发reset信号

    /**
     * @brief 设置总行数
     * @param newTotalRow 新的总行数
     */
    void setTotalRow(int newTotalRow);

    /**
     * @brief 设置每页最大显示行数
     * @param rows 每页最大行数
     */
    void setMaxRow(int rows);

    /**
     * @brief 设置每页显示行数选择列表
     * @param rowList 每页显示行数选择列表
     */
    void setMaxRowList(const QList<int> rowList);

signals:
    /**
     * @brief 页码发生变化信号
     * @param start 起始索引
     * @param maxLen 每页最大条数
     */
    void pageNumChanged(int start, int maxLen);

public slots:
    /**
     * @brief 下一页
     */
    void next();

    /**
     * @brief 上一页
     */
    void pre();

    /**
     * @brief 跳转到指定页
     * @param page 目标页码
     */
    void jumpTo(int page);

private slots:
    /**
     * @brief 当前页选择发生变化时的处理函数
     * @param text 当前页选择的文本
     */
    void onCurrentPageSelected(const QString &text);

    /**
     * @brief 每页显示行数选择发生变化时的处理函数
     * @param text 每页显示行数选择的文本
     */
    void onMaxRowsItemSelected(const QString &text);

private:
    /**
     * @brief 设置页号选择列表
     */
    void setPageCount();

    /**
     * @brief 重置为首页
     */
    void reset();

    /**
     * @brief 切换页码
     * @param newCurrentPage 新的当前页码
     */
    void switchPage(int newCurrentPage);

private:
    Ui::UiPageWidget *ui;  // UI指针，用于访问UI元素
    int m_totalRow = 0;    // 总共有多少行
    int m_currentPage = 1; // 当前是第几页
    int m_maxRow = 10;     // 每一页有多少行
};

#endif // UIPAGEWIDGET_H
