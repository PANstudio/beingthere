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
#include "MyTimer.hpp"
#include "ofxPathfinder.h"

class PlayerManager {
public:
    void setup(string address,int port);
    void setNumberOfPlayers(int numberOfPlayers);
    void listen();
    void closeListener();
    void getFinderImage(ofImage img);
    void drawPath();
    void drawPlayerManager();
    void drawPlayerHealth(int x, int y,float scale);
    vector<HealthBar>getPlayerHealth();
    
    string getDebugData();
    
    void startReducingPlayerHealth(int id);
    void reducePlayerHealth(int id,int amount);
    void stopReducingPlayerHealth(int id);
    
    ofPoint getPlayerCoords();
    vector<ofPoint> getPlayersCoords();
    
    ofxPathfinder finder;
    
private:
    ofxOscReceiver oscReceiver;
    int _numberOfPlayers;
    vector <Player> players;
    vector<MyTimer> reducerTimer;
    
protected:
    
};
#endif /* PlayerManager_hpp */