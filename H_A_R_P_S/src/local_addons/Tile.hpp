//--------------------------------------------------------------
//
//  Tile.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef Tile_h
#define Tile_h

#include <stdio.h>
#include "ofMain.h"
class Tile : public ofRectangle {
    public:
        Tile();
        ~Tile();
    
        Tile(bool _walkable,int _toxicity,ofVec2f _worldPosition, int _gridXPosition,int _gridYPosition,int _size);
    
        int getfCost();
    
        void setHighlighted(bool isHighlighted);
        void printData();
        void draw();
        void drawMicro();
        void displayGrid(bool _show);
    
        ofVec2f worldPosition;
        int gCost;
        int hCost;
        int fCost;
        int gridX;
        int gridY;
        int size;
        int toxicity;
        
        bool walkable;
        bool highlighted;
        bool isPath;
        bool haveChecked;
        bool showGrid;
    
        Tile *parent;
};
#endif /* Tile_h */