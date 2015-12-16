//
//  DisplayWindow.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 15/12/2015.
//
//

#include "DisplayWindow.hpp"
//--------------------------------------------------------------
void DisplayWindow::setup()
{
    font.load("ofxdatgui_assets/font-verdana.ttf",20);
    title = "Project H.A.R.P.S";

    // Align Center the Text
    w = (ofGetWidth()/2) - (font.getStringBoundingBox(title, 0, 0).width/2);
    h = (ofGetHeight()/2) - (font.getStringBoundingBox(title, 0, 0).height/2);
}
//--------------------------------------------------------------
void DisplayWindow::update()
{
    
}
//--------------------------------------------------------------
void DisplayWindow::draw()
{
    ofBackground(0, 0, 0);
    ofSetColor(ofColor::ivory);
    font.drawString(title, w, h);
    drawCalibration();
    
}
//--------------------------------------------------------------
void DisplayWindow::doCalibration(bool show)
{
    calibration = show;
}
//--------------------------------------------------------------
void DisplayWindow::drawCalibration()
{
    ofPushMatrix();
    ofTranslate(0,0);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofSetColor(ofColor::white);
    ofDrawRectangle(0,0, ((10-1)*50), ((10-1)*50));

    for (int x = 0; x < 10; x++) {
        ofDrawBitmapString(ofToString(x), x*50, 10);
        for (int y = 0; y < 10; y++) {
            ofFill();
            ofSetColor(ofColor::white);
            ofDrawCircle((x*50), (y*50), 7);
            ofSetColor(ofColor::red);
            ofDrawCircle((x*50), (y*50), 5);
            ofSetColor(ofColor::white);
        }
    }
    ofPopMatrix();
}