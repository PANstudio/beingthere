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
    HPL_REBOOT = 0,
    HPL_GREEN_ZONE,
    HPL_YELLOW_ZONE,
    HPL_RED_ZONE,
    HPL_SAFE_ZONE,
    HPL_RESET_MEMORY,
    HPL_MALFUNCTION,
    HPL_SEND_MAP
};

struct cmds {
    string cmd;
    string cmdname;
};

class RobotManager {

    public:
        void setup();
        void loadCommands();
        map <int,cmds> getCommands();
        void update();
        void getMap(string mapName);
        void fireCommand(int whichRobot, int command);
        void draw(int x, int y);
        void close();
        
    protected:
        vector <string> sendingTo;
        int _port;
        map<int,cmds> commands;
        vector <string> receiversHostname;
        vector <deque<string> > commandsSent;
        map<string,ofxOscSender> senders;
        ofImage _map;
        ofBuffer imgAsBuffer;
        ofImage img;
};

#endif /* RobotManager_h */