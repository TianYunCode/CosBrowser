#include <QCompleter>
#include <QListView>

#include "uicomboline.h"
#include "fend/uidelegates/uitableitemdelegate.h"

// UiComboLine 类构造函数，接受一个父窗口部件参数
UiComboLine::UiComboLine(QWidget *parent) : QLineEdit(parent)
{
    // 调用另一个构造函数设置初始单词列表
    UiComboLine(QStringList(), parent);
}

// UiComboLine 类构造函数，接受一个单词列表和一个父窗口部件参数
UiComboLine::UiComboLine(const QStringList &words, QWidget *parent) : QLineEdit(parent)
{
    // 设置单词列表
    setWords(words);
}

// 设置单词列表的函数
void UiComboLine::setWords(const QStringList &words)
{
    // 创建一个 QCompleter 对象，并将其与当前窗口部件关联
    QCompleter *com = new QCompleter(words, this);

    // 获取 QCompleter 的弹出视图
    QAbstractItemView *view = com->popup();

    // 设置水平滚动条策略为永远不显示
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置垂直滚动条策略为永远不显示
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置弹出视图的项委托，这里使用自定义的 UiTableItemDelegate
    view->setItemDelegate(new UiTableItemDelegate(view));

    // 设置弹出视图的光标样式为指向手形
    view->setCursor(Qt::PointingHandCursor);

    // 连接 QCompleter 的 activated 信号到槽函数，当选择一个单词时触发
    connect(com, QOverload<const QString &>::of(&QCompleter::activated),
            [=](const QString &text)
            {
                emit itemSelected(text); // 发射 itemSelected 信号
            });

    // 将 QCompleter 设置为当前窗口部件的自动补全器
    setCompleter(com);

    // 设置 QCompleter 的过滤模式为 MatchContains（即包含匹配）
    com->setFilterMode(Qt::MatchContains);
}

// 设置整数列表的函数
void UiComboLine::setWords(const QList<int> words)
{
    // 将整数列表转换为字符串列表
    QStringList strs;
    for (int i : words)
    {
        strs << QString::number(i);
    }

    // 调用 setWords 函数设置字符串列表
    setWords(strs);
}

// 设置从 start 到 len 的整数范围的函数
void UiComboLine::setWords(int start, int len)
{
    // 创建一个字符串列表，包含从 start 到 len 的所有整数的字符串表示
    QStringList strs;
    for (int i = start; i <= len; i++)
    {
        strs << QString::number(i);
    }

    // 调用 setWords 函数设置字符串列表
    setWords(strs);
}

// 获取当前单词列表的函数
QStringList UiComboLine::getWords()
{
    // 创建一个空的字符串列表
    QStringList strs;

    // 如果有 QCompleter
    if (completer())
    {
        // 获取 QCompleter 的模型
        QAbstractItemModel *m = completer()->model();

        // 遍历模型中的每一行，将数据添加到字符串列表中
        for (int i = 0; i < m->rowCount(); i++)
        {
            strs << m->index(i, 0).data().toString();
        }
    }

    // 返回字符串列表
    return strs;
}

// 当鼠标按下时触发的函数
void UiComboLine::mousePressEvent(QMouseEvent *e)
{
    // 如果有 QCompleter，则完成自动补全
    if (completer())
    {
        completer()->complete();
    }

    // 调用 QLineEdit 的 mousePressEvent 函数
    QLineEdit::mousePressEvent(e);
}
