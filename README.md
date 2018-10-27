# ARS

Esse projeto é a minha segunda sessão de estudo de qt. Irei fazer uma aplicação mais complexa.

## Ponto 1 
- Para iniciar criei um novo projeto e configurei o main.cpp definindo um id e uma resolução de tela. 
```c++
Window {
    id: mainViewWindow
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello World")
}
```

- Próximo passo foi criar uma nova classe Startup e definir uma referencia privata para QQmlApplicationEngine.
```c++
private:
    QQmlApplicationEngine& m_engine;
```

- Agora meu objetivo é ter apenas uma ponto de contato entre o qml e c++. Tendo desse forma uma classe de gerenciamento a view principal. Criarei um classe chamda MainViewMgr para gerenciar o main view e colocarei em uma pasta ViewManager. 

- Depois que criar a classe irei criar um propriedade privada do MainViewMgr na classe de Startup 
```c++
private:
    QQmlApplicationEngine& m_engine;
    MainViewMgr& m_mainViewMgr;
};
```
- Precisamos o MainViewMgr no context do qml. 
```c++

    auto root_context = m_engine.rootContext();
    root_context->setContextProperty("MainViewMgr", &m_mainViewMgr);
    
```

- Agora que temos uma organizar melhor do projeto iremos criar uma propriedade para o título de aplicação. Como o titulo não ser modificado pela aplicação criaremos uma propriedade somente de leitura e que seja uma constante. 
```c++
    Q_PROPERTY(QString appName READ appName CONSTANT)

public:
    QString appName() const {return m_appName;}
    
private:
    QString m_appName;
```

- Iniciaremos o nome da aplicação como Simulador
```c++
#include "mainviewmgr.h"

MainViewMgr::MainViewMgr(QObject *parent) : QObject(parent),
    m_appName("Radar Simulator")
{

}
```

- Precisamos colocar na main.qml a propriedade com nome da aplicação 
```qml
   title: qsTr(MainViewMgr.appName)
```

- Refatorando o classe main.cpp retiraremos a engine e colocaremos a referencia para o startup
```c++
#include <QGuiApplication>
#include <startup.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Startup my_startup;
    return app.exec();
}
```
