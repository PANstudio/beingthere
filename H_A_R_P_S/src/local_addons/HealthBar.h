//
//  HealthBar.h
//  H_A_R_P_S
//
//  Created by David Haylock on 18/12/2015.
//
//

#ifndef HealthBar_h
#define HealthBar_h

#include "ofMain.h"

class HealthBar {
public:
    //----------------------------------------
    HealthBar() {
        _health = 100;
    }
    //----------------------------------------
    ~HealthBar() {
        
    }
    //----------------------------------------
    void setup() {
        _health = 100;
    }
    //----------------------------------------
    void reset()
    {
        _health = 100;
    }
    //----------------------------------------
    bool noHealth()
    {
        return _died;
    }
    //----------------------------------------
    int getHealth()
    {
        return _health;
    }
    //----------------------------------------
    void reduceHealth(int amount)
    {
        _health -= amount;
    }
    //----------------------------------------
    void draw(ofPoint healthPosition) {
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
private:
    int _health;
    bool _died;
    
protected:
    
};

#endif /* HealthBar_h */
