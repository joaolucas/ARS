#ifndef INTRUMENT_H
#define INTRUMENT_H

#include <QObject>

class Settings;
class Connector;
class QThread;
class Instrument : public QObject
{
    Q_OBJECT
public:
    explicit Instrument(QObject *parent
                        , Settings& config
                        , Connector& conn
                        , QThread &thread);
    virtual ~Instrument();
    bool IsConnected() const {return m_isConnected;}
    void EnableTestMode();
    void Initialize();

signals:
    void NotifyInitializationDone(bool value);
    void NotifyStatusUpdate(const QString& msg);


public slots:
    void onPowerChanged(bool value);
    void onDistanceChanged(double value);
    void onVelocityChanged(double value);
    void onConnectionDone(bool value);
    void onConnectorStatusChanged(const QString& msg);


private:
    bool m_isConnected;
    QThread& m_thread;
    Settings& m_setting;
    bool m_testMode;
    Connector& m_connector;

    void WriteRfPower(bool value);
    void WriteSpeed(double speedKph);
    void WriteDistance(double distanceMeters);

    void InitWithConnector();
    void SetDefaultValues();
};

#endif // INTRUMENT_H
