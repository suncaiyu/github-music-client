#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QMediaPlayer>
#include "ProcessJson.h"


/// 搜索部分写的很烂，需要重构 ///
///
///
///
class Manager;
class HttpManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ProcessJson *processJson READ processJson WRITE setProcessJson)
public:
    static HttpManager *GetInstance();
    Q_INVOKABLE void getNetworkInfo(QUrl url);
    void reGetNetworkInfo(QUrl url);
    Q_INVOKABLE void downLoad(QString str, QString name);
    HttpManager();
    static QObject *httpmanager_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
    ProcessJson *processJson() { return mPJson; }
    void setProcessJson(ProcessJson *p) {mPJson = p;}

signals:
    void readyOk(QString name);
    void updateList();
    void errorMessageSignal(QString msg);
    void downLoadProcessSignal(qint64 all, qint64 current);
public slots:
    void GetInfoSlot();
    void reGetInfoSlot();
private:

    virtual ~HttpManager();
    QNetworkAccessManager *mDownloadManager;
    QNetworkAccessManager *mGetInfoManager;
    static HttpManager *mMe;
    QFile *mDownLoadFile;
    QUrl mUrl;
    ProcessJson *mPJson;
    class Manager {
    public:
        Manager() {qDebug() << "create manager";};
        ~Manager()
        {
            qDebug() << "delete Manager";
            if (HttpManager::mMe) {
                delete HttpManager::mMe;
                HttpManager::mMe = nullptr;
            }
        }
    };
    static Manager manager;
};
//static QObject *httpmanager_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
#endif // HTTPMANAGER_H
