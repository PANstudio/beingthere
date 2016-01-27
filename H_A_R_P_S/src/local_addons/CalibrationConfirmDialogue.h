//
//  CalibrationConfirmDialogue.h
//  H_A_R_P_S
//
//  Created by David Haylock on 26/01/2016.
//
//

#ifndef CalibrationConfirmDialogue_h
#define CalibrationConfirmDialogue_h

#include "ofMain.h"

//---------------------------------------------------
class ConfirmButton : public ofRectangle {
public:
    ConfirmButton() {}
    //---------------------------------------------------
    ConfirmButton(int x,int y,int w, int h,string name,ofColor c)
    {
        this->set(x,y,w,h);
        standardColor = c;
        buttonName = name;
        isActive = false;
        isOver = false;
        
    }
    //---------------------------------------------------
    ~ConfirmButton() {}
    //---------------------------------------------------
    void setupButton(int x,int y,int w, int h,string name,ofColor c)
    {
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
        
        ofDrawRectangle(this->getStandardized());
        ofPopStyle();
        ofPushStyle();
        ofSetColor(0, 0, 0);
        ofDrawBitmapString(buttonName, this->getCenter().x-15,this->getCenter().y);
        ofSetColor(ofColor::ivory);
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
            ofNotifyEvent(CLICKED, buttonName,this);
        }
    }
    ofEvent<string> CLICKED;
    bool isActive = false;
    bool isOver = false;
    ofColor standardColor;
    string buttonName;
};

//---------------------------------------------------
class ConfirmReadings {
    
public:
    
    //---------------------------------------------------
    void setup(int width, int height)
    {
        _confirmed = false;
        confirmButton = ConfirmButton(200, 50, 50, 20, "Confirm", ofColor::green);
        cancelButton = ConfirmButton(260, 50, 50, 20, "Cancel", ofColor::red);
    }
    //---------------------------------------------------
    void setNode(int _nodeID)
    {
        nodeID = _nodeID;
    }
    //---------------------------------------------------
    bool confirmed()
    {
        return _confirmed;
    }
    //---------------------------------------------------
    void draw()
    {
        ofPushStyle();
        ofPushStyle();
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(0,0,400,100);
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(0,0,400,100);
        ofPopStyle();
        ofSetColor(255);
        stringstream ss;
        ss << "Node " << nodeID << endl;
        ss << "Are you sure you want to save these readings?" << endl;
        ofDrawBitmapString(ss.str(), 15, 15);
        confirmButton.draw();
        cancelButton.draw();
        ofPopStyle();
    }
    
    int nodeID;
    bool _confirmed;
    ConfirmButton confirmButton;
    ConfirmButton cancelButton;
};

#endif /* CalibrationConfirmDialogue_h */
