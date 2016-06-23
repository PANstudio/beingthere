//
//  HappileeScenes.h
//  Happilee
//
//  Created by David Haylock on 19/06/2016.
//
//

#ifndef HappileeScenes_h
#define HappileeScenes_h

#include <stdio.h>
#include "ofMain.h"

class HappileeRebooting {
    
    void setup() {
        
    }
    
    void update() {
        
    }
    
    void draw() {
        
    }
    
};

class HappileeMalfunctioned {
public:
    void setup(ofTrueTypeFont &font) {
        malfunctionText = font;
    }
    
    void update() {
        
    }
    
    void draw() {
        ofPushStyle();
        ofFill();
        ofSetColor(0, 50, 255);
        ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
        string a = "Happilee";
        ofRectangle centerTitle = malfunctionText.getStringBoundingBox(a, 0, ofGetHeight()/2-100);
        ofSetColor(160);
        ofDrawRectangle(ofGetWidth()/2-(centerTitle.width/2)-10,centerTitle.y-centerTitle.height-5,centerTitle.width+20,centerTitle.height+10);
        ofSetColor(0, 50, 255);
        malfunctionText.drawString(a,ofGetWidth()/2-(centerTitle.width/2),centerTitle.y);
        
        ofSetColor(255, 255, 255);
        stringstream st;
        st << "Happilee ERROR: " << 100 << endl;
        st << endl;
        st << "Unfortunatly this Happilee Unit has overloaded his sentiment drive." << endl;
        st << "Please return to a safe area to download the Sentiment Data" << endl;
        ofRectangle leftTitle = malfunctionText.getStringBoundingBox(st.str(), 0, ofGetHeight()/2-50);
        malfunctionText.drawString(st.str(),25, leftTitle.y);
        
        string ab = "Return to Last Safe Area ...";
        ofRectangle bottomTitle = malfunctionText.getStringBoundingBox(ab, 0, ofGetHeight()/2+100);
        malfunctionText.drawString(ab,ofGetWidth()/2-(bottomTitle.width/2),bottomTitle.y);
        
        ofPopStyle();
        ofPopMatrix();
        ofPopStyle();
    }
    
    ofTrueTypeFont malfunctionText;
};

class HappileeInformation {
    void setup() {
        
    }
    
    void update() {
        
    }
    
    void draw() {
        
    }
    stringstream information;
};

#endif /* HappileeScenes_h */
