//--------------------------------------------------------------
//
//  MapGenerator.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef MapGenerator_hpp
#define MapGenerator_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxJSON.h"
#include "MapHelpers.hpp"
#include "Tile.hpp"

using namespace cv;
using namespace ofxCv;

class MapGenerator {
public:
    
    void resetMap();
    void update();
    void generateMap(int width,int height,int offsetEdge, int tileSize,int numberOfClouds,int smoothingValue,int growthLoops,float seedValue, int dangerAreaSize);
    void generateMap(Map m);
    void generateCustomMap(int width,int height,int offsetEdge, int tileSize,int numberOfClouds,int smoothingValue,int growthLoops,float seedValue, int dangerAreaSize);
    
    void smoothMap();
    void growCloud();
    void generateDangerAreas();
    void expandDangerAreas(int times);
    
    vector<ofPolyline> getDeadlyOutlines();
    vector<ofPolyline> getDangerOutlines();
    vector<ofPolyline> getOkOutlines();
    
    deque<Tile> getNeighbouringTiles(Tile tile);
    int getSurroundingTileCount(int gridX, int gridY);
    bool isInMapRange(int x, int y);
    Tile getTileFromGridRef(int x,int y);
    
    void draw();
    void drawComputerVision();
    void drawPolylines();
    void drawMicroMap();
    void drawEditor();
    
    void mouseOver(int x, int y);
    void mouseDown(int x, int y,int pressed);
    void mouseReleased(int x, int y,int pressed);
    void mouseDragged(int x, int y,int pressed);
    
    void loadMaps(string mapsFile);
    
    Map getMap(string mapDifficulty,int mapLevel);
    vector<MapDetails> getMapsInfo();
    
    // To Do
    void saveMap();
private:
    
    // Map Object
    Tile **map;
    
    int mapSizeX;
    int mapSizeY;
    
    int _width;
    int _height;
    int _tileSize;
    bool _useRandomSeed;
    int _fillPercent;
    float _seedValue;
    int _newWidth;
    int _newHeight;
    int _numberOfClouds;
    int _GaussianBlur;
    float _simplifyContours;
    int _offsetEdge;
    int _dangerAreaSize;
    int _mapMultiplier;
    
    ofxCv::ContourFinder deadColorFinder;
    ofxCv::ContourFinder dangerColorFinder;
    ofxCv::ContourFinder okColorFinder;
    ofxCv::ContourFinder finishColorFinder;
    
    Mat _mapTexture;
    Mat _blurred;
    Mat _redOnly;
    Mat _yellowOnly;
    Mat _greenOnly;
    Mat _blueOnly;
    
    ofImage *mapTexture;
    
    vector <ofPolyline> deadlyArea;
    vector <ofPolyline> dangerArea;
    vector <ofPolyline> okArea;
    vector <ofPolyline> finishArea;
    vector<MapDetails> _MapInfo;
    vector<vector<Map> > maps;
    
protected:
    
    
};


#endif /* MapGenerator_hpp */