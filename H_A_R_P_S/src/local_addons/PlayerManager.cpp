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
        MyTimer t;
        t.setup(500, ofToString(player)+" Reducer", false, "");
        reducerTimer.push_back(t);
    }
}
//--------------------------------------------------------------
void PlayerManager::listen()
{
    for (int i = 0 ; i < players.size(); i++) {
        reducerTimer[i].update();
    }
    
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
void PlayerManager::startReducingPlayerHealth(int id)
{
    if (reducerTimer.size() < id) {
        return;
    }
    else {
        reducerTimer[id].start();
    }
}
//--------------------------------------------------------------
void PlayerManager::stopReducingPlayerHealth(int id)
{
    if (reducerTimer.size() < id) {
        return;
    }
    else {
        reducerTimer[id].stop();
    }
}
//--------------------------------------------------------------
void PlayerManager::reducePlayerHealth(int id, int amount)
{
    if (players.size() < id) {
        return;
    }
    else {
        players[id].reduceHealth(amount);
    }
}
//--------------------------------------------------------------
void PlayerManager::drawPlayerHealth(int x, int y,float scale)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(scale, scale);
    for (int i = 0; i < players.size(); i++) {
        stringstream st;
        st << "Player X: " << players[i].getPlayerCoords().x << endl;
        st << "Player Y: " << players[i].getPlayerCoords().y << endl;
        st << "Player Rotation: " << players[i].getPlayerHeading() << endl;
        ofDrawBitmapString(st.str(),0,50+(i*150));
        players[i].drawPlayerHealth(ofPoint(0,0+(i*150)));
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
ofPoint PlayerManager::getPlayerCoords()
{
    ofPoint pos;
    return pos;
}
//--------------------------------------------------------------
vector<HealthBar> PlayerManager::getPlayerHealth()
{
    vector<HealthBar> health;
    for (auto player : players) {
        health.push_back(player.getHealth());
    }
    return health;
}
//--------------------------------------------------------------
vector<ofPoint> PlayerManager::getPlayersCoords()
{
    vector<ofPoint> pos;
    for (int i = 0; i < players.size(); i++) {
        pos.push_back(players[i].getPlayerCoords());
    }
    return pos;
}