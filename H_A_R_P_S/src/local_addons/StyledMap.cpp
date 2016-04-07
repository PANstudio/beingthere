//
//  StyledMap.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 19/12/2015.
//
//

#include "StyledMap.h"
//--------------------------------------------------------------
void StyledMap::setup()
{
    for(map<string,ofxColorMap::ColorMap>::const_iterator it = colorMap.namedMaps.begin();
        it != colorMap.namedMaps.end(); it++) {
        const string& name = it->first;
        cout << name << endl;
        gradientsNames.push_back(name);
    }
    gradientImage.allocate(250, 25, OF_IMAGE_GRAYSCALE);
    colorGradientImage.allocate(250, 25, OF_IMAGE_COLOR);
    unsigned char *p = gradientImage.getPixels();
    for (int x = 0; x < gradientImage.getWidth(); x++) {
        for (int y = 0; y < gradientImage.getHeight(); y++) {
            int value = 255*(float)x/gradientImage.getWidth();
            p[(int)(x+y*gradientImage.getWidth())] = value;
        }
    }
    
    gradientImage.update();
    colorMap.setMapFromName("RdYlGn_r");
    colorMap.apply(gradientImage, colorGradientImage);
}
//--------------------------------------------------------------
void StyledMap::update()
{
    
}
//--------------------------------------------------------------
void StyledMap::draw(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(255, 255, 255);
    colorMapImage.draw(0, 0);
    ofPopMatrix();
}
//--------------------------------------------------------------
void StyledMap::draw(int x, int y,float scaleX,float scaleY)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(255, 255, 255);
    colorMapImage.draw(0, 0,scaleX,scaleY);
    ofPopMatrix();
}
//--------------------------------------------------------------
void StyledMap::drawGradients(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(255, 255, 255);
    gradientImage.draw(0, 0);
    colorGradientImage.draw(0, gradientImage.getHeight());
    ofPopMatrix();
}
//--------------------------------------------------------------
ofImage StyledMap::getStyledMap()
{
    return colorMapImage;
}
//--------------------------------------------------------------
void StyledMap::getMapImage(cv::Mat _map)
{
    mapImage.clear();
    colorMapImage.clear();
    mapImage.allocate(_map.cols, _map.rows, OF_IMAGE_GRAYSCALE);
    colorMapImage.allocate(_map.cols, _map.rows, OF_IMAGE_COLOR);
    for (int y = 0; y < mapImage.getHeight(); y++) {
        for (int x = 0; x < mapImage.getWidth(); x++) {
            mapImage.setColor(x, y, _map.at<uchar>(y,x));
        }
    }
    colorMap.apply(mapImage,colorMapImage);
    colorMapImage.resize(500, 500);
}
//--------------------------------------------------------------
void StyledMap::setGradient(string gradient)
{
    colorMap.setMapFromName(gradient);
    colorMap.apply(gradientImage, colorGradientImage);
    colorMapImage.resize(mapImage.getWidth(), mapImage.getHeight());
    colorMap.apply(mapImage,colorMapImage);
    colorMapImage.resize(500, 500);
}
//--------------------------------------------------------------
vector<string> StyledMap::getGradientsNames()
{
    return gradientsNames;
}