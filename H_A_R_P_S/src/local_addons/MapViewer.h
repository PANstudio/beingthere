//
//  MapViewer.h
//  H_A_R_P_S
//
//  Created by David Haylock on 13/04/2016.
//
//

#ifndef MapViewer_h
#define MapViewer_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "ofxJSON.h"
#include "MapHelpers.h"

class MyImage : public ofImage {
    public:
        void setTag(string tag){
            _tag = tag;
        }
        string getTag(){
            return _tag;
        }
    
        void setDifficulty(string d) {
            _diff = d;
        }
        string getDifficulty() {
            return _diff;
        }
    
    private:
        string _tag;
        string _diff;
};

class MapViewer : public ofBaseApp {
    public:
        void setup();
        void update();
        void draw();
        void close();
        void scroll(float y);
//        bool myFunction(MyImage &a,MyImage &b);
    
    protected:
        ofxThreadedImageLoader mapLoader;
        vector<ofPoint> mapPositions;
//        vector<vector<ofImage> > maps;
        vector<MyImage> maps;
        int noMaps;
        int screenWidth;
        int mapHeight;
        int screenDivision;
        int yPosition;
    private:
        vector<Map> mapInfo;
};


#endif /* MapViewer_h */
