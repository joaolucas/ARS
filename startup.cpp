#include "startup.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ViewManager/mainviewmgr.h"

Startup::Startup(QObject *parent) : QObject(parent),
    m_engine(*new QQmlApplicationEngine()),
    m_mainViewMgr(*new MainViewMgr())
{
    auto root_context = m_engine.rootContext();
    root_context->setContextProperty("MainViewMgr", &m_mainViewMgr);
     m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}
