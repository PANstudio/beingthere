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


class MapViewer : public ofBaseApp {
    public:
        void setup();
        void update();
        void draw();
        void close();
    
    protected:
        ofxThreadedImageLoader mapLoader;
        vector<ofPoint> mapPositions;
        vector<ofImage> maps;
        int noMaps;
    private:
    
};


#endif /* MapViewer_h */
