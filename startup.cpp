#include "startup.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ViewManager/mainviewmgr.h"
#include "Model/provider.h"
#include "Model/settings.h"
#include "Model/instrument.h"

Startup::Startup(QObject *parent) : QObject(parent),
    m_engine(*new QQmlApplicationEngine()),
    m_mainViewMgr(*new MainViewMgr()),
    m_settings (Provider::GetSettingsAsSingleton()),
    m_instrument(*new Instrument(this))
{
    m_settings.ParseJsonData();
    m_mainViewMgr.Initialize(m_settings);
    auto root_context = m_engine.rootContext();
    root_context->setContextProperty("MainViewMgr", &m_mainViewMgr);
     m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

     WireMainViewMgrToInstrument();
}

void Startup::WireMainViewMgrToInstrument()
{
     connect(&m_mainViewMgr, &MainViewMgr::powerOnChanged,
              &m_instrument,&Instrument::onPowerChanged);

     connect(&m_mainViewMgr, &MainViewMgr::distanceChanged,
              &m_instrument,&Instrument::onDistanceChanged);

     connect(&m_mainViewMgr, &MainViewMgr::velocityChanged,
              &m_instrument,&Instrument::onVelocityChanged);
}
