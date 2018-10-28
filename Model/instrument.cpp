#include "instrument.h"
#include "utils.h"
#include "Model/connector.h"
#include "Model/settings.h"
#include <QDebug>
#include <QThread>

Instrument::Instrument(QObject *parent,
                       Settings &config,
                       Connector &conn,
                       QThread& thread) :
    QObject(parent),
    m_isConnected (false),
    m_thread(thread),
    m_setting(config),
    m_connector(conn)
{

}

Instrument::~Instrument()
{
    Utils::DestructorMsg(this);
}


void Instrument::Initialize()
{    //Fake making a TCP connection
    // QThread::msleep(5000);
    InitWithConnector();
}

void Instrument::InitWithConnector()
{
    m_connector.moveToThread(&m_thread);
    connect(&m_thread, &QThread::started,
            &m_connector,&Connector::onStart );
    connect(&m_connector, &Connector::notifyDone,
            this ,&Instrument::onConnectionDone);
    connect(&m_connector, &Connector::notifyMessage,
            this ,&Instrument::onConnectorStatusChanged);
    m_thread.start();


}

void Instrument::onPowerChanged(bool value)
{
    WriteRfPower(value);
}

void Instrument::onDistanceChanged(double value)
{
    WriteDistance(value);
}

void Instrument::onVelocityChanged(double value)
{
    WriteSpeed(value);
}



void Instrument::WriteRfPower(bool value)
{
    if (m_isConnected)
    {
        //SetSynthRfOutput(static_cast<int>(value));
    }
    else
    {
        qDebug() << (value ? "Turning on power" :"Turning off power");
    }
}

void Instrument::WriteDistance(double distanceMeters)
{
    if (m_isConnected)
    {
        //SetDelay(distance_in_ticks);
    }
    else
    {
        qDebug() << "Distance:" << distanceMeters;
    }
}

void Instrument::WriteSpeed(double speedKph)
{
    if (m_isConnected)
    {
        //SetDoppler(speed_nco);
    }
    else
    {
        qDebug() << "Velocity :" << speedKph;
    }
}


void Instrument::onConnectionDone(bool value)
{
    m_isConnected = value;
    if (m_isConnected) SetDefaultValues();
    emit NotifyInitializationDone(value);
    m_thread.quit();
    m_thread.wait();
    qDebug() << "Connection has completed.";
}

void Instrument::onConnectorStatusChanged(const QString &msg)
{
    //Lançando sinal para o além.
    emit NotifyStatusUpdate(msg);
}

void Instrument::SetDefaultValues()
{
    WriteRfPower(m_setting.getInitialPowerState());
    WriteDistance(m_setting.getInitialDistanceM());
    WriteSpeed(m_setting.getInitialSpeedKph());

}
