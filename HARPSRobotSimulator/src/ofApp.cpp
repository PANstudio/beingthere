#include "ofApp.h"

//-----------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    health = 0;
    setupListeners();
    
    receiveCommand.setup(7890);
    receiveCommand.startListening();
    
    myFbo.allocate(512, 512);
    myGlitch.setup(&myFbo);
}
//-----------------------------------------------------------------
void ofApp::update()
{
//    receiveCommand.update();
    myFbo.begin();
    ofClear(51, 153, 255,255);
    ofSetColor(ofColor::white);
    ofDrawCircle(512/3, 512/3, 30);
    ofDrawCircle((512/3)*2, 512/3, 30);
    ofDrawCircle(512/2, 512/3*2, 30);
    ofSetColor(ofColor::black);
    ofDrawCircle(512/3, 512/3, 15);
    ofDrawCircle((512/3)*2, 512/3, 15);
    ofDrawCircle(512/2, 512/3*2, 15);
    myFbo.end();
}
//-----------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);
    myGlitch.generateFx();
    ofSetColor(255);
    myFbo.draw(0, 0);
}
//-----------------------------------------------------------------
void ofApp::setupListeners()
{
    ofAddListener(receiveCommand.resetHealth,this,&ofApp::resetHealth);
    ofAddListener(receiveCommand.reduceHealth,this,&ofApp::reduceHealth);
    ofAddListener(receiveCommand.malfunction,this,&ofApp::malfunction);
    ofAddListener(receiveCommand.start,this,&ofApp::start);
    ofAddListener(receiveCommand.instruction,this,&ofApp::instructions);
    ofAddListener(receiveCommand.flashLights,this,&ofApp::flashLights);
    ofAddListener(receiveCommand.inDanger,this,&ofApp::inDanger);
    ofAddListener(receiveCommand.okDanger,this,&ofApp::isOk);
}
//-----------------------------------------------------------------
void ofApp::removeListeners()
{
    ofRemoveListener(receiveCommand.resetHealth,this,&ofApp::resetHealth);
    ofRemoveListener(receiveCommand.reduceHealth,this,&ofApp::reduceHealth);
    ofRemoveListener(receiveCommand.malfunction,this,&ofApp::malfunction);
    ofRemoveListener(receiveCommand.start,this,&ofApp::start);
    ofRemoveListener(receiveCommand.instruction,this,&ofApp::instructions);
    ofRemoveListener(receiveCommand.flashLights,this,&ofApp::flashLights);
    ofRemoveListener(receiveCommand.inDanger,this,&ofApp::inDanger);
    ofRemoveListener(receiveCommand.okDanger,this,&ofApp::isOk);
}
//-----------------------------------------------------------------
void ofApp::exit()
{
    removeListeners();
    receiveCommand.stopListening();
}
//-----------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
    if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
    if (key == '3') {
        myGlitch.setFx(OFXPOSTGLITCH_SHAKER, true);
        myGlitch.setShaker(1.5, 1.5);
    }
    if (key == '4') {
        myGlitch.setFx(OFXPOSTGLITCH_SHAKER, true);
        myGlitch.setShaker(3.5, 3.5);
    }
    if (key == 's') {
        myGlitch.setFx(OFXPOSTGLITCH_SHAKER, false);
//        myGlitch.setShaker(3.5, 3.5);
    }
    if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
    if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
    if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
    if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
    if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
    if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
    
    if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
    if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
    if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
    if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
    if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
    if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
}
//-----------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
    if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
    if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
    if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
    if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
    if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
    if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
    if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
    if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
    if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
    
    if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
    if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
    if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
    if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
    if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
    if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
}
//-----------------------------------------------------------------
void ofApp::resetHealth(string &str)
{
    
}
//-----------------------------------------------------------------
void ofApp::reduceHealth(string &str)
{
    
}
//-----------------------------------------------------------------
void ofApp::malfunction(string &str)
{
    
}
//-----------------------------------------------------------------
void ofApp::start(string &str)
{
    
}
//-----------------------------------------------------------------
void ofApp::instructions(string &str)
{
    
}
//-----------------------------------------------------------------
void ofApp::flashLights(string &str)
{
    
}
//-----------------------------------------------------------------
void ofApp::inDanger(string &str)
{
    myGlitch.setFx(OFXPOSTGLITCH_SHAKER, true);
}
//-----------------------------------------------------------------
void ofApp::isOk(string &str)
{
    myGlitch.setFx(OFXPOSTGLITCH_SHAKER, false);
}