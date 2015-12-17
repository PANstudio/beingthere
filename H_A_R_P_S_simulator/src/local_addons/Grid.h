//
//  Grid.h
//  H_A_R_P_S_simulator
//
//  Created by David Haylock on 17/12/2015.
//
//

#ifndef Grid_h
#define Grid_h

#include "ofMain.h"

class Grid {
public:
    //--------------------------------------------------------------
    void setup(int gridSizeX,int gridSizeY,int gridOffsetX,int gridOffsetY,int spacingX,int spacingY) {
        _gridSizeX = gridSizeX;
        _gridSizeY = gridSizeY;
        _gridOffsetX = gridOffsetX;
        _gridOffsetY = gridOffsetY;
        _spacingX = spacingX;
        _spacingY = spacingY;
    }
    //--------------------------------------------------------------
    void draw() {
        for (int y = 0; y < _gridSizeY; y++) {
            for (int x = 0; x < _gridSizeX; x++) {
                ofSetColor(ofColor::ivory);
                ofDrawLine(0+(x*_spacingX),_gridOffsetY,0+(x*_spacingX),(_gridSizeY*_spacingY)-_gridOffsetY);
                ofDrawLine(_gridOffsetX,0+(y*_spacingY),(_gridSizeX*_spacingX)-_gridOffsetX,0+(y*_spacingY));
            }
        }
    }
    
private:
    int _gridSizeX;
    int _gridSizeY;
    int _gridOffsetX;
    int _gridOffsetY;
    int _spacingX;
    int _spacingY;
};

#endif /* Grid_h */
