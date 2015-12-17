//
//  Player.hpp
//  H_A_R_P_S_simulator
//
//  Created by David Haylock on 17/12/2015.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "ofMain.h"
class Player {
public:
    
    // Constructors and Co
    Player();
    Player(int id,ofColor c);
    ~Player();
    
    // Standard Setup
    void setup(int id);
    void update();
    void draw();
    
    // Player positions
    void setPlayerPosition(ofVec2f pos,int heading);
    ofVec2f getPlayerCoords();
    ofVec2f getPlayerPreviousCoords();
    int getPlayerHeading();
    
    // Health System
    void drawPlayerHealth(ofPoint healthPosition);
    void resetHealth();
    void reduceHealth(int rate);
    
private:
    ofVec2f _pos;
    int _heading;
    int _id;
    int _health;
    ofColor _c;
    
protected:
    
};
#endif /* Player_hpp */
