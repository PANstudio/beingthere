//
//  MapViewer.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 13/04/2016.
//
//

#include "MapViewer.h"
bool printOnce = false;
//--------------------------------------------------------------
void MapViewer::setup()
{
    int screenWidth = ofGetWidth();
    int mapHeight = 205;
    int screenDivision = screenWidth/mapHeight;
    
    ofxJSONElement generatedMaps;
    
    if(!generatedMaps.open("maps/maps.json")) {
        
    }
    else {
        int nMaps = generatedMaps["Maps"].size();
        maps.resize(nMaps);
        for (int i = 0; i < nMaps; i++) {
            mapLoader.loadFromDisk(maps[i],generatedMaps["Maps"][i]["image"].asString());
        }
    }
}
//--------------------------------------------------------------
void MapViewer::update()
{

}
//--------------------------------------------------------------
void MapViewer::draw()
{

//    ofPushStyle();
    ofSetColor(255);
    for (int i = 0; i < (int)maps.size(); ++i) {
        maps[i].update();
        int x = (i%8);
        int y = (i/8);
        maps[i].draw(x*205,y*205, 200, 200);
    }
//    ofPopStyle();
}
//--------------------------------------------------------------
void MapViewer::close()
{
    mapLoader.stopThread();
}

