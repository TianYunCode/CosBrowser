#include "uitableview.h"
#include "fend/uidelegates/uitableitemdelegate.h"

// 构造函数，初始化表格视图并设置父窗口
UiTableView::UiTableView(QWidget *parent) : QTableView(parent)
{
    // 设置表格视图的项目委托为 UiTableItemDelegate
    setItemDelegate(new UiTableItemDelegate(this));
}
