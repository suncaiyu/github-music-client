#include "SystemIcon.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QApplication>
SystemIcon::SystemIcon(QObject *parent) : QObject(parent)
{
    mIcon = new QSystemTrayIcon(this);
    mIcon->setIcon(QIcon(":/font/res/Music.ico"));
    mIcon->setToolTip("Furrain Music");
    connect(mIcon , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
    mExitAction = new QAction(QIcon(":/font/res/Music.ico"), "退出", this);
    connect(mExitAction, &QAction::triggered, this, [this](){
        qApp->exit(0);
    });
    mMenu = new QMenu;
    mMenu->addAction(mExitAction);
    mIcon->setContextMenu(mMenu);
    mIcon->show();
}

SystemIcon::~SystemIcon()
{
    delete mExitAction;
    mExitAction = nullptr;
    delete mMenu;
    mMenu = nullptr;
    delete mIcon;
    mIcon = nullptr;
}

// 激活系统托盘
void SystemIcon::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    // 单击托盘显示窗口
    case QSystemTrayIcon::Trigger:
    {
        mWindow->show();
        mWindow->raise();
        break;
    }
    // 双击
    case QSystemTrayIcon::DoubleClick:
    {
        // ...
        break;
    }
    default:
        break;
    }
}
