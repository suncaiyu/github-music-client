#include "ProcessJson.h"
#include <QDebug>

ProcessJson::ProcessJson()
{

}

void ProcessJson::process(QByteArray array, bool flag)
{
    if (flag) {
        nList.clear();
        uList.clear();
    }
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(array, &jsonError);
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        qDebug() << "Parse is ok";
    } else {
        if (document.isNull()) {
            qDebug() << "Parse is null";
        }
        if (jsonError.error != QJsonParseError::NoError) {
            qDebug() << "Parse JsonError" << jsonError.error;
        }
    }
    if (document.isArray()) {
        processArray(document);
    } else {
        qDebug() << "not array";
    }
}

void ProcessJson::processArray(QJsonDocument document)
{
    QStringList dirList;
    QJsonArray array = document.array();
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject object = array.at(i).toObject();
        if (object.value("type").toString() != "file") {
            if (object.value("size").toInt() == 0) {
                dirList.push_back(object.value("name").toString());
            }
            continue;
        }
        QString fileName = object.value("name").toString();
        if (fileName.endsWith("mp3") || fileName.endsWith("m4a") || fileName.endsWith("flac")) {
            nList.push_back(object.value("name").toString());
            uList.push_back(object.value("download_url").toString());
        }
    }
    if (dirList.size() == 0) {
        emit searchOk();
    } else {
        emit research(dirList);
    }
}
