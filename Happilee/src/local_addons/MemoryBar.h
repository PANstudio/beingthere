//
//  MemoryBar.h
//  Happilee
//
//  Created by David Haylock on 27/05/2016.
//
//

#ifndef MemoryBar_h
#define MemoryBar_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxTween.h"


class MemoryBar {
    public:
        void setup(float initialMemory);
        void update();
        void draw(int x,int y);
    
        float getMemoryRemaining();
        void resetMemory(float initialMemory);
        void reduceMemory(float amount);
        void tweenFinished(int &val);
        bool hasRebooted();
        bool getIsDead();
        ofEvent<string> isDead;
        ofEvent<string> isRebooted;
    private:
        float memoryRemaining;
        int previousMemory;
        bool hasDied;
        bool _hasRebooted;
        ofxTween reducer;
        ofxEasingExpo expo;
        ofxEasingCirc circ;
};

#endif /* MemoryBar_h */
