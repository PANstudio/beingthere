//--------------------------------------------------------------
//
//  TargetTile.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------
#include "TargetTile.h"
//--------------------------------------------------------------
void TargetTile::setTargetPosition(ofPoint center,int size,int mapWidth,int mapHeight)
{
    _center = center;
    _size = size;
    _mapWidth = mapWidth;
    _mapHeight = mapHeight;
}
//--------------------------------------------------------------
vector<Tile> TargetTile::getTargetTiles(Tile tile)
{
    vector<Tile> neighbours;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if ((x == 0 && y == 0)) {
                continue;
            }
            
            int checkX = tile.gridX + x;
            int checkY = tile.gridY + y;
            if (checkX >= 0 && checkX < _mapWidth && checkY >= 0 && checkY < _mapHeight) {
//                neighbours.push_back(map[checkX][checkY]);
            }
            else {
                
            }
        }
    }
    return neighbours;
}
//--------------------------------------------------------------

