#ifndef MAINVIEWMGR_H
#define MAINVIEWMGR_H

#include "PropertyHelper.h"
#include "Model/settings.h"

#include <QObject>

class MainViewMgr : public QObject
{
    Q_OBJECT

    READONLY_PROPERTY(QString, appName)
    AUTO_PROPERTY(bool, powerOn)
    AUTO_PROPERTY(double, distance)
    AUTO_PROPERTY(double, velocity)

    READONLY_PROPERTY (double, distancePreset1)
    READONLY_PROPERTY (double, velocityPreset1)
    READONLY_PROPERTY (double, distancePreset2)
    READONLY_PROPERTY (double, velocityPreset2)
    READONLY_PROPERTY (double, distancePreset3)
    READONLY_PROPERTY (double, velocityPreset3)
    READONLY_PROPERTY (double, distancePreset4)
    READONLY_PROPERTY (double, velocityPreset4)
    // Q_PROPERTY(QString appName READ appName CONSTANT)

    public:
        explicit MainViewMgr(QObject *parent = nullptr);
      void Initialize(const Settings& config);
    //   QString appName() const {return m_appName;}

signals:

public slots:
    void debugPowerOn(bool value);
    void debugVelocityChange(bool value);
    void debugDistanceChange(bool value);


private:
    //   QString m_appName;
};


#endif // MAINVIEWMGR_H
