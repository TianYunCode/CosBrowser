#include <QAbstractItemView>
#include <QPainter>
#include <QTableWidget>

#include "uitableitemdelegate.h"

// 构造函数，初始化委托并设置表格视图
UiTableItemDelegate::UiTableItemDelegate(QAbstractItemView *table, QObject *parent)
    : QStyledItemDelegate(parent), m_table(table)
{
    // 初始化父类 QStyledItemDelegate，并保存表格视图的指针
}

// 绘制单元格内容
void UiTableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 检查当前单元格是否处于鼠标悬停状态，并且索引是否有效
    if (option.state.testFlag(QStyle::State_MouseOver) && index.isValid())
    {
        // 获取表格视图的模型
        QAbstractItemModel *m = m_table->model();

        // 获取当前单元格的行号
        int row = index.row();

        // 获取模型的列数
        int columnCount = m->columnCount();

        // 遍历当前行的所有列
        for (int i = 0; i < columnCount; i++)
        {
            // 获取当前列的模型索引
            QModelIndex idx = m->index(row, i);

            // 创建一个新的 QStyleOptionViewItem 对象，用于绘制当前列的单元格
            QStyleOptionViewItem op = option;
            op.index = idx;
            op.rect = m_table->visualRect(idx);

            // 调用父类的 paint 方法绘制当前列的单元格
            QStyledItemDelegate::paint(painter, op, idx);
        }

        // 如果当前单元格处于鼠标悬停状态，绘制完成后直接返回
        return;
    }

    // 如果当前单元格不处于鼠标悬停状态，直接调用父类的 paint 方法绘制
    return QStyledItemDelegate::paint(painter, option, index);
}
