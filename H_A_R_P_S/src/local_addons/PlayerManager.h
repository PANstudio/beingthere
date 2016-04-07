//--------------------------------------------------------------
//
//  PlayerManager.h
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef PlayerManager_h
#define PlayerManager_h

#include <stdio.h>
#include "Player.h"
#include "ofMain.h"
#include "ofxOsc.h"
#include "MyTimer.h"
#include "ofxPathfinder.h"
#include "ofxCv.h"

class PlayerManager : public ofThread {
public:
    //! Setup the OSC Port
    void setup(string address,int port);
    
    //! Set the Number of Players
    void setNumberOfPlayers(int numberOfPlayers);

    //! Listen for messages
    void listen();
    
    //! Shut down the listener
    void closeListener();
    
    //! Grab image for the path finder
    void getFinderImage(cv::Mat img);
    
    //! Draw the Pathfinder
    void drawPath();
    
    //! Draw all the data
    void drawPlayerManager();
    
    //! Draw Health
    void drawPlayerHealth(int x, int y,float scale);
    
    //! Get the player health
    vector<HealthBar>getPlayerHealth();
    
    //! Get the Debug Data
    string getDebugData();
    
    //! Start Reducing the Players Health
    void startReducingPlayerHealth(int id);
    
    //! Action to reduce the health
    void reducePlayerHealth(int id,int amount);
    
    //! Stop Reducing the Players Health
    void stopReducingPlayerHealth(int id);
    
    //! Get the Player current Postion
    ofPoint getPlayerCoords();
    
    //! Get the Players Current Positions
    vector<ofPoint> getPlayersCoords();
    
    // Might Go
    ofxPathfinder finder;
    
private:
    ofxOscReceiver oscReceiver;
    int _numberOfPlayers;
    vector <Player> players;
    vector<MyTimer> reducerTimer;
    
protected:
    
};
#endif /* PlayerManager_h */