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

signals:

public slots:
    void onPowerChanged(bool value);

private:
    bool m_isConnected;
    void WriteRfPower(bool value);
};

#endif // INTRUMENT_H
