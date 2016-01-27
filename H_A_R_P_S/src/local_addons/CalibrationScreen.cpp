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
            nodes.push_back(ControlNode(x, y,gridSpacingX, count));
            count++;
        }
    }
    vector<string> header;
    header.push_back("Node ID");
    
    // Receiver Posistion
    header.push_back("RXDistX");
    header.push_back("RXDistY");
    header.push_back("TX1-RXDist");
    
    // Transmitter 1
    header.push_back("TX1RSSI1");
    header.push_back("C1-1");
    header.push_back("C1-2");
    header.push_back("C1-3");
    header.push_back("C1-4");
    header.push_back("C1-5");
    header.push_back("C1-6");
    
    // Transmitter 2
    header.push_back("TX2RSS2");
    header.push_back("C2-1");
    header.push_back("C2-2");
    header.push_back("C2-3");
    header.push_back("C2-4");
    header.push_back("C2-5");
    header.push_back("C2-6");
    
    // Transmitter 3
    header.push_back("TX3RSS3");
    header.push_back("C3-1");
    header.push_back("C3-2");
    header.push_back("C3-3");
    header.push_back("C3-4");
    header.push_back("C3-5");
    header.push_back("C3-6");
    
    confirmation.setup(0,500,200,200);
    ofAddListener(confirmation.confirmButton.pressed, this, &CalibrationScreen::buttonClicked);
    ofAddListener(confirmation.cancelButton.pressed, this, &CalibrationScreen::buttonClicked);
    spreadsheet.setHeaders(header);
    spreadsheet.setup(10, 0, 25, header.size());
}
//--------------------------------------------------------------
void CalibrationScreen::setNodeReadings(int node)
{
    if (!nodes.empty()) {
        NodeReadings r = NodeReadings(nodes[node]._id,nodes[node]._x/100,nodes[node]._y/100, ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100), ofRandom(100));
        nodes[node].setValues(r);
        spreadsheet.addEntry(nodes[node].getReadings());
    }
}
//--------------------------------------------------------------
void CalibrationScreen::draw()
{
    for (auto node : nodes) {
        node.draw();
    }
    
    
    drawSpreadsheet();
    confirmation.draw();
}
//--------------------------------------------------------------
void CalibrationScreen::drawSpreadsheet()
{
    ofSetColor(255);
    spreadsheet.draw();
}
//--------------------------------------------------------------
void CalibrationScreen::moveNodes(int x, int y)
{
    cout << x << " " << y << endl;
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].updatePosition(x, y);
    }
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