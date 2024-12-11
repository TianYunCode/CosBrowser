#ifndef UITABLEVIEW_H
#define UITABLEVIEW_H

// 包含QTableView的头文件
#include <QTableView>

// 定义UiTableView类，继承自QTableView
class UiTableView : public QTableView
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    UiTableView(QWidget *parent = nullptr);
};

#endif // UITABLEVIEW_H
