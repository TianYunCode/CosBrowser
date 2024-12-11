#ifndef UITABLEITEMDELEGATE_H
#define UITABLEITEMDELEGATE_H

// 包含QStyledItemDelegate的头文件
#include <QStyledItemDelegate>

// 包含QAbstractItemView的头文件，因为我们需要使用QAbstractItemView指针
#include <QAbstractItemView>

// 定义UiTableItemDelegate类，继承自QStyledItemDelegate
class UiTableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定被代理的表格视图和父对象
     * @param table 被代理的表格视图指针
     * @param parent 父对象指针，默认为nullptr
     */
    UiTableItemDelegate(QAbstractItemView *table, QObject *parent = nullptr);

    /**
     * @brief 重写paint方法，用于绘制表格项
     * @param painter 用于绘制的QPainter对象
     * @param option 包含绘制选项的QStyleOptionViewItem对象
     * @param index 当前绘制的模型索引
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    // 指明被代理的View,方便获取整行的item
    QAbstractItemView *m_table;
};

#endif // UITABLEITEMDELEGATE_H
