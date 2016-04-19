//--------------------------------------------------------------
//
//  RobotManager.h
//  H_A_R_P_S
//
//  Created by David Haylock on 14/11/2015.
//
//--------------------------------------------------------------

#ifndef RobotManager_h
#define RobotManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxJSON.h"

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
enum ROBOT_COMMAND {
    HPL_REDUCE_HEALTH = 0,
    HPL_RESET_HEALTH,
    HPL_MALFUNCTION,
    HPL_START,
    HPL_INSTRUCTIONS,
    HPL_FLASH_LIGHTS,
    HPL_TURN_OFF_SCREEN,
    HPL_TURN_ON_SCREEN,
    HPL_EXTEND_AERIAL,
    HPL_RETRACT_AERIAL,
    HPL_IN_DANGER,
    HPL_IS_OK
};


class RobotManager {

    public:
        void setup();
        void loadCommands();
        void update();
        void fireCommand(int whichRobot, int command);
        void draw(int x, int y);
        void close();
        
    protected:
        vector <string> sendingTo;
        int _port;
        map<int,string> commands;
        vector <string> receiversHostname;
        vector <deque<string> > commandsSent;
        map<string,ofxOscSender> senders;
};

#endif /* RobotManager_h */