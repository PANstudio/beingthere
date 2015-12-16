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
    
    calibrationScreen.setup(10, 10, 50, 50);
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
    calibrationScreen.draw();
}
//--------------------------------------------------------------
void DisplayWindow::doCalibration(bool show)
{
    calibration = show;
}
//--------------------------------------------------------------
void DisplayWindow::drawCalibration()
{

}
//--------------------------------------------------------------
void DisplayWindow::mouseMoved(int x, int y )
{
    calibrationScreen.mousePos(x, y);
}
//--------------------------------------------------------------
void DisplayWindow::mousePressed(int x, int y, int button)
{
    calibrationScreen.mousePressed(x, y,button);
}