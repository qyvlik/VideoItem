#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "videoitem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<VideoItem>("videoitem",1,5,"VideoItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
