#pragma once
#include <QObject>

QT_FORWARD_DECLARE_CLASS(QString)
QT_FORWARD_DECLARE_CLASS(QStringListModel)
QT_FORWARD_DECLARE_CLASS(QJsonParseError)
QT_FORWARD_DECLARE_CLASS(QJsonObject)
class QFile;
class QDir;

typedef std::pair<QJsonObject,QJsonParseError> JsonObjErrPair;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent, QString filename);

    ~Settings();
    void ParseJsonData();
    QString getApplicationName() const {return m_applicationName;}
    QString getAppShortName() const {return m_appShortName;}
    QString getHostName() const {return m_hostName;}
    double getInitialDistanceM() const {return m_initialDistanceM;}
    double getInitialSpeedKph() const {return m_initialSpeedKph;}
    double getRadarFrequencyGHz() const {return m_radarFreqGhz;}
    int getRxIfAttnDb() const { return m_RxIfAttnDb;}
    int getTxIfAttnDb() const {return m_TxIfAttnDb;}
    bool getInitialPowerState() const {return m_initialPowerState;}
    bool getTestMode() const {return m_testMode;}
    void setTestMode(bool value) {m_testMode = value;}
    int getBootDelay() const {return m_bootDelay;}

    double getDistance1() const {return m_distance1;}
    double getDistance2() const {return m_distance2;}
    double getDistance3() const {return m_distance3;}
    double getDistance4() const {return m_distance4;}

    double getVelocity1() const {return m_speed1;}
    double getVelocity2() const {return m_speed2;}
    double getVelocity3() const {return m_speed3;}
    double getVelocity4() const {return m_speed4;}

signals:
    void NotifyFailure(QString filename);

private:
    QString m_filename;
    QStringListModel& m_modelCommands;

    QString m_applicationName;
    QString m_appShortName;
    QString m_hostName;
    double m_initialDistanceM;
    double m_initialSpeedKph;
    double m_radarFreqGhz;
    int m_RxIfAttnDb;
    int m_TxIfAttnDb;
    bool m_initialPowerState;
    bool m_testMode;
    int m_bootDelay;

    QString m_pwCommand;
    int m_waitMs;
    int m_readWaitMs;

    double m_distance1;
    double m_distance2;
    double m_distance3;
    double m_distance4;

    double m_speed1;
    double m_speed2;
    double m_speed3;
    double m_speed4;

    //NOTE: QVector stores items adjancently in memory QList is optimized
    //for speed of access - probably going to skip this
    //void ReadSettings();
    //        void UseDefaults();

    QString ReadJsonFile();
    JsonObjErrPair GetJsonObject(QString json_raw);
    //QString OpenJsonData();
    QDir OpenConfigDirectory();
    QString ReadJsonFromInternalResource();
    void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString& settings);
    QJsonObject CreateJsonObject();

    void ShowJsonParseError(const QJsonParseError &json_parse_error);
};
