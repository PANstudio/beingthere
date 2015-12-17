//
//  PlayerManager.hpp
//  H_A_R_P_S_simulator
//
//  Created by David Haylock on 17/12/2015.
//
//

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
    void closeBroadcast();
    void update();
    void drawPlayerManager();
    
    string getDebugData();
    
    ofPoint getPlayerCoords();
    vector<ofPoint> getPlayersCoords();
    
private:
    ofxOscSender oscSender;
    int _numberOfPlayers;
    vector <Player> players;
    vector <ofVec2f> pPos;
protected:
    
};
#endif /* PlayerManager_hpp */
