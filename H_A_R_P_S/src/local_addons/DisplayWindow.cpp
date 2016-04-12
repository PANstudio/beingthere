//
//  DisplayWindow.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 15/12/2015.
//
//

#include "DisplayWindow.h"
//--------------------------------------------------------------
void DisplayWindow::setup()
{
    font.load("ofxdatgui_assets/font-verdana.ttf",20);
    title = "Project H.A.R.P.S";

    calibrationScreen.setup();
    calibrationScreen.setupGrid(10, 10, 50, 50);
    
    // Align Center the Text
    w = (ofGetWidth()/2) - (font.getStringBoundingBox(title, 0, 0).width/2);
    h = (ofGetHeight()/2) - (font.getStringBoundingBox(title, 0, 0).height/2);
    timestring = "0000";
    
    setupFlag = false;
    mapImage.clear();
    mapImage.allocate(100, 100, OF_IMAGE_COLOR);
}
//--------------------------------------------------------------
void DisplayWindow::update()
{
    calibrationScreen.update();
}
//--------------------------------------------------------------
void DisplayWindow::setMapImage(ofImage mapImg)
{
    mapImage.clear();
    mapImage.allocate(mapImg.getWidth(), mapImg.getHeight(), OF_IMAGE_COLOR);
    mapImage.setFromPixels(mapImg.getPixels().getData(), mapImg.getWidth(), mapImg.getHeight(), OF_IMAGE_COLOR);
}
//--------------------------------------------------------------
void DisplayWindow::setupSegmentDisplay()
{
    // if the old display exists delete
    if (timerDisplay == nullptr) {
        delete timerDisplay;        
    }
    // Make new object
    timerDisplay = new ofxSegmentDisplay::UnitArray;
    
    ofxSegmentDisplay::Unit::Style& style = timerDisplay->getUnitStyleRef();
    style.segment_width = 10;
    style.padding = ofVec2f(9,16);
    style.skew = 9;
    style.width = SEGMENT_WIDTH;
    style.height = SEGMENT_HEIGHT;
    style.segment_margin = 1;
    timerDisplay->setUnitInterval(64);
    style.updated = true;
    _segmentColor = ofColor::red;
    _backColor = ofColor::black;

    timestring = "0000";
    cout << "Have setup segment display" << endl;
    setupFlag = true;
}
//--------------------------------------------------------------
void DisplayWindow::setTimerColors(ofColor segmentColor, ofColor backColor)
{
    _segmentColor = segmentColor;
    _backColor = backColor;
}
//--------------------------------------------------------------
void DisplayWindow::setNumberOfHealthBars(int num)
{
    for (int i = 0; i < num; i++) {
        playerHealth.push_back(HealthBar());
    }
}
//--------------------------------------------------------------
void DisplayWindow::setCalibration(int gridX, int gridY, int spacingX, int spacingY)
{
    calibrationScreen.setupGrid(gridX, gridY, spacingX, spacingY);
}
//--------------------------------------------------------------
void DisplayWindow::setHealthBars(vector<HealthBar> healthLevels)
{
    playerHealth = healthLevels;
}
//--------------------------------------------------------------
void DisplayWindow::draw()
{
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    if (calibration) {
        calibrationScreen.draw();
    }
    else {
        ofSetColor(255, 255, 252);
        mapImage.draw(0, 0);
        ofSetColor(ofColor::ivory);
        font.drawString(title, w, h);
        for (int i = 0; i < playerHealth.size(); i++) {
            playerHealth[i].draw(ofPoint(10,10+(i*50)));
        }

        int x = (ofGetWidth()/2)-(SEGMENT_WIDTH*timestring.size())/2;
        int y = 10;

        if (setupFlag) {
            ofPushMatrix();
            ofTranslate(x,y);
            if (ofToInt(timestring) < 10) {
                timerDisplay->draw(timestring, _segmentColor, _backColor);
            }
            else {
                timerDisplay->draw(timestring, _segmentColor, _backColor);
            }
            ofPopMatrix();
        }
    }
    ofPopStyle();
}
//--------------------------------------------------------------
void DisplayWindow::doCalibration(bool show)
{
    calibration = show;
}
//--------------------------------------------------------------
void DisplayWindow::close()
{
    if (timerDisplay == nullptr) {
        delete timerDisplay;
    }
}
//--------------------------------------------------------------
void DisplayWindow::drawCalibration()
{

}
//--------------------------------------------------------------
void DisplayWindow::drawPreview(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(0.25,0.25);
    ofPushStyle();
    this->draw();
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    ofPopStyle();
    ofPopMatrix();
}
//--------------------------------------------------------------
void DisplayWindow::getTimeLeft(string time)
{
    timestring = time;
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