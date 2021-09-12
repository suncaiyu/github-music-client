#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QSettings>
class Manager;
class ListSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList mUrl READ URL WRITE SetUrl);
    Q_PROPERTY(QStringList mName READ Name WRITE SetName);
public:
    static ListSettings *GetInstance() {
        if (mListSettings == nullptr) {
            mListSettings = new ListSettings;
        }
        return mListSettings;
    }
    static QObject *qml_getisntance(QQmlEngine *engine, QJSEngine *scriptEngine);
    Q_INVOKABLE void addInfo(QString url, QString name);
    Q_INVOKABLE void removeInof(QString url);
    Q_INVOKABLE void getInfo();
    void SetUrl(QStringList u) {mUrl = u;}
    QStringList URL() {return mUrl;}
    void SetName(QStringList n) {mName = n;}
    QStringList Name() {return mName;}
private:
    ListSettings();
    ~ListSettings();
    static ListSettings *mListSettings;
    QSettings *mSettings = nullptr;
    QStringList mUrl;
    QStringList mName;
    class Manager{
    private :
        Manager();
        ~Manager() {
            if (mListSettings) {
                delete mListSettings;
                mListSettings = nullptr;
            }
        };
    };
    static Manager mManager;
};

#endif // LISTSETTINGS_H
