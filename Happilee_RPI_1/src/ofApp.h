#pragma once

#include "ofMain.h"
#include "ofxTween.h"
#include "EmotionHandler.h"
#include "CommandReceiver.h"
#include "MyTimer.h"
#include "HappileeConfiguration.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
    
        MyTimer emotionTimer;
    
        void setupListeners();
        void removeListeners();
        void timerStarted(string &val);
        void timerEnded(string &val);
    
        void happileeSuccessfullyRebooted(string &val);
    
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
        HappileeConfiguration hapConfig;
    
        void drawDebugInfo();
        int selectEmotion;
    
    
        void shuffleEmotions();
        vector <int> randomisedEmotions;
        vector <int> randomisedEmotions0;
        void fisherYatesShuffle(vector<int> &randomised);
};
