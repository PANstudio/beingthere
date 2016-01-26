//--------------------------------------------------------------
//
//  MyTimer.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//--------------------------------------------------------------

#include "MyTimer.hpp"
////--------------------------------------------------------------
//MyTimer::MyTimer(float timerLength,string timerName,bool loop,string fontFile)
//{
//    bTimerReached = true;
//    _loop = loop;
//    _timerLength = timerLength;
//    _timerName = timerName;
//    font.load(fontFile, 40);
//}
////--------------------------------------------------------------
//MyTimer::~MyTimer()
//{
//    
//}
//--------------------------------------------------------------
void MyTimer::setup(float timerLength,string timerName,bool loop,string fontFile)
{
    bTimerReached = true;
    _loop = loop;
    _timerLength = timerLength;
    _timerName = timerName;
    if (fontFile.size() < 1) {
        
    }
    else {
        font.load(fontFile, 40);
    }
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
        ofMessage msg(_timerName + " Finished");
        ofSendMessage(msg);
        if (_loop) {
            start();
        }
    }
}
//--------------------------------------------------------------
string MyTimer::getTimeLeft()
{
    stringstream time;
    float timeString;
    //    double fractpart;
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
void MyTimer::draw(int x, int y)
{
    ofSetColor(255, 255, 255);
    ofRectangle r = font.getStringBoundingBox(getTimeLeft(), x,y);
    if (font.isLoaded()) {
        font.drawString(getTimeLeft(), r.getCenter().x,r.getCenter().y);
    }
    else {
        
    }
}
//--------------------------------------------------------------
int MyTimer::getSecondsLeft()
{
    return timeLeft;
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
        ofMessage msg(_timerName + " Started");
        ofSendMessage(msg);
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