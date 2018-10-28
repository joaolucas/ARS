#include "startup.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include "ViewManager/mainviewmgr.h"
#include "Model/provider.h"
#include "Model/settings.h"
#include "Model/instrument.h"
#include <QThread>

const int TIMER_INTERVAL = 250;

Startup::Startup(QObject *parent) : QObject(parent),
    m_engine(*new QQmlApplicationEngine()),
    m_mainViewMgr(*new MainViewMgr()),
    m_settings (Provider::GetSettingsAsSingleton()),
    m_instrument(*new Instrument(this,
                                 m_settings,
                                 Provider::GetConnectorForSingleUse(),
                                 * new QThread())),
    m_bootDelay(0),
    m_timer(*new QTimer(this))
{
    m_settings.ParseJsonData();
    m_mainViewMgr.Initialize(m_settings);
    auto root_context = m_engine.rootContext();
    root_context->setContextProperty("MainViewMgr", &m_mainViewMgr);
    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    WireMainViewMgrToInstrument();
    WireInstrumentToMainViewMgr();
    setupBootDelayTimer();
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

void Startup::onTimerFired()
{
    static int counter;
    ++counter;
    float elapsed_time = TIMER_INTERVAL* counter;
    float progress = (elapsed_time/m_bootDelay) * 100.0;
    m_mainViewMgr.feedbackProgress(progress);
    if (progress > 100)
    {
        m_instrument.Initialize();
        m_timer.stop();
    }
}

void Startup::setupBootDelayTimer()
{
    m_bootDelay = m_settings.getBootDelay();
    bool in_test_mode = m_settings.getTestMode();
    if (in_test_mode) m_bootDelay = 5000;
    m_timer.setInterval(TIMER_INTERVAL);
    connect(&m_timer,SIGNAL(timeout()),SLOT(onTimerFired()));
     m_timer.start();
}

void Startup::WireInstrumentToMainViewMgr()
{
    connect(&m_instrument, &Instrument::NotifyStatusUpdate,
            &m_mainViewMgr, &MainViewMgr::onStatusMessageChanged);
    connect(&m_instrument, &Instrument::NotifyInitializationDone,
            &m_mainViewMgr, &MainViewMgr::onInstrumentInitializationDone);

}
