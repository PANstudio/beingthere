//
//  SimpleButton.h
//
//  Created by David Haylock on 15/12/2015.
//
//

#pragma once
#ifndef SimpleButton_h
#define SimpleButton_h

#include "ofMain.h"
//---------------------------------------------------
class SimpleButton : public ofRectangle {
public:
    SimpleButton() {}
    //---------------------------------------------------
    SimpleButton(int x,int y,int w, int h,int config,string name,ofColor c)
    {
        _config = config;
        this->set(x,y,w,h);
        standardColor = c;
        buttonName = name;
        isActive = false;
        isOver = false;
        
        for(int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                ofRectangle r;
                r.setFromCenter(this->getCenter().x+(x*10),this->getCenter().y+(y*10),8,8);
                rects.push_back(r);
            }
        }
        
    }
    //---------------------------------------------------
    ~SimpleButton() {}
    //---------------------------------------------------
    void setupButton(int x,int y,int w, int h,int config,string name,ofColor c)
    {
        _config = config;
        this->set(x,y,w,h);
        standardColor = c;
        buttonName = name;
        isActive = false;
        isOver = false;
        
        for(int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                ofRectangle r;
                r.setFromCenter(this->getCenter().x+(x*10),this->getCenter().y+(y*10),8,8);
                rects.push_back(r);
            }
        }
    }
    //---------------------------------------------------
    void draw()
    {
        ofPushStyle();
        if (isOver) {
            ofSetColor(ofColor::orange);
        }
        else if(isActive) {
            ofSetColor(ofColor::seaGreen);
        }
        else {
            ofSetColor(standardColor);
        }
        
        ofDrawRectangle(this->getStandardized());
        ofPopStyle();
        
        ofPushStyle();
        
        for(int e = 0; e < rects.size(); e++) {
            if (_config == 0) {
                if(config_1[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_1[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 1) {
                if(config_2[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_2[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 2) {
                if(config_3[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_3[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 3) {
                if(config_4[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_4[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 4) {
                if(config_5[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_5[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 5) {
                if(config_6[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_6[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 6) {
                if(config_7[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_7[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 7) {
                if(config_8[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_8[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 8) {
                if(config_9[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_9[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 9) {
                if(config_10[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_10[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 10) {
                if(config_11[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_11[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 11) {
                if(config_12[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_12[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 12) {
                if(config_13[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_13[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 13) {
                if(config_14[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_14[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            else if (_config == 14) {
                if(config_15[e] == 1) {
                    ofSetColor(ofColor::red);
                }
                else if(config_15[e] == 0) {
                    ofSetColor(ofColor::green);
                }
            }
            ofDrawRectangle(rects[e]);
        }
        ofPopStyle();
    }
    
    //---------------------------------------------------
    void mouseOver(int x,int y)
    {
        if (inside(x,y)) {
            isOver = true;
        }
        else {
            isOver = false;
        }
    }
    //---------------------------------------------------
    void buttonPressed(int x,int y,int button)
    {
        if (inside(x,y)) {
            isActive = !isActive;
        }
    }
    
    bool isActive = false;
    bool isOver = false;
private:

    ofColor standardColor;
    string buttonName;

    deque <ofRectangle> rects;
    
    int _config;
    
    int config_1[9] = {0,0,0,
                       0,0,0,
                       0,0,0}; // Config All Off
    
    int config_2[9] = {1,1,1,
                       1,1,1,
                       1,1,1}; // Config All On
    
    int config_3[9] = {1,1,0,
                       1,0,0,
                       0,0,0}; // Config Top Left
    
    int config_4[9] = {0,1,1,
                       0,0,1,
                       0,0,0}; // Config Top Right
    
    int config_5[9] = {0,0,0,
                       0,0,1,
                       0,1,1}; // Config Bottom Right
    
    int config_6[9] = {0,0,0,
                       1,0,0,
                       1,1,0}; // Config Bottom Left
    
    int config_7[9] = {1,1,0,
                       1,1,0,
                       0,0,0}; // Config Top Left 4
    
    int config_8[9] = {0,1,1,
                       0,1,1,
                       0,0,0}; // Config Top Right 4
    
    int config_9[9] = {0,0,0,
                       0,1,1,
                       0,1,1}; // Config Bottom Right 4
    
    int config_10[9] = {0,0,0,
                        1,1,0,
                        1,1,0}; // Config Bottom Left 4
    
    int config_11[9] = {1,0,0,
                        1,0,0,
                        1,0,0}; // Config Left Line
    
    int config_12[9] = {0,1,0,
                        0,1,0,
                        0,1,0}; // Config Middle Line
    
    int config_13[9] = {0,0,1,
                        0,0,1,
                        0,0,1}; // Config Right Line
    
    int config_14[9] = {0,0,1,
                        0,1,0,
                        1,0,0}; // Config Right Line
    
    int config_15[9] = {1,0,0,
                        0,1,0,
                        0,0,1}; // Config Right Line
};
#endif /* SimpleButton_h */
