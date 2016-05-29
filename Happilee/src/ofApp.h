#pragma once

#include "ofMain.h"
#include "ofxTween.h"
#include "EmotionHandler.h"
#include "CommandReceiver.h"
#include "MyTimer.h"



class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        MyTimer emotionTimer;
    
        void setupListeners();
        void removeListeners();
        void timerStarted(string &val);
        void timerEnded(string &val);
        void haveDied(string &val);
        void haveWon(string &val);
    
        void resetMemory(string &val);
        void inGreenZone(string &val);
        void inYellowZone(string &val);
        void inRedZone(string &val);
        void inSafeZone(string &val);
        void rebootHappilee(string &val);
        void malfunctionHappilee(string &val);
    
        int hpState;
    
        CommandReceiver receiver;
        EmotionHandler emotionProcessor;
        void drawFaceElement();
        void drawIndicators();
        int selectEmotion;
    
    
        void shuffleEmotions();
        vector <int> randomisedEmotions;
        vector <int> randomisedEmotions0;
        void fisherYatesShuffle(vector<int> &randomised);
};
