//--------------------------------------------------------------
//
//  PlayerManager.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef PlayerManager_hpp
#define PlayerManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"

class PlayerManager {
public:
    void setup(string address,int port);
    void listen();
    void closeListener();
    
    string getDebugData();
    
    ofPoint getPlayerCoords();
    vector<ofPoint> getPlayersCoords();
    
private:
    ofxOscReceiver oscReceiver;
    
protected:
    
};
#endif /* PlayerManager_hpp */