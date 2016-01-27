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
    nodes.clear();
    int count = 0;
        for (int y = 0; y < gridSizeY; y++) {
             for (int x = 0; x < gridSizeX; x++) {
            nodes.push_back(ControlNode(x*gridSpacingX, y*gridSpacingY, count));
            count++;
        }
    }
    vector<string> header;
    header.push_back("Node ID");
    for (int i = 1; i <= 6; i++) {
        string s = "Var " + ofToString(i);
        header.push_back(s);
    }
    
    confirmation.setup(200,200);
    ofAddListener(confirmation.confirmButton.CLICKED, this, &CalibrationScreen::buttonClicked);
    ofAddListener(confirmation.cancelButton.CLICKED, this, &CalibrationScreen::buttonClicked);
    spreadsheet.setHeaders(header);
    spreadsheet.setup(500, 0, 25, header.size());
}
//--------------------------------------------------------------
void CalibrationScreen::setNodeReadings(int node)
{
    if (!nodes.empty()) {
        nodes[node].setValues(ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100));
        spreadsheet.addEntry(nodes[node].getReadings());
    }
}
//--------------------------------------------------------------
void CalibrationScreen::draw()
{
    for (auto node : nodes) {
        node.draw();
    }
    
    ofSetColor(255);
    spreadsheet.draw();
    
    confirmation.draw();
}
//--------------------------------------------------------------
void CalibrationScreen::saveCalibrationData()
{
    vector<vector<string>> data;
    data.push_back(spreadsheet.getHeaders());
    
    int entryNumbers = spreadsheet.getEntries().size();
    for (int i = 0; i < entryNumbers; i++) {
        data.push_back(spreadsheet.getEntries()[i]);
    }
    
    readingsFile.setData(data);
    readingsFile.saveFile(ofToDataPath("readings.csv"));
}
//--------------------------------------------------------------
void CalibrationScreen::mousePos(int x, int y)
{
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].mouseOver(x, y);
    }
    confirmation.confirmButton.mouseOver(x, y);
    confirmation.cancelButton.mouseOver(x, y);
}
//--------------------------------------------------------------
void CalibrationScreen::buttonClicked(string &str)
{
    cout << str << endl;
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
        
        confirmation.confirmButton.buttonPressed(x, y, button);
        confirmation.cancelButton.buttonPressed(x, y, button);
        
        
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].isActive) {
                nodes[i].isActive = false;
            }
            nodes[i].nodeClicked(x, y, 1);
            if (nodes[i].isActive) {
                setNodeReadings(i);
            }
        }
    }
}