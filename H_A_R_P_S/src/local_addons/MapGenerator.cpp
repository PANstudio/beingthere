//--------------------------------------------------------------
//
//  MapGenerator.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------
#include "MapGenerator.hpp"
#pragma mark - Setup
//--------------------------------------------------------------
// *
// *    Setup Functions
// *
//--------------------------------------------------------------
void MapGenerator::setup(int width,int height, int tileSize)
{
    for (int i = 0; i < 14; i++) {
        if (i < 7) {
            buttons.push_back(SimpleButton(510+(i*45), 10, 40, 40, i, "", ofColor(255,175)));
        }
        else {
            buttons.push_back(SimpleButton(510+((i-7)*45), 60, 40, 40, i, "", ofColor(255,175)));
        }
    }
    whichButton = 0;
    bAnimate = false;
    
    _width = width;
    _height = height;
    
    generateNewGrid(width, height, tileSize);
}
//--------------------------------------------------------------
// *    Reset Map
//--------------------------------------------------------------
void MapGenerator::resetMap()
{
    delete map;
}
//--------------------------------------------------------------
// *    Clean Map
//--------------------------------------------------------------
void MapGenerator::clearMap()
{
    // Make the Map Walkable
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y].walkable = true;
            map[x][y].toxicity = 0;
        }
    }
}
//--------------------------------------------------------------
// *    Generate New Grid
//--------------------------------------------------------------
void MapGenerator::generateNewGrid(int width, int height, int tileSize)
{
    if (map == nullptr) {
        resetMap();
    }
    
    map = new Tile*[width];
    for (int x = 0; x < width; x++)
        map[x] = new Tile[height];
    
    // Make the Map Walkable
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y] = *new Tile(true,0,ofVec2f(x*tileSize,y*tileSize),x,y,tileSize);
        }
    }
}
//--------------------------------------------------------------
// *    Close
//--------------------------------------------------------------
void MapGenerator::close()
{
    resetMap();
}
#pragma mark - Generation
//--------------------------------------------------------------
// *
// *    Generator Functions
// *
//--------------------------------------------------------------
void MapGenerator::generateMap(Map m)
{
    if (m.width != _width && m.height != _height) {
        generateNewMap(m.width,m.height,m.offsetEdge, m.tileSize, m.numberOfClouds, m.smoothingValue, m.growthLoops, m.seedValue, m.dangerAreaSize);
    }
    else {
        generateMap(m.offsetEdge, m.tileSize, m.numberOfClouds, m.smoothingValue, m.growthLoops, m.seedValue, m.dangerAreaSize);
    }
}
//--------------------------------------------------------------
// *    Generate New Map
//--------------------------------------------------------------
void MapGenerator::generateNewMap(int width, int height, int offsetEdge, int tileSize, int numberOfClouds, int smoothingValue, int growthLoops, float seedValue, int dangerAreaSize)
{
    // Generate New Grid
    generateNewGrid(width, height, tileSize);
    
    // Set Variables
    _width = width;
    _height = height;
    _offsetEdge = offsetEdge;
    _numberOfClouds = numberOfClouds;
    _dangerAreaSize = dangerAreaSize;
    _tileSize = tileSize;
    
    _newWidth = _width*tileSize;
    _newHeight = _height*tileSize;
    
    ofSeedRandom(seedValue);
    
    generateClouds(_width, _height, offsetEdge, numberOfClouds);
    
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
    
    generateImages(width, height, tileSize);
    
}
//--------------------------------------------------------------
// *    Generate Custom Map
//--------------------------------------------------------------
void MapGenerator::generateCustomMap(int smoothingValue, int growthLoops, int dangerAreaSize)
{
    // Generate the Danger Zone
    generateDangerAreas();
    
    // Expand the Zones
    for (int i = 0; i < dangerAreaSize; i++) {
        expandDangerAreas(i);
    }
    
    generateImages(_width, _height, _tileSize);
}
//--------------------------------------------------------------
// *    Generate Random Map
//--------------------------------------------------------------
void MapGenerator::generateMap(int offsetEdge, int tileSize, int numberOfClouds, int smoothingValue, int growthLoops, float seedValue, int dangerAreaSize)
{
    
    _offsetEdge = offsetEdge;
    _numberOfClouds = numberOfClouds;
    _dangerAreaSize = dangerAreaSize;
    
    ofSeedRandom(seedValue);
    
    // Clear the Current context
    clearMap();

    // Generate Clouds
    generateClouds(_width, _height, offsetEdge, numberOfClouds);
    
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
    
    generateImages(_width, _height, tileSize);
}
//--------------------------------------------------------------
// *    Generate Images for Line Generator
//--------------------------------------------------------------
void MapGenerator::generateImages(int width, int height, int tileSize)
{
    int nWidth = width*tileSize;
    int nHeight = height*tileSize;
    
    // Create Map Texture for openCV
    mapTexture = new ofImage();
    mapTexture->allocate(nHeight,nHeight, OF_IMAGE_COLOR);
    mapTexture->clear();
    
    fboPixels = new unsigned char[nWidth*nHeight*3];
    
    mapFbo = new ofFbo();
    mapFbo->allocate(nWidth, nHeight);
    
    mapFbo->begin();
    ofClear(0, 0, 0);
    mapFbo->end();
    
    if (finderImg == nullptr) {
        delete finderImg;
    }
    
    if (microImg == nullptr) {
        delete microImg;
    }
    
    microImg = new ofImage();
    microImg->allocate(_width, _height, OF_IMAGE_COLOR);
    finderImg = new ofImage();
    finderImg->allocate(_width, _height, OF_IMAGE_GRAYSCALE);
    
    _distanceImage = Mat(_height, _width, CV_8UC1);
    for (int y = 0; y < _height; y++) {
        for (int x  = 0; x < _width; x++) {
            _distanceImage.at<uchar>(y,x) = 255;
        }
    }
    
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            if(!map[x][y].walkable) {
                finderImg->setColor(x, y,ofColor::black);
                _distanceImage.at<uchar>(y, x) = 255;
                microImg->setColor(x, y, ofColor::red);
            }
            else {
                if (map[x][y].toxicity == 0) {
                    _distanceImage.at<uchar>(y, x) = 0;
                    finderImg->setColor(x, y,ofColor::white);
                    microImg->setColor(x, y, ofColor::green);
                }
                else {
                    ofColor c;
                    int a = 255-ofMap(255/(map[x][y].toxicity+1),255,0,0,255);
                    c.set(ofMap(255/(map[x][y].toxicity+1),255,0,0,255));
                    finderImg->setColor(x, y,c);
                    _distanceImage.at<uchar>(y, x) = a;
                    c.set(ofMap(255/(map[x][y].toxicity+1),255,0,0,255), ofMap(255/(map[x][y].toxicity+1),255,0,0,255), 0);
                    microImg->setColor(x, y, c);
                }
            }
        }
    }
    
    GaussianBlur(_distanceImage, 21);
    
    microImg->update();
}
//--------------------------------------------------------------
// *    Generate Clouds
//--------------------------------------------------------------
void MapGenerator::generateClouds(int width, int height, int offsetEdge,int numberOfClouds)
{
    
    // Clear Previous Clouds
    // and Generate new points
    cloudPos.clear();
    for (int i = 0; i < numberOfClouds; i++) {
        int x1 = ofRandom(0+offsetEdge, (width)-offsetEdge);
        int y1 = ofRandom(0+offsetEdge, (height)-offsetEdge);
        cloudPos.push_back(ofVec2f(x1, y1));
    }

    for (int i = 0; i < cloudPos.size(); i++) {
        int wx = cloudPos[i].x;
        int wy = cloudPos[i].y;
        map[wx][wy].walkable = false;
    }
}
//--------------------------------------------------------------
// *
// * Animation
// *
//--------------------------------------------------------------
void MapGenerator::startAnimation(int numberOfClouds,int smoothingLoops,int growthLoops,float seedValue)
{
    smLoop = false;
    danLoop = false;
    grLoop = false;
    bAnimate = true;
    genLoop = true;
    
    _smoothingLoops = smoothingLoops;
    _growthLoops = growthLoops;
    _RseedValue = seedValue;
    
    ofSeedRandom(_RseedValue);
    generateClouds(_width, _height, _offsetEdge, numberOfClouds);
    
    aX = 0;
    aY = 0;
}
//--------------------------------------------------------------
bool MapGenerator::isAnimating()
{
    return bAnimate;
}
//--------------------------------------------------------------
bool MapGenerator::isAnimationFinished()
{
    if (!bAnimate ) {
        return true;
    }
    else {
        return false;
    }
}
//--------------------------------------------------------------
void MapGenerator::animate()
{
    if (!genLoop && !grLoop && !smLoop && !danLoop) {
        bAnimate = false;
    }
    
    if ((aX >= 99 && aY == 99) && genLoop) {
        genLoop = false;
        aX = 0;
        aY = 0;
        grLoop = true;
    }
    
    if ((aX >= 99 && aY == 99) && grLoop) {
        if (_growthLoops == 0) {
            grLoop = false;
            smLoop = true;
            aX = 0;
            aY = 0;
        }
        else {
            _growthLoops--;
            grLoop = true;
            aX = 0;
            aY = 0;
        }
    }
    
    if ((aX >= 99 && aY == 99) && smLoop) {
        if (_smoothingLoops == 0) {
            smLoop = false;
            danLoop = true;
            aX = 0;
            aY = 0;
        }
        else {
            _smoothingLoops--;
            smLoop = true;
            aX = 0;
            aY = 0;
        }
    }
    
    if ((aX >= 99 && aY == 99) && danLoop) {
        danLoop = false;
        expandDangerAreas(4);
    }
    
    if (aY < 99) {
        if (aX >= 99) {
            aY++;
            aX = 0;
        }
        while (aX < _width) {
            if (genLoop) {
                for (int i = 0; i < cloudPos.size(); i++) {
                    int wx = cloudPos[i].x;
                    int wy = cloudPos[i].y;
                    if (wx == aX && wy == aY) {
                        map[aX][aY].walkable = false;
                    }
                }
            }
            
            if (grLoop) {
                if(!map[aX][aY].walkable) {
                    if (aX == 0 || aX == _width-1 || aY == 0 || aY == _height-1) {
                        map[aX][aY].walkable = true;
                    }
                    else {
                        for (auto tile : getNeighbouringTiles(map[aX][aY])) {
                            bool a = (ofRandom(0,100) < 50) ? true : false;
                            map[tile.gridX][tile.gridY].walkable = a;
                        }
                    }
                }
                else {
                    
                }
            }
            
            if (smLoop) {
                int neighbourWallTiles = getSurroundingTileCount(aX,aY);
                if (neighbourWallTiles > 4)
                    map[aX][aY].walkable = false;
                else if (neighbourWallTiles < 4)
                    map[aX][aY].walkable = true;
            }
            
            if (danLoop) {
                if (aX == 0 || aX == 100-1 || aY == 0 || aY == 100-1) {
                    
                }
                else {
                    Tile currentTile = getTileFromGridRef(aX, aY);
                    for(auto tile : getNeighbouringTiles(currentTile)) {
                        if (!currentTile.walkable && tile.walkable) {
                            map[tile.gridX][tile.gridY].walkable = true;
                            map[tile.gridX][tile.gridY].toxicity = 1;
                        }
                    }
                }
            }
            
            if (exLoop) {
                
            }
            aX++;
        }
    }
    generateImages(_width, _height, _tileSize);
}
//--------------------------------------------------------------
// *
// *    Generator Operations
// *
//--------------------------------------------------------------
void MapGenerator::generatePolylines(int blurMap,int iRR[2],int iRY[2],int iRG[2])
{
    mapFbo->begin();
    ofClear(0, 0, 0);
    draw(false);
    glReadPixels(0, 0, _newWidth, _newHeight, GL_RGB, GL_UNSIGNED_BYTE, fboPixels);
    mapFbo->end();
    
    mapTexture->setFromPixels(fboPixels, _newWidth, _newHeight, OF_IMAGE_COLOR);
    mapTexture->update();
    
    copy(mapTexture->getPixels(), _mapTexture);
    GaussianBlur(_mapTexture, _blurred,blurMap);
    
    // Get all the Various Color Images
    inRange(_blurred, Scalar(iRR[0],0,0), Scalar(iRR[1],0,0), _redOnly);
    inRange(_blurred, Scalar(iRY[0],iRY[0],0), Scalar(iRY[1],iRY[1],0), _yellowOnly);
    inRange(_blurred, Scalar(0,iRG[0],0), Scalar(0,iRG[1],0), _greenOnly);
    
    // Find Contours
    deadColorFinder.findContours(_redOnly);
    dangerColorFinder.findContours(_yellowOnly);
    okColorFinder.findContours(_greenOnly);
    
    deadlyArea.clear();
    dangerArea.clear();
    okArea.clear();
    
    for (int i = 0; i < deadColorFinder.size(); i++) {
        ofPolyline l;
        l = deadColorFinder.getPolyline(i).getSmoothed(3);
        l.simplify();
        deadlyArea.push_back(l);
    }
    
    for (int i = 0; i < dangerColorFinder.size(); i++) {
        ofPolyline l;
        l = dangerColorFinder.getPolyline(i);;
        l.simplify();
        dangerArea.push_back(l);
    }
    for (int i = 0; i < okColorFinder.size(); i++) {
        ofPolyline l;
        l = okColorFinder.getPolyline(i);
        l.simplify();
        okArea.push_back(l);
    }
}
//--------------------------------------------------------------
void MapGenerator::smoothMap()
{
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            int neighbourWallTiles = getSurroundingTileCount(x,y);
            if (neighbourWallTiles > 4)
                map[x][y].walkable = false;
            else if (neighbourWallTiles < 4)
                map[x][y].walkable = true;
        }
    }
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
                        bool a = (ofRandom(0,100) < 50) ? true : false;
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
bool MapGenerator::isInMapRange(int x, int y)
{
    return x >= 0 && x < _width && y >= 0 && y < _height;
}
#pragma mark - Getters
//--------------------------------------------------------------
// *
// *    Getters Functions
// *
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
vector<ofPolyline> MapGenerator::getDeadlyOutlines()
{
    return deadlyArea;
}
//--------------------------------------------------------------
vector<ofPolyline> MapGenerator::getDangerOutlines()
{
    return dangerArea;
}
//--------------------------------------------------------------
vector<ofPolyline> MapGenerator::getOkOutlines()
{
    return okArea;
}
//--------------------------------------------------------------
void MapGenerator::getPlayerCoordinates(vector<ofPoint> playerCoords)
{
    ofPushMatrix();

    for (int player = 0; player < playerCoords.size(); player++) {
        for (int i = 0; i < okArea.size(); i++) {
            okArea[i].simplify(0.1);
            if (okArea[i].inside(playerCoords[player].x,playerCoords[player].y)) {
                fireEvent(player, "OK");
            }
            ofSetColor(ofColor::green);
            okArea[i].draw();
        }
        
        for (int i = 0; i < dangerArea.size(); i++) {
            dangerArea[i].simplify(0.1);
            if (dangerArea[i].inside(playerCoords[player].x,playerCoords[player].y)) {
                fireEvent(player, "Danger");
            }
            ofSetColor(ofColor::yellow);
            dangerArea[i].draw();
        }
        
        for (int i = 0; i < deadlyArea.size(); i++) {
            deadlyArea[i].simplify(0.1);
            if (deadlyArea[i].inside(playerCoords[player].x,playerCoords[player].y)) {
                fireEvent(player, "Deadly");
            }
            ofSetColor(ofColor::red);
            deadlyArea[i].draw();
        }
        
        if (!playerCoords.empty()) {
            for (auto player : playerCoords) {
                ofSetColor(255, 255, 255);
                ofDrawCircle(player.x, player.y, 10);
            }
        }
    }
    
    ofPopMatrix();
}
//--------------------------------------------------------------
ofImage MapGenerator::getFinderImage()
{
    return *finderImg;
}
//--------------------------------------------------------------
int MapGenerator::getWidth()
{
    return _width;
}
//--------------------------------------------------------------
int MapGenerator::getHeight()
{
    return _height;
}
//--------------------------------------------------------------
int MapGenerator::getTileSize()
{
    return _tileSize;
}
//--------------------------------------------------------------
int MapGenerator::getGrowthLoops()
{
    return _growthLoops;
}
//--------------------------------------------------------------
int MapGenerator::getDangerAreaSize()
{
    return _dangerAreaSize;
}
//--------------------------------------------------------------
int MapGenerator::getNumberOfClouds()
{
    return _numberOfClouds;
}
//--------------------------------------------------------------
int MapGenerator::getSmoothingLoops()
{
    return _smoothingLoops;
}
//--------------------------------------------------------------
float MapGenerator::getRandomSeedValue()
{
    return _RseedValue;
}
Mat MapGenerator::getSmoothMap()
{
    return _distanceImage;
}
#pragma mark - Setters
//--------------------------------------------------------------
// *
// *    Setters
// *
//--------------------------------------------------------------
void MapGenerator::setWidth(int width)
{
    _width = width;
}
//--------------------------------------------------------------
void MapGenerator::setHeight(int height)
{
    _height = height;
}
//--------------------------------------------------------------
void MapGenerator::setTileSize(int tileSize)
{
    _tileSize = tileSize;
}
//--------------------------------------------------------------
void MapGenerator::setDangerAreaSize(int size)
{
    _dangerAreaSize = size;
}
//--------------------------------------------------------------
void MapGenerator::setGrowthLoops(int growthLoops)
{
    _growthLoops = growthLoops;
}
//--------------------------------------------------------------
void MapGenerator::setRandomSeedValue(float randomSeed)
{
    _RseedValue = randomSeed;
}
//--------------------------------------------------------------
void MapGenerator::setNumberOfClouds(int numberOfClouds)
{
    _numberOfClouds = numberOfClouds;
}
//--------------------------------------------------------------
void MapGenerator::setSmoothingLoops(int smoothingLoops)
{
    _smoothingLoops = smoothingLoops;
}
#pragma mark - Drawing
//--------------------------------------------------------------

