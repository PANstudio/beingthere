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
    void getMapImage(cv::Mat _map);
    void setGradient(string gradient);
    
    vector<string> getGradientsNames();
    vector<string> gradientsNames;
    
    ofImage mapImage;
    ofImage colorMapImage;
    ofImage gradientImage;
    ofImage colorGradientImage;
    ofxColorMap colorMap;
};

//struct textLine {
//    
//    textLine(int rotation,int x,int y,string text){
//        _rotation = rotation;
//        _x = x;
//        _y = y;
//        _text = text;
//    }
//    
//    int _rotation;
//    int _x;
//    int _y;
//    int _offsetPositionX;
//    int _offsetPositionY;
//    string _text;
//};
//
//class StyledMap {
//    public:
//        void setup(int width,int height);
//        void update();
//        void setShapes(vector <ofPolyline> deadly,vector <ofPolyline> danger);
//        void drawStyledMap(int x,int y);
//    private:
//        vector<ofPolyline> deadlyShapes;
//        vector<ofPolyline> dangerShapes;
//    
//        vector <textLine> text;
//        ofTrueTypeFont fontSmall;
//        ofFbo test;
//        ofFbo test1;
//        ofFbo dangerMask;
//        ofFbo deadlyMask;
//        
//        ofFbo masks;
//        ofShader maskDeadlyShader;
//        ofShader maskDangerShader;
//        ofxBlurShader blur;
//        ofxBlurShader blur1;
//    protected:
//    
//};

#endif /* StyledMap_hpp */
