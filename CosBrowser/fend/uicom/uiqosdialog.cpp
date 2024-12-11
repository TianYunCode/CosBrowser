#include "uiqosdialog.h"
#include "config/common.h"
#include "ui_uiqosdialog.h"
#include "ui_uibasedialog.h"

// 构造函数，初始化对话框并设置父窗口
UiQosDialog::UiQosDialog(QWidget *parent) : UiBaseDialog(parent), ui(new Ui::UiQosDialog)
{
    // 设置对话框的用户界面
    ui->setupUi(body());

    // 设置对话框的Logo图片路径
    setLogo(GLOBAL::PATH::LOGO_PATH);

    // 设置对话框的标题
    setTitle(STR("Qos"));

    // 设置Logo标签的固定大小为32x24像素
    m_ui->labelLogo->setFixedSize(32, 24);

    // 设置标题标签的样式属性为"h4"
    m_ui->labelTitle->setProperty("style_font", "h4");

    // 设置对话框的初始大小为400x50像素
    resize(400, 50);
}

// 析构函数，释放资源
UiQosDialog::~UiQosDialog()
{
    // 删除用户界面对象
    delete ui;
}