// *    Drawing Functions
// *
//--------------------------------------------------------------
void MapGenerator::draw(bool showGrid)
{
    for (int x = 0; x < _width; x ++) {
        for (int y = 0; y < _height; y ++) {
            map[x][y].showGrid = showGrid;
            map[x][y].draw();
        }
    }
    ofSetColor(ofColor::white);
    drawMat(_distanceImage, 0, 0,200,200);
    
    if (isAnimating()) {
        ofPushStyle();
        ofSetColor(0, 0, 0);
        ofSetLineWidth(3);
        ofDrawLine(0, aY*_tileSize, 500, aY*_tileSize);
        ofPopStyle();
    }
}
//--------------------------------------------------------------
void MapGenerator::drawMicroMap()
{
    if (!_mapTexture.empty()) {
        drawMat(_mapTexture, 0, 100,100,100);
    }
}
//--------------------------------------------------------------
void MapGenerator::drawFinderMap(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(1.5, 1.5);
    if (getFinderImage().isAllocated()) {
        ofSetColor(255, 255, 255);
        getFinderImage().draw(0,0);
        microImg->draw(0,100);
    }
//    drawMicroMap();
    ofPopMatrix();
    ofPushMatrix();
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
    
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].draw();
    }
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(0, 0, _width*_tileSize, _height*_tileSize);
    ofPopStyle();
    ofSetColor(255, 255, 255);
    ofDrawLine(ofGetMouseX(), ofGetMouseY()-10, ofGetMouseX(), ofGetMouseY()+10);
    ofDrawLine(ofGetMouseX()-10, ofGetMouseY(), ofGetMouseX()+10, ofGetMouseY());
    
    if (ofGetMouseX() < _width*_tileSize && ofGetMouseY() < _height*_tileSize) {
        ofPushStyle();
        ofNoFill();
        ofSetColor(0, 0, 0);
        ofSetLineWidth(2);
        ofDrawRectangle(ofGetMouseX()-((_tileSize*3)/2), ofGetMouseY()-((_tileSize*3)/2), (_tileSize*3), (_tileSize*3));
        ofPopStyle();
    }
    
}
//--------------------------------------------------------------
void MapGenerator::drawComputerVision(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    
    float scaleValue = 0.25;
    
    if (!_redOnly.empty()) {
        ofPushMatrix();
        ofScale(scaleValue,scaleValue);
        ofSetColor(ofColor::white);
        drawMat(_redOnly,0,0,500,500);
        ofSetColor(ofColor::red);
        deadColorFinder.draw();
        ofPopMatrix();
    }
    if (!_yellowOnly.empty()){
        ofPushMatrix();
        ofTranslate(125,0);
        ofScale(scaleValue,scaleValue);
        ofSetColor(ofColor::white);
        drawMat(_yellowOnly,0,0,500,500);
        ofSetColor(ofColor::yellow);
        dangerColorFinder.draw();
        ofPopMatrix();
    }
    if (!_greenOnly.empty()){
        ofPushMatrix();
        ofTranslate(250,0);
        ofScale(scaleValue,scaleValue);
        ofSetColor(ofColor::white);
        drawMat(_greenOnly,0,0,500,500);
        ofSetColor(ofColor::green);
        okColorFinder.draw();
        ofPopMatrix();
    }    
    ofPopMatrix();
}
//--------------------------------------------------------------
void MapGenerator::drawPolylines()
{
    ofPushMatrix();
    ofTranslate(_newWidth/2, _newHeight);
    ofScale(0.5,0.5);
    ofFill();
    
    for (int i = 0; i < okArea.size(); i++) {
        okArea[i].simplify(0.8);
        ofSetColor(ofColor::green);
        okArea[i].draw();
    }
    
    for (int i = 0; i < dangerArea.size(); i++) {
        dangerArea[i].simplify(0.8);
        ofSetColor(ofColor::yellow);
        dangerArea[i].draw();
    }
    
    for (int i = 0; i < deadlyArea.size(); i++) {
        
        deadlyArea[i].simplify(0.8);
        ofSetColor(ofColor::red);
        deadlyArea[i].draw();
    }
    
    for (int i = 0; i < finishArea.size(); i++) {
        finishArea[i].simplify(0.1);
        ofSetColor(ofColor::white);
        finishArea[i].draw();
    }
    
    ofPopMatrix();
}
#pragma mark - Fire Events
//--------------------------------------------------------------
// *
// *    Fire Events
// *
//--------------------------------------------------------------
void MapGenerator::fireEvent(int playerId, string area)
{
    ofMessage msg(ofToString(playerId)+": "+area);
    ofSendMessage(msg);
}
#pragma mark - Mouse Events
//--------------------------------------------------------------
// *
// *    Mouse Functions
// *
//--------------------------------------------------------------
void MapGenerator::mouseDown(int x, int y, int pressed)
{
    if (x > _width*_tileSize || y > _height*_tileSize) {
        for (int i = 0; i < buttons.size(); i++) {
            if (buttons[i].isActive) {
                buttons[i].isActive = false;
            }
            buttons[i].buttonPressed(x, y, pressed);
        }
        
        for (int i = 0; i < buttons.size(); i++) {
            if (buttons[i].isActive) {
                whichButton = i;
            }
        }
    }
    if (pressed == OF_MOUSE_BUTTON_LEFT) {
        for (int x1 = 0; x1 < _width; x1++) {
            for (int y1 = 0; y1 < _height; y1++) {
                if (map[x1][y1].inside(x, y)){
                    int counter = 0;
                    for (int iY = -1; iY <= 1; iY++) {
                        for (int iX = -1; iX <= 1; iX++) {
                            if (buttons[whichButton].getConfig()[counter] == 1) {
                                map[x1+iX][y1+iY].walkable = false;
                                map[x1+iX][y1+iY].toxicity = 0;
                            }
                            else {
                                map[x1+iX][y1+iY].walkable = true;
                                map[x1+iX][y1+iY].toxicity = 0;
                            }
                            counter++;
                        }
                    }
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
                    int counter = 0;
                    for (int iY = -1; iY <= 1; iY++) {
                        for (int iX = -1; iX <= 1; iX++) {
                            if (buttons[whichButton].getConfig()[counter] == 1) {
                                map[x1+iX][y1+iY].walkable = false;
                                map[x1+iX][y1+iY].toxicity = 0;
                            }
                            else {
                                map[x1+iX][y1+iY].walkable = true;
                                map[x1+iX][y1+iY].toxicity = 0;
                            }
                            counter++;
                        }
                    }
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
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].mouseOver(x, y);
    }
    
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
#pragma mark - Save and Load
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
                mObj.tileSize = mapConfig["Maps"]["Difficulty"][difficultyLevel[diff]][levels]["tilesize"].asInt();
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
void MapGenerator::saveMap(Map m)
{
    ofxJSONElement mapConfig;
    ofxJSONElement mapConfig1;
    
    if(!mapConfig.open("config.json")) {
        cout << "File not Loaded" << endl;
        return;
    }
    else {
        int getMapNos = mapConfig["Maps"]["Difficulty"][m.difficulty].size();
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["difficulty"] = m.difficulty;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["level"] = getMapNos+1;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["tilesize"] = m.tileSize;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["numberofclouds"] = m.numberOfClouds;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["growthloops"] = m.growthLoops;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["smoothingloops"] = m.smoothingValue;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["width"] = m.width;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["height"] = m.height;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["offsetedge"] = m.offsetEdge;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["timetocomplete"] = m.timeNeededToSolveMap;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["randomseed"] = m.seedValue;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["dangerareasize"] = m.dangerAreaSize;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["dangerAreaToxicity"] = m.dangerAreaToxicity;
        mapConfig["Maps"]["Difficulty"][m.difficulty][getMapNos]["deadAreaToxicity"] = m.deadAreaToxicity;
        mapConfig.save("config.json",true);
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