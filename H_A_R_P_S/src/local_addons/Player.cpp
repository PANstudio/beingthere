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
Player::Player(int id,ofColor c)
{
    _id = id;
    _c = c;
    healthBar.setup();
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
    healthBar.setup();
}
//--------------------------------------------------------------
ofPoint Player::getPlayerCoords()
{
    return _pos;
}
//--------------------------------------------------------------
int Player::getPlayerHeading()
{
    return _heading;
}
//--------------------------------------------------------------
void Player::draw()
{
    ofPushStyle();
    ofSetColor(_c);
    ofPushMatrix();
    ofTranslate(_pos);
    ofPushMatrix();
    ofRotateZ(_heading);
    ofDrawCircle(0,0,4);
    ofSetColor(ofColor::black);
    ofDrawBitmapString(ofToString(_id), 0, 0);
    ofPopMatrix();
    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------
int Player::getHealth()
{
    return healthBar.getHealth();
}
//--------------------------------------------------------------
void Player::reduceHealth(int rate)
{
    healthBar.reduceHealth(rate);
}
//--------------------------------------------------------------
void Player::resetHealth()
{
    healthBar.reset();
}
//--------------------------------------------------------------
void Player::drawPlayerHealth(ofPoint healthPosition)
{
    healthBar.draw(healthPosition);
}
