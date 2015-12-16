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
void PlayerManager::setNumberOfPlayers(int numberOfPlayers)
{
    _numberOfPlayers = numberOfPlayers;
    players.clear();
    
    for (int player = 0; player < _numberOfPlayers; player++) {
        players.push_back(Player(player,ofColor::ivory));
    }
}
//--------------------------------------------------------------
void PlayerManager::listen()
{
    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        
        for(int i = 0; i < _numberOfPlayers; i++)
        {
            if (m.getAddress() == "/player"+ofToString(i)) {
                players[i].setPlayerPosition(ofPoint(m.getArgAsFloat(0),m.getArgAsFloat(1)),                m.getArgAsFloat(2));
            }
        }
    }
}
//--------------------------------------------------------------
void PlayerManager::drawPlayerManager()
{
    for (auto player : players) {
        player.draw();
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