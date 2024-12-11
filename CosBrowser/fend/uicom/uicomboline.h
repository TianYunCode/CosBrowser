#ifndef UICOMBOLINE_H
#define UICOMBOLINE_H

// 包含必要的Qt头文件
#include <QLineEdit>
#include <QListView>
#include <QStringListModel>

// 定义UiComboLine类，继承自QLineEdit
class UiComboLine : public QLineEdit
{
    Q_OBJECT  // 使用Qt的元对象系统

public:
    /**
     * @brief 构造函数，允许指定父窗口
     * @param parent 父窗口指针，默认为nullptr
     */
    UiComboLine(QWidget *parent = nullptr);

    /**
     * @brief 构造函数，允许指定提示列表和父窗口
     * @param words 提示列表
     * @param parent 父窗口指针，默认为nullptr
     */
    UiComboLine(const QStringList &words, QWidget *parent = nullptr);

    /**
     * @brief 设置提示列表，通过QStringList设置
     * @param words 提示列表
     */
    void setWords(const QStringList &words);

    /**
     * @brief 设置提示列表，通过QList<int>设置
     * @param words 提示列表
     */
    void setWords(const QList<int> words);

    /**
     * @brief 设置提示列表，通过指定起始值和长度生成
     * @param start 起始值，默认为1
     * @param len 长度，默认为10
     */
    void setWords(int start = 1, int len = 10);

    /**
     * @brief 获取提示列表
     * @return 提示列表
     */
    QStringList getWords();

signals:
    /**
     * @brief 提示列表被选中信号
     * @param text 被选中的文本
     */
    void itemSelected(const QString &text);

protected:
    /**
     * @brief 鼠标点击事件处理函数
     * @param event 鼠标事件
     */
    void mousePressEvent(QMouseEvent *) override;
};

#endif // UICOMBOLINE_H
