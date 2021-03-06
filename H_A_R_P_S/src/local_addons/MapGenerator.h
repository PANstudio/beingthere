//--------------------------------------------------------------
//
//  MapGenerator.h
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef MapGenerator_h
#define MapGenerator_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxJSON.h"
#include "MapHelpers.h"
#include "Tile.h"
#include "ofxPathfinder.h"
#include "SimpleButton.h"

using namespace cv;
using namespace ofxCv;

struct event {
    string id;
    string area;
};

class MapGenerator : public ofThread {
public:
    
    //--------------------------------------------------------------
    // *
    // *    Setup Functions
    // *
    //--------------------------------------------------------------
    //! Initialize with these variables
    void setup(int width = 100,int height = 100, int tileSize = 5);
    
    //! Generate New Grid
    void generateNewGrid(int width,int height,int tileSize);
    
    //! This resets the map entirely including the size and tile size
    void resetMap();
    
    //! This clears the array of data so all tiles are walkable
    void clearMap();
    
    //! Elegantly Clean Memory
    void close();
    
    //! update
    void updateCV(int red,int green);
    
    void updateEditor();
    //--------------------------------------------------------------
    // *
    // *    Generator Setup Functions
    // *
    //--------------------------------------------------------------
    //! Generate a Predefined Map
    void generateMap(Map m);

    //! Generate a New Map
    void generateNewMap(int width,int height,int offsetEdge, int tileSize,int numberOfClouds,int smoothingValue,int growthLoops,float seedValue, int dangerAreaSize);
    
    //! Generate Map with these parameters
    void generateMap(int offsetEdge, int tileSize,int numberOfClouds,int smoothingValue,int growthLoops,float seedValue, int dangerAreaSize);
    
    //! Generate Map Based on users inputs
    void generateCustomMap(int smoothingValue,int growthLoops, int dangerAreaSize);
    
    //! Generate Images for flushing
    void generateImages(int width,int height,int tileSize);
    
    //! Generate Clouds
    void generateClouds(int width, int height,int offsetEdge,int numberOfClouds);
    
    //! Regenerate Clouds
    void reGenerateClouds();
    
    //--------------------------------------------------------------
    // *
    // *    Animator Functions
    // *
    //--------------------------------------------------------------
    //! Start Animating Generation
    void startAnimation(int numberOfClouds,int smoothingLoops,int growthLoops,float seedValue);
    
    //! Is the Generating Animating
    bool isAnimating();
    
    //! Has the Animation Finished
    bool isAnimationFinished();
    
    //! Only used for visualising the system
    void animate();
    
    //--------------------------------------------------------------
    // *
    // *    Generator Operations
    // *
    //--------------------------------------------------------------
    //! Generates the Lines and Areas
    void generatePolylines();
    
    //! Smooths the Map
    void smoothMap();
    
    //! Grows the origin points
    void growCloud();
    
    //! Generates the danger points
    void generateDangerAreas();
    
    //! Expands the area
    void expandDangerAreas(int times);
    
    //! Check if Tile is Valid
    bool isInMapRange(int x, int y);
    
    //--------------------------------------------------------------
    // *
    // *    Getters
    // *
    //--------------------------------------------------------------
    vector<ofPolyline> getDeadlyOutlines();
    vector<ofPolyline> getDangerOutlines();
    vector<ofPolyline> getOkOutlines();
    
    //! Get the Neighbouring Tiles
    deque<Tile> getNeighbouringTiles(Tile tile);
    
    //! Get the Count of the Surrounding Tiles
    int getSurroundingTileCount(int gridX, int gridY);

    //! Get Tile from Coords
    Tile getTileFromGridRef(int x,int y);
    
    //! Get the Players Cooridinates
    void getPlayerCoordinates(vector <ofPoint> playerCoords);
    
    //! Get the Finder Image
    ofImage getFinderImage();
    
    //! Get all the variables
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
    //! Set the Width of the Map
    void setWidth(int width);

    //! Set the Height of the Map
    void setHeight(int height);
    
    //! Set the Tile Size
    void setTileSize(int tileSize);
    
    //! Set the Danger Size
    void setDangerAreaSize(int size);
    
    //! Set how many growth loops there are
    void setGrowthLoops(int growthLoops);
    
    //! Set Random Seed Value
    void setRandomSeedValue(float randomSeed);
    
    //! Set Number of Clouds
    void setNumberOfClouds(int numberOfClouds);
    
    //! Set number of smoothing loops
    void setSmoothingLoops(int smoothingLoops);
    
    //! Set Red Threshold
    void setRedThreshold(int redThresh);

    //! Set Green Threshold
    void setGreenThreshold(int greenThresh);

    //--------------------------------------------------------------
    // *
    // *    Draw Functions
    // *
    //--------------------------------------------------------------
    //! Draw
    void draw(bool showGrid);

    //! Draw the Computer Vision
    void drawComputerVision(int x, int y);

    //! Draw the Polyines
    void drawPolylines();
    
    //! Draw the Micromap
    void drawMicroMap();
    
    //! Draw the Editor
    void drawEditor();

    //! Draw the Finder Map
    void drawFinderMap(int x,int y);
    
    //! 
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
    
    ofEvent<event> eventListener;
    
    // To Do
    void saveMap(string mapName,string style,Map m);
    void saveMap(Map m);
    void saveTempMap(string mapName);
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
    int _redThreshold;
    int _greenThreshold;
    
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
    bool inOkArea;
    bool inDangerArea;
    bool inDeadlyArea;
    
    bool bAnimate;
    int _smoothingLoops;
    int _growthLoops;
    float _RseedValue;
    
    vector<ofVec2f> cloudPos;
};


#endif /* MapGenerator_h */