#ifndef UIBREADWIDGET_H
#define UIBREADWIDGET_H

// 包含必要的Qt头文件
#include <QStandardItemModel>
#include <QWidget>

// 定义Ui命名空间
namespace Ui
{
class UiBreadWidget;
}

// 定义UiBreadWidget类，继承自QWidget
class UiBreadWidget : public QWidget
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    // 构造函数，允许指定父窗口
    explicit UiBreadWidget(QWidget *parent = nullptr);

    // 析构函数
    ~UiBreadWidget();

    /**
     * @brief 设置路径，可通过完整路径设置，也可通过名称列表设置
     * @param path 完整路径
     */
    void setPath(const QString &path);

    /**
     * @brief 设置路径，通过名称列表设置
     * @param names 路径名称列表
     */
    void setPath(const QStringList &names);

    /**
     * @brief 清空当前路径
     */
    void clear();

    /**
     * @brief 获取当前路径
     * @return 当前路径
     */
    QString currentPath() const;

    /**
     * @brief 获取根目录名称
     * @return 根目录名称
     */
    QString rootName() const;

    /**
     * @brief 判断当前路径是否为空
     * @return 如果路径为空，返回true；否则返回false
     */
    bool isEmpty() const;

    /**
     * @brief 判断路径是否是根目录
     * @return 如果是根目录，返回true；否则返回false
     */
    bool isRoot() const;

signals:
    /**
     * @brief 刷新信号，当路径发生变化时发出
     * @param path 新的路径
     */
    void refresh(const QString &path);

    /**
     * @brief 路径变化信号，当路径发生变化时发出
     * @param newPath 新的路径
     */
    void pathChanged(const QString &newPath);

private:
    /**
     * @brief 添加一块面包屑，即添加一个按钮
     * @param name 面包屑的名称
     */
    void addNameButton(const QString &name);

    /**
     * @brief 当点击某个面包屑时，把它后面的面包屑全部删除
     * @param index 被点击的面包屑的索引
     */
    void onItemClicked(const QModelIndex &index);

    /**
     * @brief 获取当前item，即为叶子结点
     * @return 当前item
     */
    QStandardItem *currentItem() const;

    /**
     * @brief 根据item获取，item到根节点的路径
     * @param item 指定的item，如果为nullptr，则返回当前路径
     * @return item到根节点的路径
     */
    QString getPath(QStandardItem *item = nullptr) const;

private:
    Ui::UiBreadWidget *ui;  // 指向UiBreadWidget的用户界面指针

    /* 因为根目录是必须存在的，所以
     *  使用m_rootName存储根目录，使用model存储所有目录名称列表
     */
    QString m_rootName;  // 根目录名称
    QStandardItemModel *m_model = new QStandardItemModel();  // 存储目录名称列表的模型
};

#endif // UIBREADWIDGET_H
