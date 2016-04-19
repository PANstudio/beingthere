//
//  MapMesh.h
//  H_A_R_P_S
//
//  Created by David Haylock on 17/04/2016.
//
//

#ifndef MapMesh_h
#define MapMesh_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
class MapMesh {
    public:
        void setup();
        void reset();
        void clear();
        void draw();
        void update();
        void getMapImage(cv::Mat map,ofImage styledImage);
    
    protected:
        ofEasyCam cam; // add mouse controls for camera movement
        float extrusionAmount;
        ofVboMesh mainMesh;
    private:
    
};
#endif /* MapMesh_h */
