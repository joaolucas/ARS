#include "instrument.h"
#include "utils.h"
#include <QDebug>

Instrument::Instrument(QObject *parent) :
    QObject(parent),
    m_isConnected (false)
{

}

Instrument::~Instrument()
{
    Utils::DestructorMsg(this);
}

void Instrument::onPowerChanged(bool value)
{
    WriteRfPower(value);
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

