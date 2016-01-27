//
//  ControlNode.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 16/12/2015.
//
//

#include "ControlNode.hpp"
//--------------------------------------------------------------
ControlNode::ControlNode(int x,int y,float gridSpacing,int id)
{
    _gridSpacing = gridSpacing;
    _x = x*_gridSpacing;
    _y = y*_gridSpacing;
    
    isActive = false;
    isOrigin = false;
    isOver = false;
    _id = id;
    this->set(x*_gridSpacing, y*_gridSpacing, 14, 14);
    nReading = NodeReadings(this->_id);
}
//--------------------------------------------------------------
ControlNode::~ControlNode() {}
//--------------------------------------------------------------
void ControlNode::setValues(float _var1, float _var2, float _var3, float _var4, float _var5, float _var6)
{
    nReading = NodeReadings(this->_id, _var1, _var2, _var3, _var4, _var5, _var6);
}
//--------------------------------------------------------------
void ControlNode::setValues(NodeReadings rs )
{
    nReading = NodeReadings(this->_id, rs.RXDistX, rs.RXDistY, rs.TX1RXDist, rs.TX1_RSSI1, rs.C1_1, rs.C1_2, rs.C1_3, rs.C1_4, rs.C1_5, rs.C1_6, rs.C2_1, rs.C2_2, rs.C2_3, rs.C2_4, rs.C2_5, rs.C2_6, rs.C3_1, rs.TX3_RSS3, rs.C3_1, rs.C3_2, rs.C3_3, rs.C3_4, rs.C3_5, rs.C3_6);
}
//--------------------------------------------------------------
void ControlNode::updatePosition(int x, int y)
{
    int newPosX = _x + x;
    int newPosY = _y + y;
    this->setX(newPosX);
    this->setY(newPosY);
}
//--------------------------------------------------------------
void ControlNode::draw()
{
    int x = this->getCenter().x;
    int y = this->getCenter().y;
    ofPushStyle();
    if (isActive) {
        ofFill();
        ofSetColor(ofColor::white);
        ofDrawCircle(x, y, 2+(int)(7 + 7 * sin(ofGetElapsedTimef()*5)));
        ofSetColor(ofColor::red);
        ofDrawCircle(x, y, 2+(int)(5 + 5 * sin(ofGetElapsedTimef()*5)));
    }
    else if(isOver) {
        ofFill();
        ofSetColor(ofColor::blueSteel);
        ofDrawCircle(x, y, 7);
        ofSetColor(ofColor::aqua);
        ofDrawCircle(x, y, 5);
    }
    else {
        ofFill();
        ofSetColor(ofColor::white);
        ofDrawCircle(x, y, 7);
        ofSetColor(ofColor::red);
        ofDrawCircle(x, y, 5);
    }
    ofSetColor(ofColor::white);
    ofDrawBitmapString(_id, x, y+15);
    ofPopStyle();
}
//--------------------------------------------------------------
vector<string> ControlNode::getReadings()
{
    vector<string> readings;
    readings.push_back(ofToString(nReading.nodeID));
    readings.push_back(ofToString(nReading.RXDistX));
    readings.push_back(ofToString(nReading.RXDistY));
    readings.push_back(ofToString(nReading.TX1RXDist));
    readings.push_back(ofToString(nReading.TX1_RSSI1));
    readings.push_back(ofToString(nReading.C1_1));
    readings.push_back(ofToString(nReading.C1_2));
    readings.push_back(ofToString(nReading.C1_3));
    readings.push_back(ofToString(nReading.C1_4));
    readings.push_back(ofToString(nReading.C1_5));
    readings.push_back(ofToString(nReading.C1_6));
    readings.push_back(ofToString(nReading.TX2_RSS2));
    readings.push_back(ofToString(nReading.C2_1));
    readings.push_back(ofToString(nReading.C2_2));
    readings.push_back(ofToString(nReading.C2_3));
    readings.push_back(ofToString(nReading.C2_4));
    readings.push_back(ofToString(nReading.C2_5));
    readings.push_back(ofToString(nReading.C2_6));
    readings.push_back(ofToString(nReading.TX3_RSS3));
    readings.push_back(ofToString(nReading.C3_1));
    readings.push_back(ofToString(nReading.C3_2));
    readings.push_back(ofToString(nReading.C3_3));
    readings.push_back(ofToString(nReading.C3_4));
    readings.push_back(ofToString(nReading.C3_5));
    readings.push_back(ofToString(nReading.C3_6));
    return readings;
}
//--------------------------------------------------------------
void ControlNode::mouseOver(int x,int y)
{
    if (this->inside(x, y)) {
        isOver = true;
    }
    else {
        isOver = false;
    }
}
//--------------------------------------------------------------
void ControlNode::nodeClicked(int x,int y,int button)
{
    if(this->inside(x, y)) {
        isActive = !isActive;
    }
}
//--------------------------------------------------------------
void ControlNode::setOriginNode()
{
    isOrigin = !isOrigin;
}