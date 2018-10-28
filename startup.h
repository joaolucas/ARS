#ifndef STARTUP_H
#define STARTUP_H
#include <QObject>

class QQmlApplicationEngine;
class MainViewMgr;
class Settings;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup(QObject *parent = nullptr);

signals:

public slots:

private:
    QQmlApplicationEngine& m_engine;
    MainViewMgr& m_mainViewMgr;
    Settings& m_settings;
};

#endif // STARTUP_H
