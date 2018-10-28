#include "startup.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ViewManager/mainviewmgr.h"
#include "Model/provider.h"
#include "Model/settings.h"

Startup::Startup(QObject *parent) : QObject(parent),
    m_engine(*new QQmlApplicationEngine()),
    m_mainViewMgr(*new MainViewMgr()),
    m_settings (Provider::GetSettingsAsSingleton())
{
    m_settings.ParseJsonData();
    m_mainViewMgr.Initialize(m_settings);
    auto root_context = m_engine.rootContext();
    root_context->setContextProperty("MainViewMgr", &m_mainViewMgr);
     m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}
