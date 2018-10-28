#ifndef INTRUMENT_H
#define INTRUMENT_H

#include <QObject>

class Settings;
class QThread;
class Instrument : public QObject
{
    Q_OBJECT
public:
    explicit Instrument(QObject *parent);
    virtual ~Instrument();
    bool IsConnected() const {return m_isConnected;}
    void EnableTestMode();
    void Initialize();

signals:

public slots:
    void onPowerChanged(bool value);
    void onDistanceChanged(double value);
    void onVelocityChanged(double value);

private:
    bool m_isConnected;
    void WriteRfPower(bool value);
    void WriteSpeed(double speedKph);
    void WriteDistance(double distanceMeters);
};

#endif // INTRUMENT_H
