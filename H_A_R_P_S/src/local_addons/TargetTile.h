//--------------------------------------------------------------
//
//  TargetTile.h
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef TargetTile_h
#define TargetTile_h

#include <stdio.h>
#include "ofMain.h"
#include "Tile.h"

class TargetTile {
    public:
        void setTargetPosition(ofPoint center,int size,int mapWidth,int mapHeight);
        vector<Tile> getTargetTiles(Tile tile);

    private:
        vector<Tile> tiles;
        int _size;
        ofPoint _center;
        int _mapWidth;
        int _mapHeight;
    
    protected:
};

#endif /* TargetTile_h */