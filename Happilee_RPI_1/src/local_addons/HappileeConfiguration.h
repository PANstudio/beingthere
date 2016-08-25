//
//  HappileeConfiguration.h
//  Happilee
//
//  Created by David Haylock on 24/06/2016.
//
//

#ifndef HappileeConfiguration_h
#define HappileeConfiguration_h

#include <stdio.h>
#include "ofxJSON.h"

struct Config {
    
    int greenMemoryReduction;
    int yellowMemoryReduction;
    int redMemoryReduction;
    
    int malfunctionTimerLength;
    int greenMemoryReductionTimerLength;
    int yellowMemoryReductionTimerLength;
    int redMemoryReductionTimerLength;
    
    int memoryAmount;
    int lowMemoryAmount;
    
};

class HappileeConfiguration {
    public:
        void load(string configFile);
        Config getConfig();
        void printConfiguration();
    private:
        Config c;
    protected:
        ofxJSONElement configFile;
};

#endif /* HappileeConfiguration_h */
