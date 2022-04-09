#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// classes
#include "CFI_BoxProxy.h"
#include "CFI_LinkProxy.h"
#include "CFI_PageProxy.h"
#include "CFI_Document.h"
#include "CFI_DocumentModel.h"

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    std::unique_ptr<CFI_Document>      pDocument      = std::make_unique<CFI_Document>();
    std::unique_ptr<CFI_DocumentModel> pDocumentModel = std::make_unique<CFI_DocumentModel>(pDocument.get());

    // link document model with document
    pDocument->SetModel(pDocumentModel.get());

    QGuiApplication       app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl            url(QStringLiteral("qrc:/UI/CFI_Main.qml"));

    QObject::connect(&engine,
                     &QQmlApplicationEngine::objectCreated,
                     &app,
                     [url](QObject* pObj, const QUrl& objUrl)
                     {
                         if (!pObj && url == objUrl)
                             QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection);

    // component proxies registration
    qmlRegisterType<CFI_BoxProxy> ("connectflow.proxys", 1, 0, "BoxProxy");
    qmlRegisterType<CFI_LinkProxy>("connectflow.proxys", 1, 0, "LinkProxy");
    qmlRegisterType<CFI_PageProxy>("connectflow.proxys", 1, 0, "PageProxy");

    // model registration
    engine.rootContext()->setContextProperty("cfiDocumentModel", pDocumentModel.get());

    // load the interface
    engine.load(url);

    // add a page to the document
    pDocument->AddPage();

    return app.exec();
}
//---------------------------------------------------------------------------
