#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ReceiveCommands.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
    
        int health;
        ofFbo			myFbo;
        ofxPostGlitch	myGlitch;
        ReceiveCommands receiveCommand;
    
        void setupListeners();
        void removeListeners();
    
        void resetHealth(string &str);
        void reduceHealth(string &str);
        void malfunction(string &str);
        void start(string &str);
        void instructions(string &str);
        void flashLights(string &str);
        void inDanger(string &str);
        void isOk(string &str);
};
