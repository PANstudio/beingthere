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
#include "ofxPathfinder.h"
#include "SimpleButton.h"

using namespace cv;
using namespace ofxCv;

class MapGenerator {
public:
    
    //--------------------------------------------------------------
    // *
    // *    Setup Functions
    // *
    //--------------------------------------------------------------
    // Initialize with these variables
    void setup(int width = 100,int height = 100, int tileSize = 5);
    
    // Generate New Grid
    void generateNewGrid(int width,int height,int tileSize);
    
    // This resets the map entirely including the size and tile size
    void resetMap();
    
    // This clears the array of data so all tiles are walkable
    void clearMap();
    
    // Elegantly Clean Memory
    void close();
    //--------------------------------------------------------------
    // *
    // *    Generator Setup Functions
    // *
    //--------------------------------------------------------------
    // Generate a Predefined Map
    void generateMap(Map m);

    // Generate a New Map
    void generateNewMap(int width,int height,int offsetEdge, int tileSize,int numberOfClouds,int smoothingValue,int growthLoops,float seedValue, int dangerAreaSize);
    
    // Generate Map with these parameters
    void generateMap(int offsetEdge, int tileSize,int numberOfClouds,int smoothingValue,int growthLoops,float seedValue, int dangerAreaSize);
    
    // Generate Map Based on users inputs
    void generateCustomMap(int smoothingValue,int growthLoops, int dangerAreaSize);
    
    // Generate Images for flushing
    void generateImages(int width,int height,int tileSize);
    
    // Generate Clouds
    void generateClouds(int width, int height,int offsetEdge,int numberOfClouds);
    //--------------------------------------------------------------
    // *
    // *    Animator Functions
    // *
    //--------------------------------------------------------------
    void startAnimation(int numberOfClouds,int smoothingLoops,int growthLoops,float seedValue);
    
    bool isAnimating();
    
    bool isAnimationFinished();
    
    // Only used for visualising the system
    void animate();
    
    
    //--------------------------------------------------------------
    // *
    // *    Generator Operations
    // *
    //--------------------------------------------------------------
    // Generates the Lines and Areas
    void generatePolylines(int blurMap,int deadlyThreshold, int dangerThreshold,int okThreshold);
    
    // Smooths the Map
    void smoothMap();
    
    // Grows the origin points
    void growCloud();
    
    // Generates the danger points
    void generateDangerAreas();
    
    // Expands the area
    void expandDangerAreas(int times);
    
    // Check if Tile is Valid
    bool isInMapRange(int x, int y);
    
    //--------------------------------------------------------------
    // *
    // *    Getters
    // *
    //--------------------------------------------------------------
    vector<ofPolyline> getDeadlyOutlines();
    vector<ofPolyline> getDangerOutlines();
    vector<ofPolyline> getOkOutlines();
    
    deque<Tile> getNeighbouringTiles(Tile tile);
    
    int getSurroundingTileCount(int gridX, int gridY);

    Tile getTileFromGridRef(int x,int y);
    
    void getPlayerCoordinates(vector <ofPoint> playerCoords);
    
    ofImage getFinderImage();
    
    int getWidth();
    int getHeight();
    int getTileSize();
    int getGrowthLoops();
    int getNumberOfClouds();
    int getSmoothingLoops();
    int getDangerAreaSize();
    float getRandomSeedValue();
    
    Mat getSmoothMap();
    
    //--------------------------------------------------------------
    // *
    // *    Setters
    // *
    //--------------------------------------------------------------
    void setWidth(int width);
    void setHeight(int height);
    void setTileSize(int tileSize);
    void setDangerAreaSize(int size);
    void setGrowthLoops(int growthLoops);
    void setRandomSeedValue(float randomSeed);
    void setNumberOfClouds(int numberOfClouds);
    void setSmoothingLoops(int smoothingLoops);
    
    //--------------------------------------------------------------
    // *
    // *    Draw Functions
    // *
    //--------------------------------------------------------------
    void draw(bool showGrid);
    void drawComputerVision(int x, int y);
    void drawPolylines();
    void drawMicroMap();
    void drawEditor();
    void drawFinderMap(int x,int y);
    
    void fireEvent(int playerId, string area);
    
    //--------------------------------------------------------------
    // *
    // *    Mouse Functions
    // *
    //--------------------------------------------------------------
    void mouseOver(int x, int y);
    void mouseDown(int x, int y,int pressed);
    void mouseReleased(int x, int y,int pressed);
    void mouseDragged(int x, int y,int pressed);
    
    //--------------------------------------------------------------
    // *
    // *    Load and Save Systems
    // *
    //--------------------------------------------------------------
    void loadMaps(string mapsFile);
    
    Map getMap(string mapDifficulty,int mapLevel);
    vector<MapDetails> getMapsInfo();
    
    vector<SimpleButton> buttons;
    
    // To Do
    void saveMap();
    void saveMap(Map m);
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
    Mat _blurredGrayscale;
    Mat _distanceImage;
    
    ofImage *finderImg;
    ofImage *mapTexture;
    ofImage *microImg;
    
    unsigned char * fboPixels;
    
    ofFbo *mapFbo;
    
    vector <ofPolyline> deadlyArea;
    vector <ofPolyline> dangerArea;
    vector <ofPolyline> okArea;
    vector <ofPolyline> finishArea;
    vector <MapDetails> _MapInfo;
    vector <vector<Map> > maps;
    
protected:
    int whichButton;
    int aX;
    int aY;
    bool genLoop;
    bool smLoop;
    bool danLoop;
    bool grLoop;
    bool exLoop;
    
    bool bAnimate;
    int _smoothingLoops;
    int _growthLoops;
    float _RseedValue;
    
    vector<ofVec2f> cloudPos;
};


#endif /* MapGenerator_hpp */