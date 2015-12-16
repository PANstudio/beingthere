//--------------------------------------------------------------
//
//  Player.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#include "Player.hpp"

//--------------------------------------------------------------
Player::Player()
{
    
}
//--------------------------------------------------------------
Player::~Player()
{
    
}
//--------------------------------------------------------------
void Player::setup(int id)
{
    _id = id;
}
//--------------------------------------------------------------
void Player::setPlayerPosition(ofPoint pos,int heading)
{
    _pos = pos;
    _heading = heading;
}
//--------------------------------------------------------------
void Player::draw()
{
    ofPushStyle();
    ofSetColor(ofColor::seaGreen);
    ofPushMatrix();
    ofTranslate(_pos);
    ofPushMatrix();
    ofRotateZ(_heading);
    
    ofDrawCircle(0,0, 4);
    ofDrawLine(-_pos.x, -_pos.y-10, -_pos.x, -_pos.y+10);
    ofPopMatrix();
    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------
ofPoint Player::getPlayerCoords()
{
    
}
//--------------------------------------------------------------
int Player::getPlayerHeading()
{
    
}