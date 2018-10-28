#include "connector.h"
#include "utils.h"
#include "Model/settings.h"
#include <QThread>

Connector::Connector(QObject *parent, Settings &config) :
    QObject(parent),
    m_settings(config)
{
}

Connector::~Connector()
{
    Utils::DestructorMsg(this);
}

void Connector::DoWork()
{
    emit notifyMessage("Connecting...");
    auto host_name = m_settings.getHostName().toLocal8Bit();
    char* char_str = host_name.data();
    QThread::msleep(m_settings.getBootDelay());
    emit notifyMessage("Connected.");
    emit notifyDone(true);
}


void Connector::onStart()
{
    DoWork();
}
