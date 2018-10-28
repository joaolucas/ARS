#ifndef MAINVIEWMGR_H
#define MAINVIEWMGR_H

#include "PropertyHelper.h"

#include <QObject>

class MainViewMgr : public QObject
{
    Q_OBJECT

    READONLY_PROPERTY(QString, appName)
    AUTO_PROPERTY(bool, powerOn)
    // Q_PROPERTY(QString appName READ appName CONSTANT)

    public:
        explicit MainViewMgr(QObject *parent = nullptr);
    //   QString appName() const {return m_appName;}

signals:

public slots:
    void debugPowerOn(bool value);

private:
    //   QString m_appName;
};


#endif // MAINVIEWMGR_H
