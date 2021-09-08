#include "ProcessJson.h"
#include <QDebug>

ProcessJson::ProcessJson()
{

}

void ProcessJson::process(QByteArray array)
{
    nList.clear();
    uList.clear();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(array, &jsonError);
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        qDebug() << "解析完成";
    } else {
        if (document.isNull()) {
            qDebug() << "解析是空的";
        }
        if (jsonError.error != QJsonParseError::NoError) {
            qDebug() << "解析JsonError" << jsonError.error;
        }
    }
    if (document.isArray()) {
        processArray(document);
    } else {
        qDebug() << "不是array";
    }
}

void ProcessJson::processArray(QJsonDocument document)
{
//    QStringList nameinfos;
//    QStringList urlinfos;
    QJsonArray array = document.array();
//    qDebug() << array.size();
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject object = array.at(i).toObject();
        QVariantMap info;
        for (int j = 0; j < object.size(); ++j) {
            if (object.keys().at(j) == "name") {
//                info.insert("name", object.value(object.keys().at(j)).toString());
                nList.push_back(object.value(object.keys().at(j)).toString());
            } else if (object.keys().at(j) == "download_url") {
//                info.insert("url", object.value(object.keys().at(j)).toString());
                uList.push_back(object.value(object.keys().at(j)).toString());
            }
        }
    }
}
