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
bool sortAscending(MyImage a, MyImage b) {
    return a.getDifficulty() < b.getDifficulty();
}
//--------------------------------------------------------------
bool sortDescending(MyImage a, MyImage b) {
    return a.getDifficulty() > b.getDifficulty();
}
//--------------------------------------------------------------
void MapViewer::setup()
{
    screenWidth = ofGetWidth();
    mapHeight = 205;
    screenDivision = screenWidth/mapHeight;
    
    yPosition = 0;
    
    ofxJSONElement generatedMaps;
    
    if(!generatedMaps.open("maps/maps.json")) {
        ofLogError() << "Couldn't find Maps.json";
    }
    else {
        int nNoviceMaps = 0;
        int nRookieMaps = 0;
        int nHardMaps = 0;
        int nImpossibleMaps = 0;
        int nGodLikeMaps = 0;
        
        int nMaps = 0;
        nMaps = generatedMaps["Maps"].size();
        maps.resize(nMaps);

        
        
        for (int i = 0; i < nMaps; i++) {
            Map m;
//            if (generatedMaps["Maps"][i]["difficulty"].asString() == "NOVICE") {
////
////                m.difficulty = generatedMaps["Maps"][i]["difficulty"].asString();
////                m.level = generatedMaps["Maps"][i]["level"].asInt();
////                m.tileSize = generatedMaps["Maps"][i]["tilesize"].asInt();
////                m.numberOfClouds = generatedMaps["Maps"][i]["numberofclouds"].asInt();
////                m.growthLoops = generatedMaps["Maps"][i]["growthloops"].asInt();
////                m.smoothingValue = generatedMaps["Maps"][i]["smoothingloops"].asInt();
////                m.width = generatedMaps["Maps"][i]["width"].asInt();
////                m.height = generatedMaps["Maps"][i]["height"].asInt();
////                m.offsetEdge = generatedMaps["Maps"][i]["offsetedge"].asInt();
////                m.timeNeededToSolveMap = generatedMaps["Maps"][i]["timetocomplete"].asInt();
////                m.seedValue = generatedMaps["Maps"][i]["randomseed"].asFloat();
////                m.dangerAreaSize = generatedMaps["Maps"][i]["dangerareasize"].asInt();
////                m.dangerAreaToxicity = generatedMaps["Maps"][i]["dangerAreaToxicity"].asInt();

            mapInfo.push_back(m);
            mapLoader.loadFromDisk(maps[i],generatedMaps["Maps"][i]["image"].asString());
            maps[i].setTag(generatedMaps["Maps"][i]["difficulty"].asString());
            maps[i].setDifficulty(generatedMaps["Maps"][i]["difficultylevel"].asString());
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
    sort(maps.begin(), maps.end(),sortAscending);
    ofPushMatrix();
    ofTranslate(0,yPosition);
    ofSetColor(255);

    for (int i = 0; i < (int)maps.size(); ++i) {
        int x = (i%screenDivision);
        int y = (i/screenDivision);
        maps[i].draw(10+(x*205),10+(y*205), 200, 200);
        ofDrawBitmapStringHighlight(maps[i].getTag(),10+(x*205),20+(y*205));
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void MapViewer::scroll(float y)
{
    yPosition += y;
}
//--------------------------------------------------------------
void MapViewer::close()
{
    mapLoader.stopThread();
}

