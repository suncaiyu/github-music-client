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
    mUrl = url;
    QNetworkReply *replay = mGetInfoManager->get(QNetworkRequest(url));
    connect(replay, &QNetworkReply::finished, this, &HttpManager::GetInfoSlot);
}

void HttpManager::reGetNetworkInfo(QUrl url)
{
    QNetworkReply *replay = mGetInfoManager->get(QNetworkRequest(url));
    connect(replay, &QNetworkReply::finished, this, &HttpManager::reGetInfoSlot);
}

void HttpManager::downLoad(QString i, QString name)
{
    qDebug() << i;
    qDebug() << name;
    QDir folder(qApp->applicationDirPath() + "/Music");
    if (!folder.exists()) {
        folder.mkdir(qApp->applicationDirPath() + "/Music");
    }
    folder.setFilter(QDir::Files|QDir::Hidden);
    folder.setSorting(QDir::DirsFirst);
    QFileInfoList list = folder.entryInfoList();
    QNetworkReply *replay = mDownloadManager->get(QNetworkRequest(i));
    qDebug() << replay->error();
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i).fileName() == name) {
            emit readyOk(QDir::fromNativeSeparators(qApp->applicationDirPath() + "/Music/" + name));
            return;
        }
    }
    mDownLoadFile = new QFile(QCoreApplication::applicationDirPath() + "/Music/unknown");
    mDownLoadFile->open(QIODevice::WriteOnly);
    connect(replay, &QNetworkReply::readyRead, this, [this](){
        QNetworkReply *r = qobject_cast<QNetworkReply *>(sender());
        if (r->error() != QNetworkReply::NoError) {
            qDebug() << "has error : " << r->error();
            errorMessageSignal("has error Code:" + QString::number(r->error()));
            return;
        }
        mDownLoadFile->write(r->readAll());
    });
    connect(replay, &QNetworkReply::downloadProgress, this, [this](qint64 cur, qint64 all){
        QNetworkReply *r = qobject_cast<QNetworkReply *>(sender());
        if (r->error() != QNetworkReply::NoError) {
            qDebug() << "has error : " << r->error();
            errorMessageSignal("has error Code:" + QString::number(r->error()));
            return;
        }
        qDebug() << all << "---->" << cur;
    });
    connect(replay, &QNetworkReply::finished, this, [this, name](){
        QNetworkReply *r = qobject_cast<QNetworkReply *>(sender());
        if (r->error() != QNetworkReply::NoError) {
            qDebug() << "has error : " << r->error();
            errorMessageSignal("has error Code:" + QString::number(r->error()));
            return;
        }
        mDownLoadFile->close();
        if (mDownLoadFile->size() == 0) {
            qDebug() << "文件大小是0";
            errorMessageSignal("文件大小是0");
            return;
        }
        mDownLoadFile->rename(qApp->applicationDirPath() + "/Music/" + name);
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
    mPJson->process(info);
}

void HttpManager::reGetInfoSlot()
{
    QNetworkReply *replay = qobject_cast<QNetworkReply *>(this->sender());
    mUrl = replay->url();
    QByteArray info = replay->readAll();
    mPJson->process(info, false);
}

HttpManager::HttpManager()
{
    mGetInfoManager = new QNetworkAccessManager;
    mDownloadManager = new QNetworkAccessManager;
    QDir dir(qApp->applicationDirPath() + "/Music/");
    dir.setFilter(QDir::Files|QDir::Hidden);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    mPJson = new ProcessJson;
    connect(mPJson, &ProcessJson::searchOk, this, [this](){
        mUrl.clear();
        emit updateList();
        qDebug() << mPJson->nameList().size();
    });
    connect(mPJson, &ProcessJson::research, this, [this](QStringList dirs){
        for(int i = 0; i < dirs.size(); ++i) {
            QUrl tmp = QUrl(mUrl.toString() + "/" + dirs[i]);
            reGetNetworkInfo(tmp);
        }
    });
}

HttpManager::~HttpManager()
{
    delete mGetInfoManager;
    mGetInfoManager = nullptr;
    delete mDownloadManager;
    mDownloadManager = nullptr;
    delete mPJson;
    mPJson = nullptr;
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
