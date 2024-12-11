#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QKeyEvent>

#include "uibasedialog.h"
#include "ui_uibasedialog.h"

// 构造函数，初始化对话框
UiBaseDialog::UiBaseDialog(QWidget *parent) : QDialog(parent), m_ui(new Ui::UiBaseDialog)
{
    m_ui->setupUi(this); // 设置UI界面
    setWindowFlags(Qt::CustomizeWindowHint | Qt::Window); // 设置窗口标志，自定义窗口提示和窗口标志

    setLogo(":/static/imgs/qtlogo.png"); // 设置窗口Logo
    addCloseButton(":/static/imgs/Close-1.png", ":/static/imgs/Close-2.png"); // 添加关闭按钮
    setAllButtonSize(); // 设置所有按钮的大小
    m_ui->labelLogo->setFixedSize(28, 28); // 设置Logo标签的大小
}

// 析构函数，释放资源
UiBaseDialog::~UiBaseDialog()
{
    delete m_ui; // 删除UI对象
}

// 设置对话框标题
void UiBaseDialog::setTitle(const QString &title)
{
    m_ui->labelTitle->setText(title); // 设置标题标签的文本
}

// 设置对话框Logo
void UiBaseDialog::setLogo(const QString &path)
{
    m_ui->labelLogo->setStyleSheet(QString("border-image: url(\"%1\");").arg(path)); // 设置Logo标签的样式表
}

// 添加最小化按钮
void UiBaseDialog::addMinButton(const QString &path, const QString &hoverPath)
{
    QPushButton *btn = addButton(path, hoverPath); // 添加按钮
    connect(btn, &QPushButton::clicked, this, &UiBaseDialog::showMinimized); // 连接按钮点击信号到最小化槽函数
}

// 添加最大化按钮
void UiBaseDialog::addMaxButton(const QString &maxPath, const QString &maxPathHover, const QString &normalPath, const QString &normalPathHover)
{
    QPushButton *btn = addButton(maxPath, maxPathHover); // 添加按钮

    // 定义一个lambda函数，用于切换按钮的图片
    auto funcImg = [=]()
    {
        isMaximized() ? setButtonImage(btn, normalPath, normalPathHover) : setButtonImage(btn, maxPath, maxPathHover);
    };

    // 定义一个lambda函数，用于切换窗口的最大化和正常状态
    auto funcShow = [=]()
    {
        isMaximized() ? showNormal() : showMaximized(); // 切换窗口状态
        funcImg(); // 切换按钮图片
    };

    connect(btn, &QPushButton::clicked, this, funcShow); // 连接按钮点击信号到切换窗口状态的槽函数
    funcImg(); // 初始化按钮图片
}

// 添加按钮
QPushButton *UiBaseDialog::addButton(const QString &path, const QString &hoverPath)
{
    UiPushButton *btn = new UiPushButton; // 创建按钮
    btn->setFixedSize(m_sz, m_sz); // 设置按钮大小
    setButtonImage(btn, path, hoverPath); // 设置按钮图片
    addWidget(btn); // 添加按钮到布局
    return btn; // 返回按钮指针
}

// 设置按钮图片
void UiBaseDialog::setButtonImage(QPushButton *btn, const QString &path, const QString &hoverPath)
{
    btn->setStyleSheet(QString(
                           "QPushButton{border-image: url(\"%1\");}"
                           "QPushButton:hover{border-image: url(\"%2\");}"
                           ).arg(path, hoverPath)); // 设置按钮样式表
}

// 设置所有按钮的大小
void UiBaseDialog::setAllButtonSize(int w)
{
    QList<QPushButton *> btnList = m_ui->frameTitle->findChildren<QPushButton *>(); // 获取所有按钮
    for (auto *btn : btnList)
    {
        btn->setFixedSize(w, w); // 设置按钮大小
    }

    m_sz = w; // 保存按钮大小
}

// 禁用键盘事件
void UiBaseDialog::setKeyDisabled()
{
    installEventFilter(this); // 安装事件过滤器
}

// 添加标题线
void UiBaseDialog::addTitleLine(int w)
{
    QLabel *label = new QLabel; // 创建标签
    label->setFixedSize(w, 15); // 设置标签大小
    addWidget(label); // 添加标签到布局
}

// 鼠标按下事件处理
void UiBaseDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_start = event->pos(); // 记录鼠标按下时的位置
    }

    QDialog::mousePressEvent(event); // 调用基类的鼠标按下事件处理函数
}

// 鼠标移动事件处理
void UiBaseDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint targetPos = event->pos() - m_start + pos(); // 计算目标位置
        this->move(targetPos); // 移动窗口
    }

    QDialog::mouseMoveEvent(event); // 调用基类的鼠标移动事件处理函数
}

// 事件过滤器
bool UiBaseDialog::eventFilter(QObject *obj, QEvent *event)
{
    UiBaseDialog *pDialog = qobject_cast<UiBaseDialog *>(obj); // 转换对象类型
    if (pDialog && event->type() == QEvent::KeyPress) // 如果是键盘按下事件
    {
        QKeyEvent *pKeyEvent = static_cast<QKeyEvent *>(event); // 转换事件类型
        if (pKeyEvent->key() == Qt::Key_Return || pKeyEvent->key() == Qt::Key_Escape || pKeyEvent->key() == Qt::Key_Enter) // 如果是回车、Esc或Enter键
        {
            return true; // 返回true，表示事件已被处理
        }
    }

    return QObject::eventFilter(obj, event); // 调用基类的事件过滤器
}

// 获取对话框主体
QWidget *UiBaseDialog::body()
{
    return m_ui->widgetBody; // 返回主体部件
}

// 添加关闭按钮
void UiBaseDialog::addCloseButton(const QString &path, const QString &hoverPath)
{
    setButtonImage(m_ui->btnClose, path, hoverPath); // 设置关闭按钮图片
    m_ui->horizontalLayout->addWidget(m_ui->btnClose); // 将关闭按钮添加到布局
    connect(m_ui->btnClose, &QPushButton::clicked, this, &UiBaseDialog::reject); // 连接关闭按钮点击信号到关闭对话框的槽函数
}

// 添加部件到布局
void UiBaseDialog::addWidget(QWidget *w)
{
    int i = m_ui->horizontalLayout->indexOf(m_ui->btnClose); // 获取关闭按钮的位置
    m_ui->horizontalLayout->insertWidget(i, w); // 在关闭按钮之前插入部件
}
