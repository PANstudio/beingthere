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

class Player {
public:
    
    Player();
    ~Player();
    void setup(int id);
    void setPlayerPosition(ofPoint pos,int heading);
    
    void draw();
    ofPoint getPlayerCoords();
    int getPlayerHeading();
    
private:
    ofPoint _pos;
    int _heading;
    int _id;
protected:
    
};

#endif /* Player_hpp */