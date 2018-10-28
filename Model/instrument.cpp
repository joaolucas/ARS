#include "instrument.h"
#include "utils.h"
#include <QDebug>
#include <QThread>

Instrument::Instrument(QObject *parent) :
    QObject(parent),
    m_isConnected (false)
{

}

Instrument::~Instrument()
{
    Utils::DestructorMsg(this);
}


void Instrument::Initialize()
{    //Fake making a TCP connection
    QThread::msleep(5000);
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

