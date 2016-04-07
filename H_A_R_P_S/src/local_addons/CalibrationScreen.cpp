//
//  CalibrationScreen.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 16/12/2015.
//
//

#include "CalibrationScreen.h"
//--------------------------------------------------------------
void CalibrationScreen::setup()
{
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
    showConfirmation = false;
}
//--------------------------------------------------------------
void CalibrationScreen::setupGrid(int gridSizeX, int gridSizeY, int gridSpacingX, int gridSpacingY)
{
    calibrationListener.setup(12345);
    nodes.clear();
    int count = 0;
        for (int y = 0; y < gridSizeY; y++) {
             for (int x = 0; x < gridSizeX; x++) {
            nodes.push_back(ControlNode(x, y,gridSpacingX,gridSpacingY, count));
            count++;
        }
    }
}
//--------------------------------------------------------------
void CalibrationScreen::setNodeReadings(int node)
{

}
//--------------------------------------------------------------
void CalibrationScreen::update()
{
    while (calibrationListener.hasWaitingMessages()) {
        ofxOscMessage m;
        calibrationListener.getNextMessage(m);

        if(m.getAddress() == "/calibration/TX1RXDist") {
            currentReadings.TX1RXDist = m.getArgAsFloat(0);
            cout << m.getArgAsFloat(0) << endl;
        }
        else if(m.getAddress() == "/calibration/TX1_RSSI1") {
            currentReadings.TX1_RSSI1 = m.getArgAsFloat(0);
            currentReadings.C1_1 = m.getArgAsFloat(1);
            currentReadings.C1_2 = m.getArgAsFloat(2);
            currentReadings.C1_3 = m.getArgAsFloat(3);
            currentReadings.C1_4 = m.getArgAsFloat(4);
            currentReadings.C1_5 = m.getArgAsFloat(5);
            currentReadings.C1_6 = m.getArgAsFloat(6);
        }
        else if(m.getAddress() == "/calibration/TX2_RSSI2") {
            currentReadings.TX2_RSS2 = m.getArgAsFloat(0);
            currentReadings.C2_1 = m.getArgAsFloat(1);
            currentReadings.C2_2 = m.getArgAsFloat(2);
            currentReadings.C2_3 = m.getArgAsFloat(3);
            currentReadings.C2_4 = m.getArgAsFloat(4);
            currentReadings.C2_5 = m.getArgAsFloat(5);
            currentReadings.C2_6 = m.getArgAsFloat(6);
        }
        else if(m.getAddress() == "/calibration/TX3_RSSI3") {
            currentReadings.TX3_RSS3 = m.getArgAsFloat(0);
            currentReadings.C3_1 = m.getArgAsFloat(1);
            currentReadings.C3_2 = m.getArgAsFloat(2);
            currentReadings.C3_3 = m.getArgAsFloat(3);
            currentReadings.C3_4 = m.getArgAsFloat(4);
            currentReadings.C3_5 = m.getArgAsFloat(5);
            currentReadings.C3_6 = m.getArgAsFloat(6);
        }
    }
}
//--------------------------------------------------------------
void CalibrationScreen::draw()
{
    for (auto node : nodes) {
        node.draw();
    }

    if (showConfirmation) {
        confirmation.draw();
    }
}
//--------------------------------------------------------------
void CalibrationScreen::drawSpreadsheet()
{
    ofSetColor(255);
    spreadsheet.draw();
}
//--------------------------------------------------------------
void CalibrationScreen::drawCurrentReadings(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    currentReadings.draw();
    ofPopMatrix();
}
//--------------------------------------------------------------
void CalibrationScreen::setGridSpacing(int spacingX, int spacingY)
{
    _gridSpacingX = spacingX;
    _gridSpacingY = spacingY;
}
//--------------------------------------------------------------
void CalibrationScreen::alterNodeSpacing(int x, int y)
{
    int count = 0;
    for (int y = 0; y < _gridSizeY; y++) {
        for (int x = 0; x < _gridSizeX; x++) {
            nodes[count].updateRXDist(x*_gridSpacingX, y*_gridSpacingY);
            count++;
        }
    }
}
//--------------------------------------------------------------
void CalibrationScreen::moveNodes(int x, int y)
{
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
    if (str == "Confirm") {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].isActive) {
                
                if (!nodes.empty()) {
                    currentReadings.nodeID = nodes[i]._id;
                    currentReadings.RXDistX = nodes[i]._x/100;
                    currentReadings.RXDistY = nodes[i]._y/100;
                    nodes[i].setValues(currentReadings);
                    spreadsheet.addEntry(nodes[i].getReadings());
                }
                cout << "Node " << nodes[i]._id << endl;
            }
        }
       
        showConfirmation = false;
    }
    else if (str == "Cancel") {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].isActive) {
                nodes[i].isActive = false;
            }
        }
        showConfirmation = false;
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
        
        confirmation.confirmButton.buttonPressed(x, y, button);
        confirmation.cancelButton.buttonPressed(x, y, button);
        
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].isActive) {
                nodes[i].isActive = false;
            }
            nodes[i].nodeClicked(x, y, 1);
            if (nodes[i].isActive) {
                showConfirmation = true;
                
                confirmation.setNode(nodes[i]._id);
                currentReadings.nodeID = nodes[i]._id;
                currentReadings.RXDistX = nodes[i]._x/100;
                currentReadings.RXDistY = nodes[i]._y/100;
            }
        }
    }
}