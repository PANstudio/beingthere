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
#include "Player.hpp"
#include "ofMain.h"
#include "ofxOsc.h"

class PlayerManager {
public:
    void setup(string address,int port);
    void setNumberOfPlayers(int numberOfPlayers);
    void listen();
    void closeListener();
    void drawPlayerManager();
    vector<int>getPlayerHealth();
    
    string getDebugData();
    
    ofPoint getPlayerCoords();
    vector<ofPoint> getPlayersCoords();
    
private:
    ofxOscReceiver oscReceiver;
    int _numberOfPlayers;
    vector <Player> players;
protected:
    
};
#endif /* PlayerManager_hpp */