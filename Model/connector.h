#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
class QString;
class Settings;

class Connector : public QObject
{
    Q_OBJECT
public:
    explicit Connector(QObject *parent, Settings &config);
   ~Connector();
   void DoWork();

signals:
    void notifyDone(bool value);
    void notifyMessage(const QString& msg);

public slots:
      void onStart();

private:
    Settings& m_settings;
};

#endif // CONNECTOR_H
