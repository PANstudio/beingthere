//
//  CalibrationScreen.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 16/12/2015.
//
//

#include "CalibrationScreen.hpp"
//--------------------------------------------------------------
void CalibrationScreen::setup(int gridSizeX, int gridSizeY, int gridSpacingX, int gridSpacingY)
{
    int count = 0;
        for (int y = 0; y < gridSizeY; y++) {
             for (int x = 0; x < gridSizeX; x++) {
            nodes.push_back(ControlNode(x*gridSpacingX, y*gridSpacingY, count));
            count++;
        }
    }
}
//--------------------------------------------------------------
void CalibrationScreen::draw()
{
    for (auto node : nodes) {
        node.draw();
    }
}
//--------------------------------------------------------------
void CalibrationScreen::mousePos(int x, int y)
{
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].mouseOver(x, y);
    }
}
//--------------------------------------------------------------
void CalibrationScreen::mousePressed(int x, int y,int button)
{
    if (button == OF_MOUSE_BUTTON_RIGHT) {
        for (int i = 0; i < nodes.size(); i++) {
            nodes[i].setOriginNode();

        }
    }
    else {
        for (int i = 0; i < nodes.size(); i++) {
            nodes[i].nodeClicked(x, y, 1);
        }
    }
}