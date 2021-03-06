#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "TestWidget.h"
#include "HttpManager.h"
#include "ProcessJson.h"
#include "ListSettings.h"
#include "SystemIcon.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
    QApplication app(argc, argv);
    qmlRegisterSingletonType<HttpManager>("Furrain.HttpManager", 1, 0, "HttpManager", HttpManager::httpmanager_qobject_singletontype_provider);
    qmlRegisterSingletonType<ListSettings>("Furrain.Settings", 1, 0, "Settings", ListSettings::qml_getisntance);
    qmlRegisterType<ProcessJson>("Furrain.ProcessJson", 1, 0, "ProcessJson");
    qmlRegisterType<SystemIcon>("Furrain.SystemIcon", 1, 0, "SystemIcon");
    int fontId = QFontDatabase::addApplicationFont(":/font/res/font/fontawesome-webfont.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
