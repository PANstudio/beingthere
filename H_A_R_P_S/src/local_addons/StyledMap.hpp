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
#include "ofxBlurShader.h"
#include "ofMain.h"

class StyledMap {
    public:
        void setup(int width,int height);
        void update();
        void setShapes(vector <ofPolyline> deadly,vector <ofPolyline> danger);
        void drawStyledMap(int x,int y);
    private:
        vector<ofPolyline> deadlyShapes;
        vector<ofPolyline> dangerShapes;
    
        ofFbo test;
        ofFbo test1;
        ofFbo dangerMask;
        ofFbo deadlyMask;
        
        ofFbo masks;
        ofShader maskDeadlyShader;
        ofShader maskDangerShader;
        ofxBlurShader blur;
        ofxBlurShader blur1;
    protected:
    
};

#endif /* StyledMap_hpp */
