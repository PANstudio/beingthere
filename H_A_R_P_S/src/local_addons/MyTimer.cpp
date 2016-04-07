//--------------------------------------------------------------
//
//  MyTimer.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#include "MyTimer.h"
//--------------------------------------------------------------
void MyTimer::setup(float timerLength,string timerName,bool loop)
{
    bTimerReached = true;
    _loop = loop;
    _timerLength = timerLength;
    _timerName = timerName;
}
//--------------------------------------------------------------
void MyTimer::update()
{
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    if (!bTimerReached) {
        timeLeft = _timerLength - timer;
    }
    
    if (timer >= _timerLength && !bTimerReached) {
        bTimerReached = true;
        string ev = _timerName + " Finished";
        ofNotifyEvent(timerFinished, ev, this);
        if (_loop) {
            start();
        }
    }
}
//--------------------------------------------------------------
string MyTimer::getTimeLeftStr()
{
    stringstream time;
    float timeString;
    if (bTimerReached) {
        timeString = (_timerLength/1000)/60;
    }
    else {
        timeString = (timeLeft/1000)/60;
    }
    
    string mins = ( timeString < 1 ? "00" : "01" );
    double seconds;
    double mseconds;
    string secs = "";
    float a = modf(timeString, &seconds);
    if (a*60 < 10) {
        secs = "0"+ofToString((int)(a*60));
    }
    else {
        secs = ofToString((int)(a*60));
    }
    time << mins << secs;
    return time.str();
}
//--------------------------------------------------------------
float MyTimer::getTimeLeft()
{
    return timeLeft;
}
//--------------------------------------------------------------
bool MyTimer::hasTimerFinished()
{
    return bTimerReached;
}
//--------------------------------------------------------------
void MyTimer::setNewTimerLength(int timerLength)
{
    _timerLength = timerLength;
}
//--------------------------------------------------------------
void MyTimer::start()
{
    if (bTimerReached) {
        string ev = _timerName + " Started";
        ofNotifyEvent(timerStarted, ev, this);
        bTimerReached = false;
        startTime = ofGetElapsedTimeMillis();
    }
}
//--------------------------------------------------------------
void MyTimer::stop( )
{
    bTimerReached = true;
    _loop = false;
}