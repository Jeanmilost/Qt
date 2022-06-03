#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// classes
#include "TreeModel.h"

//---------------------------------------------------------------------------
class TreeItemNameGen
{
    public:
        TreeItemNameGen()
        {}

        virtual ~TreeItemNameGen()
        {}

        virtual QString GetNextName(TreeItem* pItem)
        {
            ++m_GenCount;
            return QString::fromStdWString((L"Item " + std::to_wstring(m_GenCount)).c_str());
        }

    private:
        std::size_t m_GenCount = 0;
};
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

    TreeItem* pItemA   = pModel->AddItem(nullptr, L"Item A");
    TreeItem* pItemB   = pModel->AddItem(nullptr, L"Item B");
    TreeItem* pItemC   = pModel->AddItem(nullptr, L"Item C");
    TreeItem* pItemD   = pModel->AddItem(nullptr, L"Item D");
    TreeItem* pItemA1  = pModel->AddItem(pItemA,  L"Item A - 1");
    TreeItem* pItemA2  = pModel->AddItem(pItemA,  L"Item A - 2");
    TreeItem* pItemA3  = pModel->AddItem(pItemA,  L"Item A - 3");
    TreeItem* pItemA4  = pModel->AddItem(pItemA,  L"Item A - 4");
    TreeItem* pItemA21 = pModel->AddItem(pItemA2, L"Item A - 2 - 1");
    TreeItem* pItemA22 = pModel->AddItem(pItemA2, L"Item A - 2 - 2");
    TreeItem* pItemA23 = pModel->AddItem(pItemA2, L"Item A - 2 - 3");
    TreeItem* pItemC1  = pModel->AddItem(pItemC,  L"Item C - 1");
    TreeItem* pItemC2  = pModel->AddItem(pItemC,  L"Item C - 2");
    TreeItem* pItemC3  = pModel->AddItem(pItemC,  L"Item C - 3");
    TreeItem* pItemC4  = pModel->AddItem(pItemC,  L"Item C - 4");
    TreeItem* pItemC11 = pModel->AddItem(pItemC1, L"Item C - 1 - 1");
    TreeItem* pItemC12 = pModel->AddItem(pItemC1, L"Item C - 1 - 2");
    TreeItem* pItemC13 = pModel->AddItem(pItemC1, L"Item C - 1 - 3");

    TreeItemNameGen nameGen;

    // register a lambda function to get the next available item name
    pModel->Set_OnGetItemName([&nameGen](TreeItem* pItem) -> QString
    {
        return nameGen.GetNextName(pItem);
    });

    return app.exec();
}
//---------------------------------------------------------------------------
