//
//  CalibrationScreen.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 16/12/2015.
//
//

#ifndef CalibrationScreen_hpp
#define CalibrationScreen_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ControlNode.hpp"

class CalibrationScreen {
public:
    void setup(int gridSizeX,int gridSizeY,int gridSpacingX,int gridSpacingY);
    void draw();
    void mousePos(int x,int y);
    void mousePressed(int x,int y,int button);
private:
    int _gridSizeX;
    int _gridSizeY;
    int _gridSpacingX;
    int _gridSpacingY;
    
    vector<ControlNode> nodes;
};

#endif /* CalibrationScreen_hpp */