#include "ListSettings.h"
#include <QDebug>
ListSettings *ListSettings::mListSettings = nullptr;
QObject *ListSettings::qml_getisntance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    if (mListSettings == nullptr) {
        mListSettings = new ListSettings;
    }
    return mListSettings;
}

void ListSettings::addInfo(QString url, QString name)
{
    mSettings->setValue("music_list/" + url, name);
}

void ListSettings::removeInof(QString url)
{
    mSettings->remove("music_list/" + url);
}

void ListSettings::getInfo()
{
    mUrl.clear();
    mName.clear();
    mSettings->beginGroup("music_list");
    mName = mSettings->childKeys();
    for (int i = 0; i < mName.size(); i++) {
        mUrl.push_back(mSettings->value(mName.at(i)).toString());
    }
    mSettings->endGroup();
}

ListSettings::ListSettings()
{
    mSettings = new QSettings("Config.ini", QSettings::IniFormat);
//    mSettings->clear();
//    mSettings->beginGroup("music_list");
//        mSettings->setValue("suncaiyu", "https://api.github.com/repos/suncaiyu/music/contents");
//        mSettings->endGroup();
}

ListSettings::~ListSettings()
{
    delete mSettings;
    mSettings = nullptr;
}
