#include <QApplication>
#include <QIcon>
#include "middle/manglobal.h"

#include "fend/uilogin/uilogindialog.h"
#include "fend/uimain/uimain.h"

int main(int argc, char *argv[])
{
    // 创建 QApplication 对象，这是每个 Qt 应用程序必须有的对象
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/static/imgs/logo.ico"));

    // 初始化全局对象 MG，通常用于设置全局状态或配置
    MG->init(argc, argv);

    // 创建主窗口对象 UiMain
    UiMain w;

    // 创建登录对话框对象 UiLoginDialog
    UiLoginDialog login;

    // 显示登录对话框
    login.show();

    // 进入应用程序的主事件循环，等待用户交互
    return a.exec();
}
