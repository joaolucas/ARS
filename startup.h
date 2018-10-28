#ifndef STARTUP_H
#define STARTUP_H
#include <QObject>

class QQmlApplicationEngine;
class QTimer;
class MainViewMgr;
class Settings;
class Instrument;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup(QObject *parent = nullptr);

signals:

public slots:
      void onTimerFired();

private:
    QQmlApplicationEngine& m_engine;
    MainViewMgr& m_mainViewMgr;
    Settings& m_settings;
    Instrument& m_instrument;
    int m_bootDelay;
    QTimer& m_timer;

    void WireMainViewMgrToInstrument();
    void WireInstrumentToMainViewMgr();
    void setupBootDelayTimer();
};

#endif // STARTUP_H
