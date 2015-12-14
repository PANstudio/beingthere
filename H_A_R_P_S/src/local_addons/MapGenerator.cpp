//--------------------------------------------------------------
//
//  MapGenerator.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------
#include "MapGenerator.hpp"

//--------------------------------------------------------------
void MapGenerator::generateMap(int width, int height, int offsetEdge, int fillPercent, int numberOfClouds, int smoothingValue, int growthLoops, float seedValue, bool useRandomSeed, int dangerAreaSize, bool generateWalls)
{
    if (map != nullptr) {
        resetMap();
    }
    
    // Set Variables
    _width = width;
    _height = height;
    _offsetEdge = offsetEdge;
    _numberOfClouds = numberOfClouds;
    _dangerAreaSize = dangerAreaSize;
    
    _newWidth = _width*_mapMultiplier;
    _newHeight = _height*_mapMultiplier;
    
    map = new Tile*[width];
    for (int x = 0; x < width; x++)
        map[x] = new Tile[height];
        
    ofSeedRandom(seedValue);
    
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y] = *new Tile(true,0,ofVec2f(x*50,y*50),x,y,50);
        }
    }
    
//    // Grow the Cloud
//    for(int i = 0; i < growthLoops; i++) {
//        growCloud();
//    }
//    
//    // Smooth the Map
//    for (int i = 0; i < smoothingValue; i++) {
//        smoothMap();
//    }
//    
//    // Generate the Danger Zone
//    generateDangerAreas();
//    
//    // Expand the Zones
//    for (int i = 0; i < dangerAreaSize; i++) {
//        expandDangerAreas(i);
//    }
    
}
//--------------------------------------------------------------
void MapGenerator::smoothMap()
{
//    for (int x = 0; x < _width; x ++) {
//        for (int y = 0; y < _height; y ++) {
////            int neighbourWallTiles = getSurroundingWallCount(x,y);
//            if (neighbourWallTiles > 4)
////                map[x][y] = 1;
//            else if (neighbourWallTiles < 4)
////                map[x][y] = 0;
//        }
//    }
}
//--------------------------------------------------------------
void MapGenerator::generateDangerAreas()
{
//    for (int x = 0; x < _width; x++) {
//        for (int y = 0; y < _height; y++) {
//            if (x == 0 || x == _width-1 || y == 0 || y == _height-1) {
//                if (map[x][y] == 1) {
//                    if ((x == 0 || y == 0) && (x < _width-1 && y < _height -1)) {
//                        for (int _x = x; _x <= x+1; _x++) {
//                            for (int _y = y; _y <= y+1 ; _y++) {
//                                if(map[_x][_y] == 0) {
//                                    map[_x][_y] = 2;
//                                }
//                            }
//                        }
//                    }
//                    
//                    if ((x == _width-1 || y == _height-1) && (x > 0 && y > 0)) {
//                        for (int _x = x-1; _x < x; _x++) {
//                            for (int _y = y-1; _y < y ; _y++) {
//                                if(map[_x][_y] == 0) {
//                                    map[_x][_y] = 2;
//                                }
//                            }
//                        }
//                    }
//                    
//                }
//            }
//            else {
//                if (map[x][y] == 1) {
//                    for (int _x = x-1; _x <= x+1; _x++) {
//                        for (int _y = y-1; _y <= y+1 ; _y++) {
//                            if(map[_x][_y] == 0) {
//                                map[_x][_y] = 2;
//                            }
//                        }
//                    }
//                }
//                
//            }
//        }
//    }
}
//--------------------------------------------------------------
void MapGenerator::expandDangerAreas(int num)
{
//    for (int x = 0; x < _width; x++) {
//        for (int y = 0; y < _height; y++) {
//            if (x == 0 || x == _width-1 || y == 0 || y == _height-1) {
//                
//            }
//            else {
//                for (int i = 0; i <= num; i++) {
//                    if (map[x][y] == 2+i) {
//                        for (int _x = x-1; _x <= x+1; _x++) {
//                            for (int _y = y-1; _y <= y+1 ; _y++) {
//                                if(map[_x][_y] == 0) {
//                                    map[_x][_y] = 2+i+1;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
}
//--------------------------------------------------------------
void MapGenerator::draw()
{
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y].showGrid = true;
            map[x][y].draw();
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::resetMap()
{
    delete map;
}
//--------------------------------------------------------------
void MapGenerator::loadMaps(string mapsFile)
{
    
}
//--------------------------------------------------------------