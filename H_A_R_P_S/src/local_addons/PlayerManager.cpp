//--------------------------------------------------------------
//
//  PlayerManager.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------
#include "PlayerManager.hpp"
//--------------------------------------------------------------
void PlayerManager::setup(string address, int port)
{
    oscReceiver.setup(port);
}
//--------------------------------------------------------------
void PlayerManager::listen()
{
    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        
        for(int i = 0; i < 3; i++)
        {
            if (m.getAddress() == "/player"+ofToString(i)) {
                
            }
        }
    }
}
//--------------------------------------------------------------
ofPoint PlayerManager::getPlayerCoords()
{
    ofPoint pos;
    return pos;
}
//--------------------------------------------------------------
vector<ofPoint> PlayerManager::getPlayersCoords()
{
    vector<ofPoint> pos;
    return pos;
}