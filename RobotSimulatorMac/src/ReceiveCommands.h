//
//  ReceiveCommands.h
//  HARPSRobotSimulator
//
//  Created by David Haylock on 18/04/2016.
//
//

#ifndef ReceiveCommands_h
#define ReceiveCommands_h

#include <stdio.h>
#include "ofxOsc.h"
#include "ofMain.h"

//-----------------------
// * reduceHealth = RreH;
// * resetHealth = Rreset;
// * malfunction = Rmalf;
// * start = Rstr;
// * instructions = Rinst;
// * flashLights = RfL;
// * turnOffScreen = RtIOS;
// * turnOnScreen = RtOOS;
// * extendAerial = ReA;
// * retractAerial = RrA;
//-----------------------

class ReceiveCommands : public ofThread {
    
    public:
        void setup(int port);
        void update();
        void draw();
    
        void startListening();
        void stopListening();
        void threadedFunction();
    
        ofEvent<string>resetHealth;
        ofEvent<string>reduceHealth;
        ofEvent<string>malfunction;
        ofEvent<string>start;
        ofEvent<string>instruction;
        ofEvent<string>flashLights;
        ofEvent<string>inDanger;
        ofEvent<string>okDanger;
        ofEvent<ofImage>gotImage;
    private:
        ofxOscReceiver receiver;
        ofImage ew;
    protected:
    
};


#endif /* ReceiveCommands_h */
