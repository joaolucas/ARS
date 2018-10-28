#include "settings.h"
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <QJsonArray>
#include <QStringListModel>

#include <utility> //for std::pair
#include "utils.h" //for destructor msg
Settings::Settings(QObject *parent, QString filename) :
    QObject(parent),
    m_filename(filename),
    m_modelCommands (*new QStringListModel(this)),
    m_testMode (true),
    m_bootDelay(1000)
{
    //UseDefaults();
    // ParseJsonData();

}

Settings::~Settings()
{
    Utils::DestructorMsg(this);
}

void Settings::ParseJsonData()
{
    QString json_raw = ReadJsonFile();
    if (json_raw.size() ==0) return;

    auto json_pair = GetJsonObject(json_raw);
    auto json_err = json_pair.second;

    if (json_err.error == QJsonParseError::NoError)
    {
        auto json_obj = json_pair.first;
        m_applicationName = json_obj["applicationTitle"].toString();
        m_appShortName = json_obj["appShortName"].toString();
        m_hostName = json_obj["hostName"].toString();
        m_waitMs = json_obj["tcpWaitMs"].toInt();
        m_readWaitMs = json_obj["readWaitMs"].toInt();
        m_initialSpeedKph = json_obj["initialSpeedKph"].toDouble();
        m_initialDistanceM = json_obj ["initialDistanceM"].toDouble();
        m_radarFreqGhz = json_obj["radarFrequencyGhz"].toDouble();
        m_RxIfAttnDb = json_obj["rxIfAttenDb"].toInt();
        m_TxIfAttnDb = json_obj["txIfAttenDb"].toInt();
        m_initialPowerState = json_obj["initialPowerState"].toBool();
        m_testMode = json_obj["testMode"].toBool();
        m_bootDelay = json_obj["bootDelay"].toInt();

        m_distance1 = json_obj["distance1"].toDouble();
        m_distance2 = json_obj["distance2"].toDouble();
        m_distance3 = json_obj["distance3"].toDouble();
        m_distance4 = json_obj["distance4"].toDouble();

        m_speed1= json_obj["speed1"].toDouble();
        m_speed2= json_obj["speed2"].toDouble();
        m_speed3= json_obj["speed3"].toDouble();
        m_speed4= json_obj["speed4"].toDouble();
    }
}

//NOTE: Newly added for Qt Quick version
//QStringList Settings::getCommandsAsStringList() const
//{
//    return m_modelCommands.stringList();
//}

QString Settings::ReadJsonFile()
{
    auto default_settings = ReadJsonFromInternalResource();
    QDir config_dir = OpenConfigDirectory();
    auto path = config_dir.filePath(m_filename);
    QFile std_file (path);
    if (std_file.exists())
    {
        if (!std_file.open(QFile::ReadOnly|QFile::Text))
        {
            emit NotifyFailure("Could not open " + path);
            return default_settings;
        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    }
    else
    {
        WriteDefaultsToStdConfigFile(std_file,default_settings);
        return default_settings;
    }
}

QString Settings::ReadJsonFromInternalResource()
{
    QDir res_dir (":/json");
    if (!res_dir.exists())
    {
        emit NotifyFailure("Internal resource path missing " + res_dir.canonicalPath());
        return "";
    }
    auto path = res_dir.filePath(m_filename);
    QFile res_file (path);
    if (!res_file.open(QFile::ReadOnly|QFile::Text))
    {
        emit NotifyFailure("Could not open internal resource-" + path);
        return "";
    }
    QString settings = res_file.readAll();
    return settings;
}

QDir Settings::OpenConfigDirectory()
{
    QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation ));
    if (!config_dir.exists())
    {
        QDir dir;
        dir.mkpath(config_dir.path());
    }
    return config_dir;
}


void Settings::WriteDefaultsToStdConfigFile(QFile& stdConfigFile, const QString &settings)
{
    int length = settings.length();
    if (!stdConfigFile.open(QFile::WriteOnly|QFile::Text))
    {
        emit NotifyFailure("Could not open file to write - "+ stdConfigFile.fileName());
    }

    auto bytes_written = stdConfigFile.write(qPrintable(settings),length );
    if (bytes_written != length)
    {
        NotifyFailure("Could not write the settings to -"+ stdConfigFile.fileName());
        if (!stdConfigFile.remove())
        {
            NotifyFailure("Couldn't remove configuration file. Please delete manually"+
                          stdConfigFile.fileName());
        }
    }
    stdConfigFile.close();
}



JsonObjErrPair Settings::GetJsonObject(QString json_raw)
{
    QJsonParseError json_parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_raw.toUtf8(),
                                                     &json_parse_error);
    ShowJsonParseError(json_parse_error);
    QJsonObject json_obj = json_doc.object();
    return std::make_pair(json_obj,json_parse_error);
}

void Settings::ShowJsonParseError(const QJsonParseError& json_parse_error)
{
    if (json_parse_error.error != QJsonParseError::NoError)
    {
        QString msg = tr("Error parsing Json settings file.\n");
        msg.append(json_parse_error.errorString());
        msg.append( tr("\nThe default values will be used."));
       // QMessageBox::critical(0,tr("VFP"),msg);
    }
}



