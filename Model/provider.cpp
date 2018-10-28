#include "provider.h"
#include "Model/settings.h"
//#include "Model/connector.h"
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include "utils.h"

    static QString SETTINGS_FILE = QStringLiteral("settings.json");

    std::unique_ptr<Settings> Provider::m_instanceSettings =nullptr;
 //   std::unique_ptr<Connector> Provider::m_instanceConnector = nullptr;
    Settings& Provider::GetSettingsAsSingleton()
    {
        if (m_instanceSettings == 0)
        {
            m_instanceSettings = Utils::make_unique<Settings>(nullptr,SETTINGS_FILE);
        }
        return *m_instanceSettings;
    }

//    Connector& Provider::GetConnectorForSingleUse(){
//        if (m_instanceConnector == 0)
//        {
//            m_instanceConnector = Utils::make_unique<Connector> (nullptr,GetSettingsAsSingleton());
//        }
//        return *m_instanceConnector;
//    }

