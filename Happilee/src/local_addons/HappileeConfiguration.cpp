//
//  HappileeConfiguration.cpp
//  Happilee
//
//  Created by David Haylock on 24/06/2016.
//
//

#include "HappileeConfiguration.h"
//--------------------------------------------------------------
void HappileeConfiguration::load(string loadFile)
{
    if (!configFile.open(loadFile)) {
        // Oh No!!!
        ofLog(OF_LOG_FATAL_ERROR,"Could not find the Configuration File");
        return;
    }
    else {
        c.greenMemoryReduction = configFile["config"]["reductionamounts"]["green"].asInt();
        c.yellowMemoryReduction = configFile["config"]["reductionamounts"]["yellow"].asInt();
        c.redMemoryReduction = configFile["config"]["reductionamounts"]["red"].asInt();
        
        c.greenMemoryReductionTimerLength = configFile["config"]["reductiontimers"]["green"].asInt();
        c.yellowMemoryReductionTimerLength = configFile["config"]["reductiontimers"]["yellow"].asInt();
        c.redMemoryReductionTimerLength = configFile["config"]["reductiontimers"]["red"].asInt();
        c.malfunctionTimerLength = configFile["config"]["reductiontimers"]["malfunction"].asInt();
        
        c.memoryAmount = configFile["config"]["memoryamount"].asInt();
        c.lowMemoryAmount = configFile["config"]["lowmemoryamount"].asInt();
    }
}
//--------------------------------------------------------------
Config HappileeConfiguration::getConfig()
{
    return c;
}
//--------------------------------------------------------------
void HappileeConfiguration::printConfiguration()
{
    cout << configFile.getRawString() << endl;
}