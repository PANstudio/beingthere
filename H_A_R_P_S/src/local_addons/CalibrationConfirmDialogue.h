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
#include "BaseButton.h"

//---------------------------------------------------
class ConfirmReadings {
    
public:
    
    //---------------------------------------------------
    void setup(int x,int y,int width, int height)
    {
        _x = x;
        _y = y;
        _confirmed = false;
        confirmButton = BaseButton(x, y, 50, 20, "Confirm", ofColor::green);
        cancelButton = BaseButton(x+50, y, 50, 20, "Cancel", ofColor::red);
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
        ofPushMatrix();
        ofTranslate(_x, _y);
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
        confirmButton.drawBase();
        cancelButton.drawBase();
        ofPopStyle();
        ofPopMatrix();
    }
    
    int nodeID;
    bool _confirmed;
    BaseButton confirmButton;
    BaseButton cancelButton;
    int _x;
    int _y;
};

#endif /* CalibrationConfirmDialogue_h */
