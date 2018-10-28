#include "mainviewmgr.h"
#include <iostream>

using std::cout;
using std::endl;

MainViewMgr::MainViewMgr(QObject *parent) : QObject(parent)
{
   appName("Radar Simulator");
   powerOn(false);

   connect(this, &MainViewMgr::powerOnChanged,
           &MainViewMgr::debugPowerOn);
}


void MainViewMgr::debugPowerOn(bool value)
{
    cout << "In debugPowerOn with value:"<< value << endl;
}
