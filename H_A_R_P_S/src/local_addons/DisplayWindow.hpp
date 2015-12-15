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

class DisplayWindow : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
private:
    ofTrueTypeFont font;
    int w;
    int h;
    string title;
protected:
    
    
};
