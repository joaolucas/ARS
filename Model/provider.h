#pragma once
#include <memory>


    class Settings;
    class Connector;

    class Provider final
    {
    public:
        ~Provider();
        static Settings& GetSettingsAsSingleton();
        static Connector& GetConnectorForSingleUse();

    private:
        static std::unique_ptr<Settings> m_instanceSettings;
        static std::unique_ptr<Connector>m_instanceConnector;

    };




