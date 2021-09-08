#ifndef PROCESSJSON_H
#define PROCESSJSON_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include<QVariantList>
class ProcessJson : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList nameList READ nameList WRITE setNameList)
    Q_PROPERTY(QStringList urlList READ urlList WRITE setUrlList)
public:
    ProcessJson();
    Q_INVOKABLE void process(QByteArray);
    Q_INVOKABLE int test() {return 111;}
    Q_INVOKABLE void processArray(QJsonDocument);
    QStringList nameList() {
        return nList;
    }

    void setNameList(QStringList l) {nList = l;};
    QStringList urlList(){
        return uList;
    };
    void setUrlList(QStringList l) {uList = l;};
private:
    QStringList nList;
    QStringList uList;
};

#endif // PROCESSJSON_H
