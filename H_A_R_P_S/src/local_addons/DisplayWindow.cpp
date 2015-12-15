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
    title = "H.A.R.P.S";

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
}