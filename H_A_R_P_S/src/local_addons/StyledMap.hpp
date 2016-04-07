//
//  StyledMap.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 19/12/2015.
//
//

#ifndef StyledMap_hpp
#define StyledMap_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxColorMap.h"
#include "ofxCv.h"

class StyledMap {
    public:
    void setup();
    void update();

    void draw(int x, int y);
    void draw(int x, int y,float scaleX,float scaleY);
    void drawGradients(int x,int y);
    void getMapImage(cv::Mat _map);
    void setGradient(string gradient);
    ofImage getStyledMap();
    vector<string> getGradientsNames();
    vector<string> gradientsNames;
    
    ofImage mapImage;
    ofImage colorMapImage;
    ofImage gradientImage;
    ofImage colorGradientImage;
    ofxColorMap colorMap;
};
#endif /* StyledMap_hpp */
