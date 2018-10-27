#ifndef MAINVIEWMGR_H
#define MAINVIEWMGR_H

#include <QObject>

class MainViewMgr : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appName READ appName CONSTANT)

public:
    explicit MainViewMgr(QObject *parent = nullptr);
    QString appName() const {return m_appName;}

signals:

public slots:


private:
    QString m_appName;
};


#endif // MAINVIEWMGR_H
