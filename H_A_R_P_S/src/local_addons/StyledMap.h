//
//  StyledMap.h
//  H_A_R_P_S
//
//  Created by David Haylock on 19/12/2015.
//
//

#ifndef StyledMap_h
#define StyledMap_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxColorMap.h"
#include "ofxCv.h"

class StyledMap {
    public:
    
        //! Setup
        void setup();

        //! Update
        void update();

        //! Draw the map
        void draw(int x, int y);
        void draw(int x, int y,float scaleX,float scaleY);

        //! Draw the Gradients
        void drawGradients(int x,int y);
    
        //! Get the Map Image
        void getMapImage(cv::Mat _map);
    
        //! Set the Gradient Type
        void setGradient(string gradient);

        //! Get Styled Map
        ofImage getStyledMap();
    
        //! Get the gradients
        vector<string> getGradientsNames();

    private:
        vector<string> gradientsNames;
        ofImage mapImage;
        ofImage colorMapImage;
        ofImage gradientImage;
        ofImage colorGradientImage;
        ofxColorMap colorMap;
};
#endif /* StyledMap_h */
