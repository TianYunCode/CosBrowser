#include <QDebug>
#include "qmath.h"

#include "uipagewidget.h"
#include "ui_uipagewidget.h"

// UiPageWidget 类构造函数，接受一个父窗口部件参数
UiPageWidget::UiPageWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UiPageWidget)
{
    // 初始化 UI 布局
    ui->setupUi(this);

    // 连接按钮的 clicked 信号到 next 方法
    connect(ui->btnNext, &QPushButton::clicked, this, &UiPageWidget::next);

    // 连接按钮的 clicked 信号到 pre 方法
    connect(ui->btnPre, &QPushButton::clicked, this, &UiPageWidget::pre);

    // 设置最大行数输入框的对齐方式为中心对齐
    ui->lineMaxRows->setAlignment(Qt::AlignHCenter);

    // 设置最大行数输入框为只读
    ui->lineMaxRows->setReadOnly(true);

    // 连接最大行数输入框的 itemSelected 信号到 onMaxRowsItemSelected 方法
    connect(ui->lineMaxRows, &UiComboLine::itemSelected, this, &UiPageWidget::onMaxRowsItemSelected);

    // 设置当前页码输入框的对齐方式为中心对齐
    ui->lineCurrentPage->setAlignment(Qt::AlignHCenter);

    // 设置当前页码输入框为只读
    ui->lineCurrentPage->setReadOnly(true);

    // 连接当前页码输入框的 itemSelected 信号到 onCurrentPageSelected 方法
    connect(ui->lineCurrentPage, &UiComboLine::itemSelected, this, &UiPageWidget::onCurrentPageSelected);

    // 禁用上一页和下一页按钮
    ui->btnNext->setDisabled(true);
    ui->btnPre->setDisabled(true);

    // 设置样式属性，用于自定义样式
    ui->lineCurrentPage->setProperty("style_frame", "bottomframe");
    ui->lineMaxRows->setProperty("style_frame", "bottomframe");
}

// UiPageWidget 类析构函数
UiPageWidget::~UiPageWidget()
{
    // 删除 UI 对象
    delete ui;
}

// 获取总行数
int UiPageWidget::totalRow() const
{
    return m_totalRow;
}

// 获取每页的最大行数
int UiPageWidget::maxRow() const
{
    return m_maxRow;
}

// 获取当前页码
int UiPageWidget::currentPage() const
{
    return m_currentPage;
}

// 计算总页数
int UiPageWidget::pageCount() const
{
    if (m_totalRow == 0)
    {
        return 1;
    }

    // 使用 qCeil 获取不小于 v 的最小整数
    return qCeil(m_totalRow / float(m_maxRow));
}

// 判断是否为第一页
int UiPageWidget::isFirstPage() const
{
    return currentPage() == 1;
}

// 判断是否为最后一页
int UiPageWidget::isLastPage() const
{
    return currentPage() == pageCount();
}

// 设置总行数
void UiPageWidget::setTotalRow(int newTotalRow)
{
    m_totalRow = newTotalRow;
    // 更新标签显示总行数
    ui->label->setText(QString::fromLocal8Bit("共%1条， 每页").arg(newTotalRow));

    // 重置页面
    reset();
}

// 设置每页的最大行数
void UiPageWidget::setMaxRow(int rows)
{
    // 获取最大行数输入框中的所有选项
    QStringList words = ui->lineMaxRows->getWords();
    for (const auto &num : qAsConst(words))
    {
        // 如果找到匹配的行数，则设置新的最大行数，并重置页面
        if (num.toInt() == rows)
        {
            m_maxRow = rows;
            reset();
            break;
        }
    }
}

// 设置最大行数列表
void UiPageWidget::setMaxRowList(const QList<int> rowList)
{
    // 设置最大行数输入框的选项列表
    ui->lineMaxRows->setWords(rowList);

    // 如果列表中有元素，则设置默认值并重置页面
    if (rowList.size() > 0)
    {
        ui->lineMaxRows->setText(QString::number(rowList[0]));
        setMaxRow(rowList[0]);
    }
}

// 处理下一页按钮点击事件
void UiPageWidget::next()
{
    // 跳转到下一页
    jumpTo(currentPage() + 1);
}

// 处理上一页按钮点击事件
void UiPageWidget::pre()
{
    // 跳转到上一页
    jumpTo(currentPage() - 1);
}

// 跳转到指定页码
void UiPageWidget::jumpTo(int page)
{
    if (page != currentPage())
    {
        // 切换页面
        switchPage(page);
    }
}

// 当前页码输入框选择项时触发
void UiPageWidget::onCurrentPageSelected(const QString &text)
{
    if (m_currentPage != text.toInt())
    {
        // 跳转到指定页码
        jumpTo(text.toInt());
    }
}

// 最大行数输入框选择项时触发
void UiPageWidget::onMaxRowsItemSelected(const QString &text)
{
    // 设置最大行数
    setMaxRow(text.toInt());
}

// 重置页面
void UiPageWidget::reset()
{
    // 设置总页数
    setPageCount();

    // 切换到首页
    switchPage(1);
}

// 切换页面
void UiPageWidget::switchPage(int newCurrentPage)
{
    // 更新当前页码
    m_currentPage = newCurrentPage;
    ui->lineCurrentPage->setText(QString::number(newCurrentPage));

    // 根据当前页码更新上一页和下一页按钮的状态
    ui->btnPre->setDisabled(isFirstPage());
    ui->btnNext->setDisabled(isLastPage());

    // 计算开始行和结束行
    int start = (newCurrentPage - 1) * maxRow();
    int left = (totalRow()) - start;
    int len = left < maxRow() ? left : maxRow();
    qDebug() << QString("switchPage %1,%2").arg(start).arg(len);

    // 发送页码变化信号
    emit pageNumChanged(start, len);
}

// 设置总页数
void UiPageWidget::setPageCount()
{
    int count = pageCount();
    // 更新标签显示总页数
    ui->labelPageCount->setText("/" + QString::number(count));

    // 设置当前页码输入框的选项列表
    ui->lineCurrentPage->setWords(1, count);
    ui->lineCurrentPage->setText("1");
}
