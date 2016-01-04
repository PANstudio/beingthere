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
#include "ofxTween.h"

class HealthBar {
public:
    //----------------------------------------
    HealthBar() {
        
    }
    //----------------------------------------
    HealthBar(int width,int height,ofColor goodColor,ofColor dangerColor,ofColor deadlyColor)
    {
        _health = 100;
        _good = goodColor;
        _danger = dangerColor;
        _deadly = deadlyColor;
        _width = width;
        _height = height;
        _died = false;
    }
    //----------------------------------------
    ~HealthBar() {
        
    }
    //----------------------------------------
    void setup(int width,int height,ofColor goodColor,ofColor dangerColor,ofColor deadlyColor)
    {
        _health = 100;
        _good = goodColor;
        _danger = dangerColor;
        _deadly = deadlyColor;
        _width = width;
        _height = height;
        _died = false;
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
    int getHealthBarWidth()
    {
        return _width;
    }
    //----------------------------------------
    int getHealthBarHeight()
    {
        return _height;
    }
    //----------------------------------------
    void reduceHealth(int amount)
    {
        if (_health <= 0 && !_died) {
            _died = true;
        }
        else {
            int tempHealth = (_health - amount);
            tween.setParameters(1,expo,ofxTween::easeOut,_health,tempHealth,500,1);
            _health -= amount;
        }
    }
    //----------------------------------------
    void draw(ofPoint healthPosition) {
        CLAMP(_health, 0, 100);
        if (tween.isRunning()) {
            _health = tween.update();
        }

        ofPushMatrix();
        ofTranslate(healthPosition);
        ofPushStyle();
        ofSetColor(ofColor::white);
        ofNoFill();
        ofDrawRectangle(0, 0, _width, _height);
        ofPushStyle();

        
        if (_died) {
            ofSetColor((int)(175 + 80 * sin(ofGetElapsedTimef()*2)),0,0);
            ofFill();
            ofDrawRectangle(0, 0, _width, _height);
        }
        else {
            if (_health <= 25 && _health > 10) {
                ofSetColor(_danger);
            }
            else if (_health <= 10 && _health > 1) {
                ofSetColor(_deadly);
            }
            else {
                ofSetColor(_good);
            }
            ofFill();
            ofDrawRectangle(0, 0, ofMap(_health,100,0,_width,0), _height);
        }
        
        ofPopStyle();
        ofPopStyle();
        ofPopMatrix();
    }
private:
    int _health;
    int _width;
    int _height;
    
    ofColor _good;
    ofColor _danger;
    ofColor _deadly;
    
    bool _died;
    ofxTween tween;
    ofxEasingExpo expo;

protected:
    
};

#endif /* HealthBar_h */
