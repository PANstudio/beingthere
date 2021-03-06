//
//  DisplayWindow.h
//  H_A_R_P_S
//
//  Created by David Haylock on 15/12/2015.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "HealthBar.h"
#include "MyTimer.h"
#include "ofxSegmentDisplay.h"
#include "CalibrationScreen.h"

#define SEGMENT_WIDTH 60
#define SEGMENT_HEIGHT 128

class DisplayWindow : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void setupSegmentDisplay();
    void setNumberOfHealthBars(int num);
    void setHealthBars(vector<HealthBar>healthLevels);
    void setTimerColors(ofColor segmentColor,ofColor backColor);
    void setMapImage(ofImage mapImg);
    void doCalibration(bool show);
    void drawCalibration();

    void drawPreview(int x,int y);
    
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);
    
    void getTimeLeft(string time);
    
    void setCalibration(int gridX,int gridY,int spacingX,int spacingY);
    
    void modeSelector(int &mode);
    
    void close();
    CalibrationScreen calibrationScreen;
    ofEvent<int> currentMode;
    
private:
    ofTrueTypeFont font;
    int w;
    int h;
    ofImage mapImage;
    string title;
    bool calibration;
    vector <HealthBar> playerHealth;

    string timestring;
    ofxSegmentDisplay::UnitArray *timerDisplay;
    
    ofColor _segmentColor;
    ofColor _backColor;
    
    bool setupFlag;
protected:
    
    
};
