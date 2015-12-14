//--------------------------------------------------------------
//
//  Tile.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------
#include "Tile.hpp"

//--------------------------------------------------------------
Tile::Tile()
{
    // Constructor
}
//--------------------------------------------------------------
Tile::~Tile()
{
    // Deconstructor
}
//--------------------------------------------------------------
Tile::Tile(bool _walkable,int _toxicity,ofVec2f _worldPosition, int _gridXPosition,int _gridYPosition,int _size)
{
    walkable = _walkable;
    
    worldPosition = _worldPosition;

    gridX = _gridXPosition;
    gridY = _gridYPosition;
    size = _size;
    toxicity = _toxicity;
    
    this->set(_worldPosition.x,_worldPosition.y, size, size);
}
//--------------------------------------------------------------
int Tile::getfCost()
{
    fCost = (gCost + hCost);
    return fCost;
}
//--------------------------------------------------------------
void Tile::printData()
{
    cout << "---------------------" << endl;
    cout << "Tile" << endl;
    cout << gridX << " " << gridY << endl;
    string isWalkable = (walkable) ? "Is Walkable": "Not Walkable";
    cout << isWalkable << endl;
}
//--------------------------------------------------------------
void Tile::setHighlighted(bool isHighlighted)
{
    highlighted = isHighlighted;
}
//--------------------------------------------------------------
void Tile::showGridDetails(bool _show)
{
    showGrid = _show;
}
//--------------------------------------------------------------
void Tile::draw()
{
    if (walkable) {
        ofSetColor(ofColor::green);
    }
    else {
        ofSetColor(ofColor::red);
    }
    if (highlighted) {
        ofSetColor(ofColor::aqua);
    }
    if(haveChecked) {
        ofSetColor(ofColor::blueSteel);
    }
    if(isPath) {
        ofSetColor(ofColor::yellow);
    }
    
    ofDrawRectangle(this->getX(),this->getY(),this->getWidth(),this->getHeight());
    
    
    if(showGrid) {
        ofPushStyle();
        ofSetColor(ofColor::black);
        ofDrawBitmapString(ofToString(gCost),this->getTopLeft().x+5,this->getTopLeft().y+10);
        ofDrawBitmapString(ofToString(hCost),this->getTopRight().x-20,this->getTopRight().y+10);
        ofDrawBitmapString(ofToString(fCost),this->getCenter().x-5,this->getCenter().y+5);
        ofNoFill();
        ofDrawRectangle(this->getX(),this->getY(),this->getWidth(),this->getHeight());
        ofPopStyle();
    }
    
}