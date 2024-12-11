#include <QTimer>

#include "uiprogresswidget.h"
#include "ui_uiprogresswidget.h"
#include "helper/bytehelper.h"

// 构造函数，初始化UI组件
UiProgressWidget::UiProgressWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UiProgressWidget)
{
    ui->setupUi(this); // 设置UI组件
}

// 析构函数，释放UI组件
UiProgressWidget::~UiProgressWidget()
{
    delete ui;
}

// 设置进度条的范围
void UiProgressWidget::setRange(qulonglong minValue, qulonglong maxValue)
{
    m_time.restart(); // 重新启动计时器
    ui->progressBar->setRange(minValue, maxValue); // 设置进度条的范围
    ui->progressBar->setValue(0); // 初始化进度条的值为0
}

// 设置进度条的当前值
void UiProgressWidget::setValue(qulonglong value)
{
    double seconds = m_time.elapsed() / 1000.0; // 计算已经过去的时间（秒）
    ui->progressBar->setValue(value); // 设置进度条的当前值

    static qulonglong lastValue = 0; // 上一次设置值时的上传或下载的字节数
    qulonglong deltaValue = value - lastValue; // 计算本次与上次的差值
    lastValue = value; // 更新上一次的值

    double speed = deltaValue / seconds; // 计算速度（字节/秒）
    QString speedStr = ByteHelper::toBeautifulStr(speed); // 将速度转换为易读的字符串
    ui->labelSpeed->setText(speedStr + "/s"); // 显示速度

    int leftValue = ui->progressBar->maximum() - value; // 计算剩余的字节数
    if (speed > 0 && leftValue > 0)
    {
        int time = leftValue / speed; // 计算剩余时间（秒）
        ui->labelTime->setText(QString::fromLocal8Bit("剩余%1s").arg(time)); // 显示剩余时间
    }
    else
    {
        ui->labelTime->setText(""); // 如果没有剩余字节或速度为0，则清空剩余时间显示
    }
}

// 停止进度条的更新
void UiProgressWidget::stop()
{
    m_time.invalidate(); // 使计时器失效
    ui->labelSpeed->clear(); // 清空速度显示
}

// 设置进度条为完成状态，并显示完成信息
void UiProgressWidget::setFinished(const QString &msg)
{
    setValue(ui->progressBar->maximum()); // 设置进度条为最大值
    ui->labelTime->setText(msg); // 显示完成信息
    stop(); // 停止进度条的更新
}

// 设置进度条为错误状态，并显示错误信息
void UiProgressWidget::setError(const QString &msg)
{
    stop(); // 停止进度条的更新
    ui->labelTime->setText(msg); // 显示错误信息
}
