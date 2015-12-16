//
//  ControlNode.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 16/12/2015.
//
//

#include "ControlNode.hpp"
//--------------------------------------------------------------
ControlNode::ControlNode(int x,int y,int id)
{
    isActive = false;
    isOrigin = false;
    isOver = false;
    _id = id;
    this->set(x, y, 14, 14);
}
//--------------------------------------------------------------
ControlNode::~ControlNode() {}
//--------------------------------------------------------------
void ControlNode::draw()
{
    int x = this->getCenter().x;
    int y = this->getCenter().y;
    ofPushStyle();
    if (isActive) {
        ofFill();
        ofSetColor(ofColor::white);
        ofDrawCircle(x, y, 7);
        ofSetColor(ofColor::red);
        ofDrawCircle(x, y, 5);
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
    isActive = !isActive;
}
//--------------------------------------------------------------
void ControlNode::setOriginNode()
{
    isOrigin = !isOrigin;
}