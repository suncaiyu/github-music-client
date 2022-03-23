#include "SystemIcon.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QApplication>
#include <QtWinExtras>

SystemIcon::SystemIcon(QObject *parent) : QObject(parent)
{
    mIcon = new QSystemTrayIcon(this);
    mIcon->setIcon(QIcon(":/font/res/Music.ico"));
    mIcon->setToolTip("Furrain Music");
    connect(mIcon , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));

    mControl = new QWidgetAction(this);
    ControlAction *ca = new ControlAction();
    mControl->setDefaultWidget(ca);

    mVolumn = new QWidgetAction(this);
    VolumnAction *va = new VolumnAction();
    mVolumn->setDefaultWidget(va);

    mExitAction = new QAction(QIcon(":/font/res/Music.ico"), "退出", this);
    connect(mExitAction, &QAction::triggered, this, [this](){
        qApp->exit(0);
    });
    mMenu = new QMenu;
    mMenu->addAction(mControl);
    mMenu->addSeparator();
    mMenu->addAction(mVolumn);
    mMenu->addSeparator();
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

void SystemIcon::setWindow(QQuickWindow *window)
{
    mWindow = window;

    QWinThumbnailToolBar *thumbbar = new QWinThumbnailToolBar(window);
    thumbbar->setWindow(window);

    QWinThumbnailToolButton *settings = new QWinThumbnailToolButton(thumbbar);
    settings->setToolTip("Settings");
    settings->setIcon(QIcon(":/font/res/Music.ico"));
    settings->setDismissOnClick(true);

    thumbbar->addButton(settings);
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

ControlAction::ControlAction(QWidget *parent) : QWidget(parent)
{
    mLayout = new QHBoxLayout();
    mPrev = new QPushButton("prev");
    mNext = new QPushButton("next");
    mPlayOrPause = new QPushButton("play");
    mLayout->addWidget(mPrev);
    mLayout->addWidget(mPlayOrPause);
    mLayout->addWidget(mNext);
    setLayout(mLayout);
}

ControlAction::~ControlAction()
{
    delete mPlayOrPause;
    delete mPrev;
    delete mNext;
    delete mLayout;
}

VolumnAction::VolumnAction(QWidget *parent) : QWidget (parent)
{
    mLayout = new QHBoxLayout();
    mVolumn = new QSlider(Qt::Orientation::Horizontal);
    mLayout->addWidget(mVolumn);
    setLayout(mLayout);
}

VolumnAction::~VolumnAction()
{
    delete mVolumn;
    delete mLayout;
}
