#ifndef SYSTEMICON_H
#define SYSTEMICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QQuickWindow>
class QAction;
class QMenu;
class SystemIcon : public QObject
{
    Q_OBJECT
public:
    explicit SystemIcon(QObject *parent = nullptr);
    ~SystemIcon();
    Q_INVOKABLE void setWindow(QQuickWindow *window) {mWindow = window;};
signals:

private:
    QSystemTrayIcon *mIcon;
    QQuickWindow *mWindow;
    QAction *mExitAction;
    QMenu *mMenu;
private slots:
   void onActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // SYSTEMICON_H
