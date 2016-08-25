//--------------------------------------------------------------
//
//  PlayerManager.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------
#include "PlayerManager.h"
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
        t.setup(500, ofToString(player)+" Reducer", false);
        reducerTimer.push_back(t);
    }
}
//--------------------------------------------------------------
void PlayerManager::getFinderImage(cv::Mat img)
{
    finder.setup(img);
}
//--------------------------------------------------------------
void PlayerManager::listen()
{
    for (int i = 0 ; i < players.size(); i++) {
        reducerTimer[i].update();
    }
    
    
//    players[0].setPlayerPosition(ofPoint(ofGetMouseX(),ofGetMouseY()),0);
    
    
//    int mx = ofMap(ofGetMouseX(), 0, 500, 0, 100);
//    int my = ofMap(ofGetMouseY(), 0, 500, 0, 100);
//    finder.find(mx, my, 10, 10);
    
    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
//        cout << &m << endl;
        if (m.getAddress() == "/player/0" ) {
            
            cout << m.getArgAsFloat(0) << endl;
            cout << m.getArgAsFloat(1) << endl;
            cout << m.getArgAsFloat(2) << endl;
            
            
            mockPos = ofPoint(ofMap(m.getArgAsFloat(1), 0.0000, 10.0000, 0, 500),ofMap(m.getArgAsFloat(2), 0.0000, 10.0000, 0, 500));
            players[0].setPlayerPosition(mockPos,m.getArgAsInt(0));//ofPoint(ofGetMouseX(),ofGetMouseY()), m.getArgAsInt(0));

        }
//        for(int i = 0; i < _numberOfPlayers; i++) {
//            if (m.getAddress() == "/player"+ofToString(i)) {
//                if (_scale) {
//                    players[i].setPlayerPosition(ofPoint(ofMap(m.getArgAsFloat(0), 0.0000, 1.0000, 0, _scaleX),ofMap(m.getArgAsFloat(1), 0.0000, 1.0000, 0, _scaleY)), m.getArgAsFloat(2));
//                }
//                else {
//                    players[i].setPlayerPosition(ofPoint(m.getArgAsFloat(0),m.getArgAsFloat(1)), //Position
//                                                         m.getArgAsFloat(2)); // Orientation
//                }
//            }
//        }
    }
}
//--------------------------------------------------------------
void PlayerManager::setScaleValues(bool scale)
{
    _scale = scale;
}
//--------------------------------------------------------------
void PlayerManager::scalePositionX(int maxRangeX)
{
    _scaleX = maxRangeX;
}
//--------------------------------------------------------------
void PlayerManager::scalePositionY(int maxRangeY)
{
    _scaleY = maxRangeY;
}
//--------------------------------------------------------------
void PlayerManager::drawPlayerManager()
{
    for (auto player : players) {
        player.draw();
    }
    ofPushMatrix();
    ofScale(5, 5);
    ofPushStyle();
    ofSetLineWidth(5);
    ofSetColor(255, 255, 255);
    finder.path.draw();
    ofPopStyle();
    ofPopMatrix();
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
void PlayerManager::resetHealth()
{
    for (int i = 0; i < players.size(); i++) {
        players[i].resetHealth();
    }
}
//--------------------------------------------------------------
void PlayerManager::drawDebug()
{
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofDrawCircle(mockPos, 25);
    ofPopStyle();
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
    
    ofDrawBitmapStringHighlight(ofToString(mockPos), 500,300);
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