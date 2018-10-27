#ifndef STARTUP_H
#define STARTUP_H
#include <QObject>

class QQmlApplicationEngine;
class MainViewMgr;

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
};

#endif // STARTUP_H
