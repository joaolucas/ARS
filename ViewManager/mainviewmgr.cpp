#include "mainviewmgr.h"
#include <iostream>
#include "Model/settings.h"

using std::cout;
using std::endl;

MainViewMgr::MainViewMgr(QObject *parent) : QObject(parent)
{
   appName("Radar Simulator");
   powerOn(false);

   distance(0);
   velocity(0.0);
   velocityPreset1(0);
   velocityPreset2(0);
   velocityPreset3(0);
   velocityPreset4(0);
   distancePreset1(0);
   distancePreset2(0);
   distancePreset3(0);
   distancePreset4(0);
   feedbackAreaVisible(true);
   feedbackMessage("System Initializing....");

}


void MainViewMgr::Initialize(const Settings &config)
{
    appName(config.getApplicationName());
    powerOn(config.getInitialPowerState());
    distance(config.getInitialDistanceM());
    velocity(config.getInitialSpeedKph());
    velocityPreset1(config.getVelocity1());
    velocityPreset2(config.getVelocity2());
    velocityPreset3(config.getVelocity3());
    velocityPreset4(config.getVelocity4());
    distancePreset1(config.getDistance1());
    distancePreset2(config.getDistance2());
    distancePreset3(config.getDistance3());
    distancePreset4(config.getDistance4());
}

void MainViewMgr::onStatusMessageChanged(const QString &msg)
{
    feedbackMessage(msg);
}

void MainViewMgr::onInstrumentInitializationDone(bool value)
{
    if (value)
    {
        feedbackAreaVisible(false);
        instrumentControlsEnabled(true);
    }
    else
    {
        feedbackOKButtonVisible(true);

    }
}
