#include <QPushButton>

#include "uimessagebox.h"
#include "fend/uicom/uipushbutton.h"
#include "ui_uimessagebox.h"

// UiMessageBox 类构造函数，接受一个父窗口部件参数
UiMessageBox::UiMessageBox(QWidget *parent) : UiQosDialog(parent), ui(new Ui::UiMessageBox)
{
    // 设置 UI 布局
    ui->setupUi(body());
}

// UiMessageBox 类析构函数
UiMessageBox::~UiMessageBox()
{
    // 删除 UI 对象
    delete ui;
}

// 显示消息框并返回用户点击的按钮文本
QString UiMessageBox::showMessage(const QString &title, const QString &text, const QStringList &btnTextList)
{
    // 清空之前的消息文本
    m_text = "";

    // 设置标题
    setTitle(title);

    // 设置消息文本
    ui->label->setText(text);

    // 创建按钮
    createBtns(btnTextList);

    // 显示消息框并等待用户操作
    exec();

    // 返回用户选择的按钮文本
    return m_text;
}

// 创建按钮并添加到布局中
void UiMessageBox::createBtns(const QStringList &textList)
{
    // 遍历按钮文本列表
    for (const auto &text : qAsConst(textList))
    {
        // 创建一个新的 UiPushButton 实例
        UiPushButton *btn = new UiPushButton(this);

        // 设置按钮文本
        btn->setText(text);

        // 连接按钮的 clicked 信号到槽函数
        connect(btn, &QPushButton::clicked, [=]()
                {
                    // 设置消息文本为当前按钮的文本
                    m_text = text;

                    // 接受对话框操作
                    accept();
                });

        // 将按钮添加到水平布局中
        ui->horizontalLayout->addWidget(btn);
    }
}
