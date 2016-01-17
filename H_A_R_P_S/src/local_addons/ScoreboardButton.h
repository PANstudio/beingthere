//
//  ScoreboardButton.h
//  H_A_R_P_S
//
//  Created by David Haylock on 16/01/2016.
//
//

#ifndef ScoreboardButton_h
#define ScoreboardButton_h

#include "ofMain.h"
//---------------------------------------------------
class ScoreboardButton : public ofRectangle {
public:
    ScoreboardButton() {}
    //---------------------------------------------------
    ScoreboardButton(int x,int y,int w, int h,int orderBy,string name,ofColor c)
    {
        _orderBy = orderBy;
        this->set(x,y,w,h);
        standardColor = c;
        buttonName = name;
        isActive = false;
        isOver = false;
        
    }
    //---------------------------------------------------
    ~ScoreboardButton() {}
    //---------------------------------------------------
    void setupButton(int x,int y,int w, int h,int orderBy,string name,ofColor c)
    {
        _orderBy = orderBy;
        this->set(x,y,w,h);
        standardColor = c;
        buttonName = name;
        isActive = false;
        isOver = false;
    }
    //---------------------------------------------------
    void draw()
    {
        ofPushStyle();
        if (isOver) {
            ofSetColor(ofColor::orange);
        }
        else if(isActive) {
            ofSetColor(ofColor::seaGreen);
        }
        else {
            ofSetColor(standardColor);
        }
        
//        ofDrawRectangle(this->getStandardized());
        ofDrawRectRounded(this->getStandardized(), 8);
        ofPopStyle();
        ofSetColor(0, 0, 0);
        ofDrawBitmapString(buttonName, this->getCenter());
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
        }
    }
    int _orderBy;
    bool isActive = false;
    bool isOver = false;
    ofColor standardColor;
    string buttonName;
};
#endif /* ScoreboardButton_h */
