//--------------------------------------------------------------
//
//  Player.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "ofMain.h"
#include "MyTimer.hpp"
#include "HealthBar.h"

class Player {
public:
    
    // Constructors and Co
    Player(); 
    Player(int id,ofColor c);
    ~Player();
    
    // Standard Setup
    void setup(int id);
    void draw();

    // Player positions
    void setPlayerPosition(ofPoint pos,int heading);
    ofPoint getPlayerCoords();
    int getPlayerHeading();
    HealthBar getHealth();

    // Health System
    void drawPlayerHealth(ofPoint healthPosition);
    void resetHealth();
    void reduceHealth(int rate);
    
private:
    ofPoint _pos;
    int _heading;
    int _id;
    ofColor _c;
    HealthBar healthBar;
    
protected:
    
};

#endif /* Player_hpp */