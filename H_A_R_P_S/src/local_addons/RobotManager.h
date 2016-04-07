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

//-----------------------
// * reduceHealth = reH;
// * resetHealth = reset;
// * malfunction = malf;
// * start = str;
// * instructions = inst;
// * flashLights = fL;
// * turnOffScreen = tIOS;
// * turnOnScreen = tOOS;
// * extendAerial = eA;
// * retractAerial = rA;
//-----------------------
struct Commands {
    string reduceHealth;
    string resetHealth;
    string malfunction;
    string start;
    string instructions;
    string flashLights;
    string turnOffScreen;
    string turnOnScreen;
    string extendAerial;
    string retractAerial;
};

class RobotManager {

public:
    void setup(string sendingTo, int port,string commandsFile);
    void loadCommands(Commands commandStrings);
    void update();
    void fireCommand(int enumCommand);
    void draw(int x, int y);
    void close();
    
protected:
    string _sendingTo;
    int _port;
    Commands commands;
};

#endif /* RobotManager_h */