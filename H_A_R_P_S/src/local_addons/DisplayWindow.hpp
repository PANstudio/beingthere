//
//  DisplayWindow.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 15/12/2015.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "CalibrationScreen.hpp"
#include "HealthBar.h"

class DisplayWindow : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void setNumberOfHealthBars(int num);
    void setHealthBars(vector<HealthBar>healthLevels);
    void doCalibration(bool show);
    void drawCalibration();
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);
    
private:
    ofTrueTypeFont font;
    int w;
    int h;
    string title;
    bool calibration;
    vector <HealthBar> playerHealth;
    CalibrationScreen calibrationScreen;
    
protected:
    
    
};
