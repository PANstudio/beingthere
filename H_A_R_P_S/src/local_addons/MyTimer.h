//--------------------------------------------------------------
//
//  MyTimer.h
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#ifndef MyTimer_h
#define MyTimer_h

#include <stdio.h>
#include "ofMain.h"

class MyTimer {
    public:
    
        void setup(float timerLength,string timerName,bool loop,string fontFile);
        void update();
        void draw(int x, int y);
        
        void start();
        void stop();
        void reset();
        void setNewTimerLength(int timerLength);
        string getTimeLeft();
        int getSecondsLeft();
    
    private:
        float startTime;
        float endTime;
        float timeLeft;
        bool  bTimerReached;
        bool _loop;
        float _timerLength;
        string _timeLeftString;
        string _timerName;
        ofTrueTypeFont font;
        ofEvent<string> TimerFinished;
        ofEvent<string> TimerStarted;
};
#endif /* MyTimer_h */