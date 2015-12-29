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
//    healthBar = HealthBar(400, 20, ofColor::green, ofColor::orange, ofColor::red);
}
//--------------------------------------------------------------
Player::Player(int id,ofColor c)
{
    _id = id;
    _c = c;
    healthBar = HealthBar(400, 20,ofColor::green, ofColor::orange, ofColor::red);
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
ofPoint Player::getPlayerCoords()
{
    return _pos;
}
//--------------------------------------------------------------
int Player::getPlayerHeading()
{
    return 370;
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
HealthBar Player::getHealth()
{
    return healthBar;
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
