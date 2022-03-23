#ifndef SYSTEMICON_H
#define SYSTEMICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QQuickWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidgetAction>
#include <QSlider>

class QAction;
class QMenu;
class ControlAction;
class VolumnAction;
class SystemIcon : public QObject
{
    Q_OBJECT
public:
    explicit SystemIcon(QObject *parent = nullptr);
    ~SystemIcon();
    Q_INVOKABLE void setWindow(QQuickWindow *window);
signals:

private:
    QSystemTrayIcon *mIcon;
    QQuickWindow *mWindow;
    QAction *mExitAction;
    QMenu *mMenu;
    QWidgetAction *mControl;
    QWidgetAction *mVolumn;


private slots:
   void onActivated(QSystemTrayIcon::ActivationReason reason);
};

class ControlAction : public QWidget
{
    Q_OBJECT
public:
    ControlAction(QWidget *parent = nullptr);
    ~ControlAction();

private:
    QHBoxLayout *mLayout;
    QPushButton *mPrev;
    QPushButton *mNext;
    QPushButton *mPlayOrPause;
};

class VolumnAction : public QWidget
{
    Q_OBJECT
public:
    VolumnAction(QWidget *parent = nullptr);
    ~VolumnAction();

private:
    QHBoxLayout *mLayout;
    QSlider *mVolumn;
};

#endif // SYSTEMICON_H
