//
//  BaseButton.h
//  H_A_R_P_S
//
//  Created by David Haylock on 27/01/2016.
//
//

#ifndef BaseButton_h
#define BaseButton_h

#include "ofMain.h"

class BaseButton: public ofRectangle {
public:
    
    ofColor _baseColor;
    ofEvent<string> pressed;
    string _buttonName;
    bool isActive = false;
    bool isOver = false;

    //---------------------------------------------------
    BaseButton() {}
    //---------------------------------------------------
    ~BaseButton() {}
    //---------------------------------------------------
    BaseButton(int x,int y, int width,int height,string buttonName,ofColor baseColor)
    {
        this->set(x, y, width, height);
        _baseColor = baseColor;
        _buttonName = buttonName;
    }
    //---------------------------------------------------
    void setup(int x,int y, int width,int height,string buttonName,ofColor baseColor)
    {
        this->set(x, y, width, height);
        _baseColor = baseColor;
        _buttonName = buttonName;
    }
    //---------------------------------------------------
    void drawBase()
    {
        ofPushStyle();
        if (isOver) {
            ofSetColor(ofColor::yellowGreen);
        }
        else if(isActive) {
            ofSetColor(ofColor::aqua);
        }
        else {
            ofSetColor(_baseColor);
        }
        ofDrawRectangle(this->getStandardized());
        ofPopStyle();
        ofPushStyle();
        ofSetColor(0, 0, 0);
        ofDrawBitmapString(_buttonName, this->getCenter());
        ofSetColor(ofColor::white);
        ofNoFill();
        ofDrawRectangle(this->getStandardized());
        ofPopStyle();
    }
    //---------------------------------------------------
    void mouseOver(int x,int y)
    {
        if (inside(x,y)) {
            isOver = true;
        }
        else {
            isOver = false;
        }
    }
    //---------------------------------------------------
    void buttonPressed(int x,int y,int button)
    {
        if (inside(x,y)) {
            isActive = !isActive;
            ofNotifyEvent(pressed, _buttonName,this);
        }
    }
    
};

#endif /* BaseButton_h */
