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
    _health = 100;
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
    _health = 100;
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
void Player::reduceHealth(int rate)
{
    _health -= rate;
}
//--------------------------------------------------------------
void Player::resetHealth()
{
    _health = 100;
}
//--------------------------------------------------------------
void Player::drawPlayerHealth(ofPoint healthPosition)
{
    ofPushMatrix();
    ofTranslate(healthPosition);
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(0, 0, 400, 20);
    ofPushStyle();
    if (_health < 50 && _health > 25) {
        ofSetColor(ofColor::yellow);
    }
    else if (_health <= 25 && _health > 10) {
        ofSetColor(ofColor::orange);
    }
    else if (_health <= 10 && _health > 1) {
        ofSetColor(ofColor::red);
    }
    else {
        ofSetColor(ofColor::green);
    }
    
    ofFill();
    ofDrawRectangle(0, 0, _health*4, 20);
    ofPopStyle();
    ofPopStyle();
    ofPopMatrix();
}
