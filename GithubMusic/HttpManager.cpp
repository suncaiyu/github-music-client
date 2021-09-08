#include "HttpManager.h"
#include <QNetworkReply>
#include <QByteArray>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
//HttpManager::Manager HttpManager::manager = Manager();
HttpManager *HttpManager::mMe = nullptr;

HttpManager *HttpManager::GetInstance()
{
    if(mMe == nullptr) {
        mMe = new HttpManager();
    }
    return mMe;
}

void HttpManager::getNetworkInfo(QUrl url)
{
    QNetworkReply *replay = mGetInfoManager->get(QNetworkRequest(url));
    connect(replay, &QNetworkReply::finished, this, &HttpManager::GetInfoSlot);
}

void HttpManager::downLoad(QString i, QString name)
{
    QDir folder(qApp->applicationDirPath() + "/Music");
    if (!folder.exists()) {
        folder.mkdir(qApp->applicationDirPath() + "/Music");
    }
    folder.setFilter(QDir::Files|QDir::Hidden);
    folder.setSorting(QDir::DirsFirst);
    QFileInfoList list = folder.entryInfoList();
    QNetworkReply *replay = mDownloadManager->get(QNetworkRequest(i));
//    qDebug() << qApp->applicationDirPath();
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i).fileName() == name) {
            emit readyOk(QDir::fromNativeSeparators(qApp->applicationDirPath() + "/Music/" + name));
            return;
        }
    }
    mDownLoadFile = new QFile(QCoreApplication::applicationDirPath() + "/Music/" + name);
    mDownLoadFile->open(QIODevice::WriteOnly);
    connect(replay, &QNetworkReply::readyRead, this, [this](){
        QNetworkReply *r = qobject_cast<QNetworkReply *>(sender());
        mDownLoadFile->write(r->readAll());
    });
    connect(replay, &QNetworkReply::downloadProgress, this, [this](qint64 cur, qint64 all){
        qDebug() << all << "---->" << cur;
    });
    connect(replay, &QNetworkReply::finished, this, [this](){
        QNetworkReply *r = qobject_cast<QNetworkReply *>(sender());

        emit readyOk(QDir::fromNativeSeparators(mDownLoadFile->fileName()));
        delete mDownLoadFile;
        mDownLoadFile = nullptr;
        r->deleteLater();
    });
}

void HttpManager::GetInfoSlot()
{
    QNetworkReply *replay = qobject_cast<QNetworkReply *>(this->sender());
    QByteArray info = replay->readAll();
    emit UrlGetInfo(info);
    emit urlGetInfo(info);
}

HttpManager::HttpManager()
{
    mGetInfoManager = new QNetworkAccessManager;
    mDownloadManager = new QNetworkAccessManager;
    player = new QMediaPlayer;
//    player->setMedia(QUrl::fromLocalFile("D:\\QtProject\\build-GithubMusic-Desktop_Qt_5_14_0_MinGW_32_bit-Debug\\Music\\1874-陈奕迅.mp3"));
//    player->play();
    QDir dir(qApp->applicationDirPath() + "/Music/");
    dir.setFilter(QDir::Files|QDir::Hidden);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    qDebug() << list.size();
}

HttpManager::~HttpManager()
{
    delete mGetInfoManager;
    mGetInfoManager = nullptr;
    delete mDownloadManager;
    mDownloadManager = nullptr;
}

QObject *HttpManager::httpmanager_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    if(mMe == nullptr) {
        mMe = new HttpManager();
    }
    return mMe;
}
