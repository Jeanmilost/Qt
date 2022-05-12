#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// classes
#include "TreeModel.h"

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication            app(argc, argv);
    QQmlApplicationEngine      engine;
    const QUrl                 url(QStringLiteral("qrc:/Resources/UI/main.qml"));
    std::unique_ptr<TreeModel> pModel = std::make_unique<TreeModel>();


    QObject::connect(&engine,
                     &QQmlApplicationEngine::objectCreated,
                     &app,
                     [url](QObject* pObj, const QUrl& objUrl)
                     {
                         if (!pObj && url == objUrl)
                             QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection);

    // models registration
    engine.rootContext()->setContextProperty("tmTreeModel", pModel.get());

    engine.load(url);

    return app.exec();
}
//---------------------------------------------------------------------------
