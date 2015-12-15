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
// *
// *    Generator Functions
// *
//--------------------------------------------------------------
void MapGenerator::resetMap()
{
    delete map;
}
//--------------------------------------------------------------
void MapGenerator::generateCustomMap(int width, int height, int offsetEdge, int tileSize, int numberOfClouds, int smoothingValue, int growthLoops, float seedValue, int dangerAreaSize)
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
    _tileSize = tileSize;
    
    
    _newWidth = _width*tileSize;
    _newHeight = _height*tileSize;
    
    // Create Map Texture for openCV
    mapTexture = new ofImage();
    mapTexture->allocate(_newWidth,_newHeight, OF_IMAGE_COLOR);
    mapTexture->clear();
    
    map = new Tile*[width];
    for (int x = 0; x < width; x++)
        map[x] = new Tile[height];
    
    ofSeedRandom(seedValue);
    
    // Make the Map Walkable
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y] = *new Tile(true,0,ofVec2f(x*_tileSize,y*_tileSize),x,y,_tileSize);
        }
    }
    
    for (int i = 0; i < _numberOfClouds; i++) {
        int x1 = ofRandom(1+_offsetEdge, (_width-1)-_offsetEdge);
        int y1 = ofRandom(1+_offsetEdge, (_height-1)-_offsetEdge);
        map[x1][y1] = *new Tile(false,0,ofVec2f(x1*_tileSize,y1*_tileSize),x1,y1,_tileSize);
    }
    
    // Grow the Cloud
    for(int i = 0; i < growthLoops; i++) {
        growCloud();
    }
    
    // Smooth the Map
    for (int i = 0; i < smoothingValue; i++) {
        smoothMap();
    }
    
    // Generate the Danger Zone
    generateDangerAreas();
    
    // Expand the Zones
    for (int i = 0; i < dangerAreaSize; i++) {
        expandDangerAreas(i);
    }
}
//--------------------------------------------------------------
void MapGenerator::generateMap(Map m)
{
    generateMap(m.width, m.height, m.offsetEdge, m.fillPercent, m.numberOfClouds, m.smoothingValue, m.growthLoops, m.seedValue, m.dangerAreaSize);
}
//--------------------------------------------------------------
void MapGenerator::generateMap(int width, int height, int offsetEdge, int tileSize, int numberOfClouds, int smoothingValue, int growthLoops, float seedValue, int dangerAreaSize)
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
    _tileSize = tileSize;
    
    
    _newWidth = _width*tileSize;
    _newHeight = _height*tileSize;
    
    // Create Map Texture for openCV
    mapTexture = new ofImage();
    mapTexture->allocate(_newWidth,_newHeight, OF_IMAGE_COLOR);
    mapTexture->clear();
    
    map = new Tile*[width];
    for (int x = 0; x < width; x++)
        map[x] = new Tile[height];
        
    ofSeedRandom(seedValue);
    
    // Make the Map Walkable
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y] = *new Tile(true,0,ofVec2f(x*_tileSize,y*_tileSize),x,y,_tileSize);
        }
    }
    
    for (int i = 0; i < _numberOfClouds; i++) {
        int x1 = ofRandom(0+_offsetEdge, (_width)-_offsetEdge);
        int y1 = ofRandom(0+_offsetEdge, (_height)-_offsetEdge);
        map[x1][y1] = *new Tile(false,0,ofVec2f(x1*_tileSize,y1*_tileSize),x1,y1,_tileSize);
    }
    
    // Grow the Cloud
    for(int i = 0; i < growthLoops; i++) {
        growCloud();
    }

    // Smooth the Map
    for (int i = 0; i < smoothingValue; i++) {
        smoothMap();
    }

    // Generate the Danger Zone
    generateDangerAreas();

    // Expand the Zones
    for (int i = 0; i < dangerAreaSize; i++) {
        expandDangerAreas(i);
    }
}
//--------------------------------------------------------------
bool MapGenerator::isInMapRange(int x, int y)
{
    return x >= 0 && x < _width && y >= 0 && y < _height;
}
//--------------------------------------------------------------
Tile MapGenerator::getTileFromGridRef(int x,int y)
{
    return map[x][y];
}
//--------------------------------------------------------------
int MapGenerator::getSurroundingTileCount(int gridX, int gridY)
{
    int wallCount = 0;
    Tile currentTile = getTileFromGridRef(gridX, gridY);
    
    for(auto tile : getNeighbouringTiles(currentTile)) {
        if (tile.gridX == gridX && tile.gridY == gridY) {
            continue;
        }
        
        if (!tile.walkable) {
            wallCount++;
        }
        else {
            
        }
    }
    return wallCount;
}
//--------------------------------------------------------------
void MapGenerator::growCloud()
{
    for (int x = 0; x < _width; x++) {
        for (int y = 0 ; y < _height; y++) {
            if(!map[x][y].walkable) {
                if (x == 0 || x == _width-1 || y == 0 || y == _height-1) {
                    map[x][y].walkable = true;
                }
                else {
                    for (auto tile : getNeighbouringTiles(map[x][y])) {
                        bool a = (ofRandom(0,100) < 75) ? true : false;
                        map[tile.gridX][tile.gridY].walkable = a;
                    }
                }
            }
            else {
                
            }
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::smoothMap()
{
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            int neighbourWallTiles = getSurroundingTileCount(x,y);
            if (neighbourWallTiles > 3)
                map[x][y].walkable = false;
            else if (neighbourWallTiles < 3)
                map[x][y].walkable = true;
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::generateDangerAreas()
{
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            if (x == 0 || x == _width-1 || y == 0 || y == _height-1) {
                
            }
            else {
                Tile currentTile = getTileFromGridRef(x, y);
                for(auto tile : getNeighbouringTiles(currentTile)) {
                    if (!currentTile.walkable && tile.walkable) {
                        map[tile.gridX][tile.gridY].walkable = true;
                        map[tile.gridX][tile.gridY].toxicity = 1;
                    }
                }
            }
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::expandDangerAreas(int num)
{
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            if (x == 0 || x == _width-1 || y == 0 || y == _height-1) {
                
            }
            else {
                for (int i = 0; i <= num; i++) {
                    if (map[x][y].toxicity == 1+i) {
                        for (auto tile : getNeighbouringTiles(map[x][y])) {
                            if (tile.toxicity == 0 && tile.walkable) {
                                map[tile.gridX][tile.gridY].toxicity = 1+i+1;
                            }
                        }
                    }
                }
            }
        }
    }
}
//--------------------------------------------------------------
deque<Tile> MapGenerator::getNeighbouringTiles(Tile tile)
{
    deque<Tile> neighbours;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if ((x == 0 && y == 0)) {
                continue;
            }
            
            int checkX = tile.gridX + x;
            int checkY = tile.gridY + y;
            if (checkX >= 0 && checkX < _width && checkY >= 0 && checkY < _height) {
                neighbours.push_back(map[checkX][checkY]);
            }
            else {
                
            }
        }
    }
    return neighbours;
}
//--------------------------------------------------------------
// *
// *    Drawing Functions
// *
//--------------------------------------------------------------
void MapGenerator::update()
{
    // Grab Screen: This will change to an FBO so its not needed to be drawn
    mapTexture->grabScreen(0,0,_newWidth,_newHeight);
    mapTexture->update();
    
    copy(mapTexture->getPixels(), _mapTexture);
    GaussianBlur(_mapTexture, _blurred, 9);
    
    // Get all the Various Color Images
    inRange(_blurred, Scalar(25,0,0), Scalar(255,0,0), _redOnly);
    inRange(_blurred, Scalar(25,25,0), Scalar(255,255,0), _yellowOnly);
    inRange(_blurred, Scalar(0,25,0), Scalar(0,255,0), _greenOnly);
    inRange(_blurred, Scalar(0,0,50), Scalar(0,0,255), _blueOnly);
    
    // Blur it
    GaussianBlur(_greenOnly, 9);
    
    // Find Contours
    deadColorFinder.findContours(_redOnly);
    dangerColorFinder.findContours(_yellowOnly);
    okColorFinder.findContours(_greenOnly);
    finishColorFinder.findContours(_blueOnly);
    
    deadlyArea.clear();
    dangerArea.clear();
    okArea.clear();
    finishArea.clear();
    
    for (int i = 0; i < deadColorFinder.size(); i++) {
        ofPolyline l;
        l = deadColorFinder.getPolyline(i);
        l.simplify();
        deadlyArea.push_back(l);
    }
    
    for (int i = 0; i < dangerColorFinder.size(); i++) {
        ofPolyline l;
        l = dangerColorFinder.getPolyline(i);
        l.simplify();
        dangerArea.push_back(l);
    }
    for (int i = 0; i < okColorFinder.size(); i++) {
        ofPolyline l;
        l = okColorFinder.getPolyline(i);
        l.simplify();
        okArea.push_back(l);
    }
    for (int i = 0; i < finishColorFinder.size(); i++) {
        ofPolyline l;
        l = finishColorFinder.getPolyline(i);
        l.simplify();
        finishArea.push_back(l);
    }

}
//--------------------------------------------------------------
// *
// *    Drawing Functions
// *
//--------------------------------------------------------------
void MapGenerator::draw()
{
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y].showGrid = false;
            map[x][y].draw();
        }
    }

}
//--------------------------------------------------------------
void MapGenerator::drawMicroMap()
{
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y].drawMicro();
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::drawEditor()
{

    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            if (map[x][y].inside(ofGetMouseX(), ofGetMouseY()) && map[x][y].walkable) {
                ofSetColor(ofColor::red);
            }
            else if (map[x][y].inside(ofGetMouseX(), ofGetMouseY()) && !map[x][y].walkable) {
                ofSetColor(ofColor::green);
            }
            map[x][y].draw();
        }
    }
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(0, 0, _width*_tileSize, _height*_tileSize);
    ofPopStyle();
    ofSetColor(255, 255, 255);
    ofDrawLine(ofGetMouseX(), ofGetMouseY()-10, ofGetMouseX(), ofGetMouseY()+10);
    ofDrawLine(ofGetMouseX()-10, ofGetMouseY(), ofGetMouseX()+10, ofGetMouseY());
}
//--------------------------------------------------------------
void MapGenerator::drawComputerVision()
{
    if (!_redOnly.empty()) {
        ofSetColor(ofColor::white);
        drawMat(_redOnly,0,_newHeight,((_newWidth)/4),((_newHeight)/4));
        ofPushMatrix();
        ofTranslate(0,_newHeight);
        ofScale(0.25,0.25);
        ofSetColor(ofColor::red);
        deadColorFinder.draw();
        ofPopMatrix();
    }
    if (!_yellowOnly.empty()){
        ofSetColor(ofColor::white);
        drawMat(_yellowOnly,0,(_newHeight+(_newHeight/4)),((_newWidth)/4),((_newHeight)/4));
        ofPushMatrix();
        ofTranslate(0,(_newHeight+(_newHeight/4)));
        ofScale(0.25,0.25);
        ofSetColor(ofColor::yellow);
        dangerColorFinder.draw();
        ofPopMatrix();
    }
    if (!_greenOnly.empty()){
        ofSetColor(ofColor::white);
        drawMat(_greenOnly,((_newWidth)/4)*1,(_newHeight+(_newHeight/4)),((_newWidth)/4),((_newHeight)/4));
        ofPushMatrix();
        ofTranslate(((_newWidth)/4)*1,(_newHeight+(_newHeight/4)));
        ofScale(0.25,0.25);
        ofSetColor(ofColor::green);
        okColorFinder.draw();
        ofPopMatrix();
    }
    if (!_blueOnly.empty()){
        ofSetColor(ofColor::white);
        drawMat(_blueOnly,((_newWidth)/4)*1,(_newHeight),((_newWidth)/4),((_newHeight)/4));
        ofPushMatrix();
        ofTranslate(((_newWidth)/4)*1,(_newHeight));
        ofScale(0.25,0.25);
        ofSetColor(ofColor::blue);
        finishColorFinder.draw();
        ofPopMatrix();
    }
    
    ofSetColor(255, 255, 255);
    drawMat(_blurred, _newWidth/2, _newHeight,((_newWidth/2)),((_newHeight/2)));
}
//--------------------------------------------------------------
void MapGenerator::drawPolylines()
{
    
    ofPushMatrix();
    ofTranslate(_newWidth/2, _newHeight);
    ofScale(0.5,0.5);
    
    ofFill();
    
    for (int i = 0; i < okArea.size(); i++) {
        okArea[i].simplify(0.1);
        if (okArea[i].inside(ofGetMouseX(), ofGetMouseY())) {
            ofMessage msg("Player 1: in Safe Area");
            ofSendMessage(msg);
            ofSetColor(ofColor::green);
        }
        else {
            ofSetColor(ofColor::white);
        }
        
        okArea[i].draw();
        
        ofSetColor(ofColor::blue);
        ofDrawRectangle(okArea[i].getCentroid2D().x,okArea[i].getCentroid2D().y,3,3);
    }
    
    for (int i = 0; i < dangerArea.size(); i++) {
        dangerArea[i].simplify(0.1);
        if (dangerArea[i].inside(ofGetMouseX(), ofGetMouseY())) {
            ofMessage msg("Player 1: in danger area");
            ofSendMessage(msg);
            ofSetColor(ofColor::yellow);
        }
        else {
            ofSetColor(ofColor::white);
        }
        dangerArea[i].draw();
        ofSetColor(ofColor::blue);
        ofDrawRectangle(dangerArea[i].getCentroid2D().x,dangerArea[i].getCentroid2D().y,3,3);
    }
    
    for (int i = 0; i < deadlyArea.size(); i++) {
        
        deadlyArea[i].simplify(0.1);
        if (deadlyArea[i].inside(ofGetMouseX(), ofGetMouseY())) {
            ofSetColor(ofColor::red);
            ofMessage msg("Player 1: in deadly area");
            ofSendMessage(msg);
        }
        else {
            ofSetColor(ofColor::white);
        }
        deadlyArea[i].draw();
        ofSetColor(ofColor::blue);
        ofDrawRectangle(deadlyArea[i].getCentroid2D().x,deadlyArea[i].getCentroid2D().y,3,3);
    }
    for (int i = 0; i < finishArea.size(); i++) {
        finishArea[i].simplify(0.1);
        if (finishArea[i].inside(ofGetMouseX(), ofGetMouseY())) {
            ofSetColor(ofColor::blue);
            ofMessage msg("Player 1: in finshed area");
            ofSendMessage(msg);
        }
        else {
            ofSetColor(ofColor::white);
        }
        
        finishArea[i].draw();
        
        ofSetColor(ofColor::blue);
        ofDrawRectangle(finishArea[i].getCentroid2D().x,finishArea[i].getCentroid2D().y,3,3);
    }
    ofSetColor(255, 255, 255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(),10);
    ofPopMatrix();
}
//--------------------------------------------------------------
// *
// *    Mouse Functions
// *
//--------------------------------------------------------------
void MapGenerator::mouseDown(int x, int y, int pressed)
{
    if (pressed == OF_MOUSE_BUTTON_LEFT) {
        for (int x1 = 0; x1 < _width; x1++) {
            for (int y1 = 0; y1 < _height; y1++) {
                if (map[x1][y1].inside(x, y)){
                    map[x1][y1].walkable = false;
                }
            }
        }
    }
    else if (pressed == OF_MOUSE_BUTTON_RIGHT) {
        for (int x1 = 0; x1 < _width; x1++) {
            for (int y1 = 0; y1 < _height; y1++) {
                if (map[x1][y1].inside(x, y)){
                    map[x1][y1].walkable = true;
                }
            }
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::mouseDragged(int x, int y, int pressed)
{
    if (pressed == OF_MOUSE_BUTTON_LEFT) {
        for (int x1 = 0; x1 < _width; x1++) {
            for (int y1 = 0; y1 < _height; y1++) {
                if (map[x1][y1].inside(x, y)){
                    map[x1][y1].walkable = false;
                }
            }
        }
    }
    else if (pressed == OF_MOUSE_BUTTON_RIGHT) {
        for (int x1 = 0; x1 < _width; x1++) {
            for (int y1 = 0; y1 < _height; y1++) {
                if (map[x1][y1].inside(x, y)){
                    map[x1][y1].walkable = true;
                }
            }
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::mouseReleased(int x, int y, int pressed)
{
    
}
//--------------------------------------------------------------
void MapGenerator::mouseOver(int x,int y)
{
    for (int x1 = 0; x1 < _width; x1++) {
        for (int y1 = 0; y1 < _height; y1++) {
            if (map[x1][y1].inside(x, y)) {
                map[x1][y1].setHighlighted(true);
            }
            else {
                map[x1][y1].setHighlighted(false);
            }
        }
    }
}
//--------------------------------------------------------------
// *
// *    Save and Load Functions
// *
//--------------------------------------------------------------
void MapGenerator::loadMaps(string mapsFile)
{
    ofxJSONElement mapConfig;
    
    if(!mapConfig.open(mapsFile)) {
        cout << "File not Loaded" << endl;
        return;
    }
    else {
        maps.clear();
        _MapInfo.clear();
        vector<string> difficultyLevel = {"NOVICE", "ROOKIE", "NORMAL", "HARD","REALLY HARD","IMPOSSIBLE","GOD LIKE"};
        
        for (int diff = 0; diff < difficultyLevel.size(); diff++) {
            int getMapNos = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]].size();
            vector <Map> map;
            for (int levels = 0; levels < getMapNos; levels++) {
                Map mObj;
                mObj.difficulty = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["difficulty"].asString();
                mObj.level = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["level"].asInt();
                mObj.fillPercent = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["fillPercent"].asInt();
                mObj.numberOfClouds = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["numberofclouds"].asInt();
                mObj.growthLoops = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["growthloops"].asInt();
                mObj.smoothingValue = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["smoothingloops"].asInt();
                mObj.width = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["width"].asInt();
                mObj.height = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["height"].asInt();
                mObj.offsetEdge = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["offsetedge"].asInt();
                mObj.timeNeededToSolveMap = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["timetocomplete"].asInt();
                mObj.seedValue = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["randomseed"].asFloat();
                mObj.dangerAreaSize = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["dangerareasize"].asInt();
                mObj.dangerAreaToxicity = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["dangerAreaToxicity"].asInt();
                mObj.deadAreaToxicity = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["deadAreaToxicity"].asInt();
                
                mObj.startingPosition.x = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["positions"]["startposx"].asInt();
                mObj.startingPosition.y = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["positions"]["startposy"].asInt();
                mObj.endPosition.x = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["positions"]["endposx"].asInt();
                mObj.endPosition.y = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["positions"]["endposy"].asInt();
                
                map.push_back(mObj);
            }
            
            maps.push_back(map);
            MapDetails m;
            m.Difficulty = difficultyLevel[diff];
            m.numberOfLevels = getMapNos;
            _MapInfo.push_back(m);
        }
    }
}
//--------------------------------------------------------------
void MapGenerator::saveMap()
{
    stringstream ss;
    ss << "{" << endl;
    int x = 0;
    int y = 0;
    ss << "\"Line " << 0 << "\"" <<  endl;
    ss << "{" << endl;
    while (x < _width) {
        if(x == _width) {       }
        else {
            ss << "\"" << map[x][y] << "\"" << ",";
        }
        
        
        x++;
        if (x == _width) {
            ss << "}" << endl;
            ss << "{" << endl;
            y++;
            x = 0;
        }
        if(y == _height) {
            break;
        }
    }
    ss << "}" << endl;
    cout << ss.str() << endl;
}
//--------------------------------------------------------------
vector<MapDetails> MapGenerator::getMapsInfo()
{
    return _MapInfo;
}
//--------------------------------------------------------------
Map MapGenerator::getMap(string mapDifficulty,int mapLevel)
{
    if (!maps.empty()) {
        for (int i = 0; i < maps.size(); i++) {
            for (int x = 0; x < maps[i].size(); x++) {
                if (maps[i][x].difficulty == mapDifficulty) {
                    if (maps[i][x].level == mapLevel) {
                        maps[i][x].printDetails();
                        return maps[i][x];
                    }
                }
            }
        }
    }
}