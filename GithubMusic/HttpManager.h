#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QMediaPlayer>

class Manager;
class HttpManager : public QObject
{
    Q_OBJECT
public:
    static HttpManager *GetInstance();
    Q_INVOKABLE void getNetworkInfo(QUrl url);
    Q_INVOKABLE void downLoad(QString str, QString name);
    HttpManager();
    static QObject *httpmanager_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
signals:
    void UrlGetInfo(QByteArray info);
    void urlGetInfo(QByteArray info);
    void readyOk(QString name);
public slots:
    void GetInfoSlot();
private:

    virtual ~HttpManager();
    QNetworkAccessManager *mDownloadManager;
    QNetworkAccessManager *mGetInfoManager;
    QMediaPlayer *player;
    static HttpManager *mMe;
    QFile *mDownLoadFile;
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
