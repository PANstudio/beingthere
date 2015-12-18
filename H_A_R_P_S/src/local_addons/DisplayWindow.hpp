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

class DisplayWindow : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void setHealthBars(vector<int>healthLevels);
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
    
    CalibrationScreen calibrationScreen;
    
protected:
    
    
};
