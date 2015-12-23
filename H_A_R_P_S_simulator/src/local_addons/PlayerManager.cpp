//
//  PlayerManager.cpp
//  H_A_R_P_S_simulator
//
//  Created by David Haylock on 17/12/2015.
//
//

#include "PlayerManager.hpp"

//--------------------------------------------------------------
void PlayerManager::setup(string address, int port)
{
    oscSender.setup(address, port);
    cout << "OSC Broadcasting on address " << address << " and port " << port << endl;
}
//--------------------------------------------------------------
void PlayerManager::setNumberOfPlayers(int numberOfPlayers)
{
    _numberOfPlayers = numberOfPlayers;
    players.clear();
    
    for (int player = 0; player < _numberOfPlayers; player++) {
        players.push_back(Player(player,ofColor::ivory));
        pPos[player] = ofVec2f(250, 250);
    }
}
//--------------------------------------------------------------
void PlayerManager::update()
{
    if (ofGetFrameNum() % 5 == 0) {
        for (int player = 0; player < players.size(); player++) {

            // Simulator Only
            if (pPos[player].x > 500 || pPos[player].x < 0 || pPos[player].y > 500 || pPos[player].y < 0) {
                pPos[player].set(250, 250);
            }
            else {
               pPos[player] += ofVec2f(ofRandom(-10,10),ofRandom(-10,10));
            }

            players[player].setPlayerPosition(pPos[player],0);
            ofxOscMessage m;
            m.setAddress("/player"+ofToString(player));
            m.addFloatArg(players[player].getPlayerPreviousCoords().x);
            m.addFloatArg(players[player].getPlayerPreviousCoords().y);
            m.addFloatArg(5);
            oscSender.sendMessage(m, false);
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