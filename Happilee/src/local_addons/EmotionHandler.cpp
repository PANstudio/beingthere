//
//  EmotionHandler.cpp
//  Happilee
//
//  Created by David Haylock on 26/05/2016.
//
//

#include "EmotionHandler.h"

#pragma mark - Setup

//--------------------------------------------------------------
void EmotionHandler::setup(int initialMemory,int _lowMemoryAmount,int _malfunctionTimerLength)
{
    ofSetVerticalSync(true);
    lastEmotionPosition = 0;
    newEmotionPosition = 0;
    lastImagePosition = 0;
    newImagePosition = 0;
    whichEmotion = 0;
    neutralEmotionID = 0;
    malfunctionEmotionID = 0;
    
    malfunctionTimerLength = _malfunctionTimerLength;
    
    _lowMemoryAmount = _lowMemoryAmount;
    _HappileeMemory = initialMemory;
    
    hpState = HAPPILEE_GREEN;
    changeStringLatch = false;
    moveImageLatch = false;
    malfunctionedLatch = true;
    winningLatch = true;
    
    lowMemory = false;
    dots = ".";
    
    faceTexture.allocate(ofGetWidth(), ofGetHeight());
    
    faceTexture.begin();
    ofClear(0);
    faceTexture.end();
    
    interferance.setup(&faceTexture);
    receivingEmotionImage.load(ofToDataPath("images/components/emotion_pic.png"));
    warningImage.load(ofToDataPath("images/components/warning_pic.png"));
    
    loadImages();
    loadFonts();
    loadSounds();
    
    alphaMask.load("alphaMask/alpha");
    alphaMaskImage.load("alphaMask/alphaMask.png");
    
    ofAddListener(moveImage.end_E, this, &EmotionHandler::didTweenFinish);
    ofAddListener(malfunctioning.end_E, this, &EmotionHandler::didTweenFinish);
    ofAddListener(purgingEmotions.end_E, this, &EmotionHandler::didTweenFinish);
    ofAddListener(memoryProcessor.isRebooted, this, &EmotionHandler::happileeHasRebooted);
    ofAddListener(malfunctioningTimer.timerFinished, this, &EmotionHandler::malfunctioningTimerFinshed);
    
    r1.set((ofGetWidth()*0.5)+(13),(ofGetHeight()-(80+10))+5,(ofGetWidth()*0.5)-(13)-20,80-10);
    
    memoryProcessor.setup(_HappileeMemory);
    hatchTexture.allocate(r1.width,r1.height);
    malfunctioningTimer.setup(_malfunctionTimerLength, "Malfunction Timer", false);
}
//--------------------------------------------------------------
void EmotionHandler::setReductionAmount(int greenLevel, int yellowLevel, int redLevel)
{
    greenReductionAmount = greenLevel;
    yellowReductionAmount = yellowLevel;
    redReductionAmount = redLevel;
}
//--------------------------------------------------------------
void EmotionHandler::cleanUp()
{
    emotionImages.clear();
    ofRemoveListener(moveImage.end_E, this, &EmotionHandler::didTweenFinish);
    
    delete emotionSoundsDistorted;
    delete emotionSoundsClean;
}
//--------------------------------------------------------------
void EmotionHandler::resetMemory()
{
    memoryProcessor.resetMemory(_HappileeMemory);
    malfunctionedLatch = false;
    hpState = HAPPILEE_REBOOTING;
}
#pragma mark - Load Assets
//--------------------------------------------------------------
void EmotionHandler::loadImages()
{
    emotionsDirectory.listDir(ofToDataPath("images/emotions/"));
    emotionsDirectory.allowExt(".png");
    emotionsDirectory.sort();
    
    if ( emotionsDirectory.size() ) {
        emotionImages.assign(emotionsDirectory.size(), ofImage());
        emotionStrings.assign(emotionsDirectory.size(), string());
    }
    
    for (int i = 0; i < emotionsDirectory.size(); i++) {
        emotionImages[i].load(emotionsDirectory.getFile(i).path());
        
        string tmpString = emotionsDirectory.getFile(i).getBaseName();
        
        if (ofIsStringInString(tmpString, "neutral")) {
            neutralEmotionID = i;
        }
        
        if (ofIsStringInString(tmpString, "xx")) {
            malfunctionEmotionID = i;
        }
        
        char first = tmpString.at(0);
        tmpString.at(0) = ofToChar(ofToUpper(&first));
        emotionStrings[i] = tmpString;
    }

}
//--------------------------------------------------------------
void EmotionHandler::loadSounds()
{
    cleanSoundsDirectory.listDir(ofToDataPath("sounds/cleanEmotions/"));
    cleanSoundsDirectory.allowExt(".mp3");
    cleanSoundsDirectory.sort();
    
    emotionSoundsClean = new ofSoundPlayer[cleanSoundsDirectory.size()];
    
    for (int i = 0; i < cleanSoundsDirectory.size(); i++) {
        emotionSoundsClean[i].load(cleanSoundsDirectory.getFile(i).path());
        emotionSoundsClean[i].setLoop(false);
        emotionSoundsClean[i].setMultiPlay(true);
    }
    
    distortedSoundsDirectory.listDir(ofToDataPath("sounds/distortedEmotions/"));
    distortedSoundsDirectory.allowExt(".mp3");
    distortedSoundsDirectory.sort();

    emotionSoundsDistorted = new ofSoundPlayer[distortedSoundsDirectory.size()];
    
    for (int i = 0; i < distortedSoundsDirectory.size(); i++) {
        emotionSoundsDistorted[i].load(distortedSoundsDirectory.getFile(i).path());
        emotionSoundsDistorted[i].setLoop(false);
        emotionSoundsDistorted[i].setMultiPlay(true);
    }
    
    // Load individual assets
    string winPath = ofToDataPath("sounds/win/");
    string corruptionPath = ofToDataPath("sounds/corruption/");
    
    // Can be altered
    welcomeSound.load(winPath+"hello.mp3");
    purgingSound.load(winPath+"purging.mp3");
    goodbyeSound.load(winPath+"goodbye.mp3");
    
    welcomeSound.setLoop(false);
    goodbyeSound.setLoop(false);
    purgingSound.setLoop(true);

    malfunctioningSound.load(corruptionPath+"goodbye_distort_w-ding.mp3");
    malfunctioningDing.load(corruptionPath+"Death_ding.mp3");
    
    malfunctioningDing.setLoop(false);
    malfunctioningSound.setLoop(false);
    
}
//--------------------------------------------------------------
void EmotionHandler::loadFonts()
{
    regularIndicatorFont.load(ofToDataPath("fonts/DIN-REGULAR.OTF"), 20);
    lightIndicatorFont.load(ofToDataPath("fonts/DIN-LIGHT.TTF"), 17);
    darkIndicatorFont.load(ofToDataPath("fonts/DIN-BLACK.TTF"), 19);
    boldIndicatorFont.load(ofToDataPath("fonts/DIN-BOLD.OTF"), 17);
    wordsContainer.allocate(200, darkIndicatorFont.getGlyphBBox().height+darkIndicatorFont.getGlyphBBox().height*0.4);
    
    regularIndicatorFont.setGlobalDpi(40);
    boldIndicatorFont.setGlobalDpi(40);
    darkIndicatorFont.setGlobalDpi(40);
    lightIndicatorFont.setGlobalDpi(40);
    
    hpMalfunctioned.setup(regularIndicatorFont);
    hpRebooting.setup(regularIndicatorFont);
    hpWinning.setup(regularIndicatorFont);
    
    wordsContainer.begin();
    ofClear(0, 0, 0, 0);
    wordsContainer.end();
    
    offsetX = 13;
    offsetY = 10;
    height = 80;
    centerX = (ofGetWidth()*0.5);
    width = (centerX)-(offsetX);
    centerBoxY = (ofGetHeight()-offsetY)-(height/2);
    
    warningImagePos = ofPoint(centerX+(offsetX*2), centerBoxY-warningImage.getHeight()*0.5);
    receivingImagePos = ofPoint(offsetX*2, centerBoxY-receivingEmotionImage.getHeight()*0.5);
}
#pragma mark - Update
//--------------------------------------------------------------
void EmotionHandler::update()
{
    ofSoundUpdate();
    memoryProcessor.update();
    malfunctioningTimer.update();
    
    if (hpState == HAPPILEE_MALFUNCTION) {
        if (ofGetFrameNum() % 2 == 0) {
            bool is = ofRandom(1.0) > 0.25 ? true : false;
            interferance.setFx(OFXPOSTGLITCH_GLOW, is);
//            interferance.setFx(OFXPOSTGLITCH_OUTLINE, is);
        }
    }
    else if(hpState == HAPPILEE_RED)
    {
        if (ofGetFrameNum() % 5 == 0) {
            bool is = ofRandom(1.0) > 0.75 ? true : false;
            interferance.setFx(OFXPOSTGLITCH_SHAKER, is);
        }

    }
    interferance.setSlitAmount((float)(40.0 + 40.0 * sin(ofGetElapsedTimef())));
    
    wordsContainer.begin();
    ofClear(0, 0, 0, 0);
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(0, moveEmotion.update());
    for (int i = 0; i < emotionStrings.size(); i++) {
        ofSetColor(51, 51, 51);
        if (whichEmotion != getNeutralFaceID()) {
            darkIndicatorFont.drawString(emotionStrings[i],0,darkIndicatorFont.getGlyphBBox().height-(i*(darkIndicatorFont.getGlyphBBox().height+10)));
        }
    }
    ofPopMatrix();
    ofPopStyle();
    wordsContainer.end();
}
#pragma mark - Draw
//--------------------------------------------------------------
void EmotionHandler::drawIndicators()
{
    ofPushStyle();
    switch (hpState) {
        case HAPPILEE_WIN:
            ofSetColor(192, 192, 192);
            break;
        case HAPPILEE_PURGING:
            ofSetColor(192, 192, 192);
            break;
        case HAPPILEE_GREEN:
            ofSetColor(0, 181, 208);
            break;
        case HAPPILEE_YELLOW:
            ofSetColor(0, 181, 208);
            break;
        case HAPPILEE_RED:
            ofSetColor(0, 181, 208);
            break;
        case HAPPILEE_MALFUNCTION:
            ofSetColor(0, 181, 208);
            break;
        default:
            break;
    }
    
    ofDrawRectRounded(offsetX,(ofGetHeight()-height)-offsetY, width-(offsetX*0.5), height, 0);
    
    switch (hpState) {
        case HAPPILEE_WIN:
            ofSetColor(162, 215, 83);
            break;
        case HAPPILEE_PURGING:
            ofSetColor(52, 52, 52);
            break;
        case HAPPILEE_GREEN:
            ofSetColor(255, 67, 81);
            break;
        case HAPPILEE_YELLOW:
            ofSetColor(255, 67, 81);
            break;
        case HAPPILEE_RED:
            ofSetColor(255, 67, 81);
            break;
        case HAPPILEE_MALFUNCTION:
            ofSetColor(255, 67, 81);
            break;
        default:
            break;
    }
    
    ofDrawRectRounded((ofGetWidth()-width)-offsetX+(offsetX*0.5),(ofGetHeight()-height)-offsetY, width-(offsetX*0.5),height,0);
    ofPopStyle();
}
//--------------------------------------------------------------
void EmotionHandler::drawImages()
{
    faceTexture.begin();
    
    ofClear(0, 0, 0, 0);
    drawIndicators();
    
    ofPushStyle();
    ofSetColor(255, 216, 21);
    ofSetCircleResolution(200);
    ofDrawCircle(faceTexture.getWidth()*0.5, faceTexture.getHeight()*0.4, 160);
    ofPopStyle();
    
    ofPushStyle();
    int x = (faceTexture.getWidth()*0.5-(emotionImages[0].getWidth()*0.5));
    int y = ((faceTexture.getHeight()*0.4)-(emotionImages[0].getHeight()*0.5));
    ofSetColor(ofColor::white);
    ofFill();
    emotionImages[whichEmotion].draw(x,y, emotionImages[0].getWidth(), emotionImages[0].getHeight());
    ofPopStyle();
    
    drawEmotions();
    
    faceTexture.end();
    interferance.generateFx();
    
    int centerX = (ofGetWidth()*0.5)-(faceTexture.getWidth()*0.5);
    int centerY = (ofGetHeight()*0.40)-(faceTexture.getHeight()*0.5);
    
    ofSetColor(255, 255, 255);
    faceTexture.draw(0,0);
    
    if (malfunctionedLatch) {
        hpMalfunctioned.draw();
    }

    if (winningLatch) {
        hpWinning.draw();
    }
    
    if (!memoryProcessor.hasRebooted()) {
        hpRebooting.draw();
    }
    
}
//--------------------------------------------------------------
void EmotionHandler::drawHatching()
{
    int x = (offsetX*4)+receivingEmotionImage.getWidth();
    
    hatchTexture.begin();
    ofClear(255,0);
    ofPushMatrix();
    if (HAPPILEE_PURGING) {
        ofTranslate(purgingEmotions.update(), 0);
    }
    else {
        ofTranslate(0, 0);
    }
    for (int x = 0; x < 14; x++) {
        ofPushMatrix();
        ofTranslate(x*35, (height+30)/2);
        ofPushMatrix();
        ofTranslate(0, -(height+30)/2);
        ofRotateZ(45);
        
        if (hpState == HAPPILEE_PURGING) {
            ofSetColor(ofColor::white);
        }
        else {
            ofSetColor(51);
        }
        
        ofDrawRectangle(0, -15, 15, height+30);
        ofPopMatrix();
        ofPopMatrix();
    }
    ofPopMatrix();
    hatchTexture.end();
}
//--------------------------------------------------------------
void EmotionHandler::drawEmotions()
{
    int x = (offsetX*4)+receivingEmotionImage.getWidth();
    
    ofRectangle foundNewEmotion;
    
    if (whichEmotion != getNeutralFaceID()) {
        foundNewEmotion = ofRectangle(x,centerBoxY-5,regularIndicatorFont.stringWidth("Found New Emotion:"),-regularIndicatorFont.stringHeight("Found New Emotion:"));
    }
    else {
        foundNewEmotion = ofRectangle(x,centerBoxY-5,regularIndicatorFont.stringWidth("Searching"),-regularIndicatorFont.stringHeight("Searching"));
    }
    
    ofRectangle capacityWarning = ofRectangle(centerX+(offsetX*2)+warningImage.getWidth(),centerBoxY-5,lightIndicatorFont.stringWidth("Warning Low Capacity:"),-lightIndicatorFont.stringHeight("Warning Low Capacity:"));
    
    
    ofRectangle memoryPurged = ofRectangle(((centerX+offsetX)+(width/2))-(boldIndicatorFont.stringWidth("Memory Purged")/2),centerBoxY+(boldIndicatorFont.stringHeight("Memory Purged")/2),boldIndicatorFont.stringWidth("Memory Purged"),boldIndicatorFont.stringHeight("Memory Purged"));
    
    drawHatching();
    
    if (memoryProcessor.getMemoryRemaining() < lowMemoryAmount && !lowMemory) {
        lowMemory = true;
    }
    else if(memoryProcessor.getMemoryRemaining() > lowMemoryAmount+1 && lowMemory) {
        lowMemory = false;
    }
    
    if (hpState == HAPPILEE_WIN) {
        ofSetColor(255);
        boldIndicatorFont.drawString("Memory Purged", memoryPurged.x,memoryPurged.y);
    }
    else if(hpState == HAPPILEE_PURGING) {
        ofSetColor(255, 255, 255);
        hatchTexture.draw((ofGetWidth()*0.5)+(offsetX),(ofGetHeight()-(offsetY+height)+offsetX/2));
        
        if (dots.size() > 2) {
            dots.clear();
            dots = ".";
        }
        if (ofGetFrameNum() % 10 == 0) {
            dots += ".";
        }
        boldIndicatorFont.drawString("Purging Memory"+dots, (memoryPurged.x-(ofGetWidth()*0.5))+(offsetX*2),memoryPurged.y);
    }
    else if(hpState == HAPPILEE_MALFUNCTION) {
        ofSetColor(255, 255, 255);
        hatchTexture.draw((ofGetWidth()*0.5)+(offsetX),(ofGetHeight()-(offsetY+height)+offsetX/2));
        ofRectangle noMemory = ofRectangle(((centerX+offsetX)+(width/2))-(boldIndicatorFont.stringWidth("No Memory Remaining")/2),centerBoxY+(boldIndicatorFont.stringHeight("No Memory Remaining")/2),boldIndicatorFont.stringWidth("No Memory Remaining"),boldIndicatorFont.stringHeight("No Memory Remaining"));
        
        ofSetColor(255, 255, 255);
        boldIndicatorFont.drawString("No Memory Remaining",noMemory.x,noMemory.y);
        
        ofSetColor(255, 255, 255);
        warningImage.draw(warningImagePos);
    }
    else {
        
        if (lowMemory) {
            ofSetColor(255, 255, 255);
            hatchTexture.draw((ofGetWidth()*0.5)+(offsetX),(ofGetHeight()-(offsetY+height)+offsetX/2));
        }
        
        // Draw Static Text
        ofSetColor(51, 51, 51);
        if (whichEmotion != getNeutralFaceID()) {
            regularIndicatorFont.drawString("Found New Emotion", foundNewEmotion.x,foundNewEmotion.y);
        }
        else {
            if (dots.size() > 2) {
                dots.clear();
                dots = ".";
            }
            if (ofGetFrameNum() % 10 == 0) {
                dots += ".";
            }

            regularIndicatorFont.drawString("Searching"+dots, foundNewEmotion.x,foundNewEmotion.y);
        }
        wordsContainer.draw(x,centerBoxY-offsetY);

        ofSetColor(255);
        regularIndicatorFont.drawString("Warning Low Capacity:",capacityWarning.x,capacityWarning.y);
        
        ofSetColor(255);
        string memSet = ofToString(memoryProcessor.getMemoryRemaining()/1000)+"MB Remaining";
        boldIndicatorFont.drawString(memSet,capacityWarning.x,centerBoxY+20);
        ofSetColor(255, 255, 255);
        warningImage.draw(warningImagePos);
    }
    ofSetColor(255, 255, 255);
    receivingEmotionImage.draw(receivingImagePos);
}
#pragma mark - Setters
//--------------------------------------------------------------
void EmotionHandler::setImage(int whichImage,int maxTweenTime)
{
    whichEmotion = whichImage;
    newImagePosition = whichImage*emotionImages[0].getHeight();
    
    if (whichImage == getNeutralFaceID()) {
        newEmotionPosition = 0;
    }
    else {
        newEmotionPosition = whichImage*(darkIndicatorFont.getGlyphBBox().height+10);
    }

    moveEmotion.setParameters(1, expo, ofxTween::easeInOut, -50, newEmotionPosition, 250, 0);
    
    if(hpState == HAPPILEE_RED) {
        if (whichEmotion > neutralEmotionID) {
            emotionSoundsDistorted[whichEmotion-1].play();
            memoryProcessor.reduceMemory(redReductionAmount);
        }
        else if(whichEmotion == neutralEmotionID) {     }
        else {
            emotionSoundsDistorted[whichEmotion].play();
            memoryProcessor.reduceMemory(redReductionAmount);
        }
    }
    else if(hpState == HAPPILEE_YELLOW) {
        if (whichEmotion > neutralEmotionID) {
            emotionSoundsClean[whichEmotion-1].play();
            memoryProcessor.reduceMemory(yellowReductionAmount);
            
        }
        else if(whichEmotion == neutralEmotionID) {     }
        else {
            emotionSoundsClean[whichEmotion].play();
            memoryProcessor.reduceMemory(yellowReductionAmount);
        }
    }
    else if(hpState == HAPPILEE_GREEN) {
        if (whichEmotion > neutralEmotionID) {
            emotionSoundsClean[whichEmotion-1].play();
            memoryProcessor.reduceMemory(greenReductionAmount);
        }
        else if(whichEmotion == neutralEmotionID) {     }
        else {
            emotionSoundsClean[whichEmotion].play();
            memoryProcessor.reduceMemory(greenReductionAmount);
        }
    }
}
//--------------------------------------------------------------
void EmotionHandler::setHappileeState(HAPPILEE_STATE state)
{
    hpState = state;
    if (hpState == HAPPILEE_GREEN) {
        interferance.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
        interferance.setFx(OFXPOSTGLITCH_SWELL, false);
        interferance.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
        interferance.setFx(OFXPOSTGLITCH_SWELL, false);
        interferance.setFx(OFXPOSTGLITCH_TWIST, false);
        interferance.setFx(OFXPOSTGLITCH_SHAKER, false);
        interferance.setFx(OFXPOSTGLITCH_OUTLINE, false);
        interferance.setFx(OFXPOSTGLITCH_GLOW, false);
        interferance.setFx(OFXPOSTGLITCH_NOISE, false);
    }
    else if(hpState == HAPPILEE_YELLOW) {
        interferance.setFx(OFXPOSTGLITCH_NOISE, true);
        interferance.setFx(OFXPOSTGLITCH_SWELL, false);
        interferance.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
        interferance.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
        interferance.setFx(OFXPOSTGLITCH_TWIST, true);
        interferance.setFx(OFXPOSTGLITCH_SHAKER, true);
    }
    else if(hpState == HAPPILEE_RED) {
        interferance.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
        interferance.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
        interferance.setSlitAmount(10);
        interferance.setFx(OFXPOSTGLITCH_TWIST, true);
        interferance.setFx(OFXPOSTGLITCH_SHAKER, true);
    }
    else if(hpState == HAPPILEE_MALFUNCTION) {
        interferance.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
        interferance.setFx(OFXPOSTGLITCH_SWELL, false);
        interferance.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
        interferance.setFx(OFXPOSTGLITCH_SWELL, false);
        interferance.setFx(OFXPOSTGLITCH_TWIST, false);
        interferance.setFx(OFXPOSTGLITCH_SHAKER, false);
        interferance.setFx(OFXPOSTGLITCH_OUTLINE, false);
        interferance.setFx(OFXPOSTGLITCH_GLOW, false);
        interferance.setFx(OFXPOSTGLITCH_NOISE, false);
    }
}
//--------------------------------------------------------------
void EmotionHandler::setDeadState()
{
    malfunctioningSound.play();
    malfunctioningTimer.start();
    hpState = HAPPILEE_MALFUNCTION;
    setImage(malfunctionEmotionID, 0);
    malfunctioning.setParameters(5, line, ofxTween::easeInOut, 0, 1.0, malfunctionTimerLength,0);
}
//--------------------------------------------------------------
void EmotionHandler::setWinState()
{
    hpState = HAPPILEE_PURGING;
    purgingSound.play();
    purgingEmotions.setParameters(4,line, ofxTween::easeInOut, -ofGetWidth()*0.65, 0, 5000, 0);
}
#pragma mark - Getters
//--------------------------------------------------------------
int EmotionHandler::getNumberOfEmotions()
{
    return emotionImages.size();
}
//--------------------------------------------------------------
int EmotionHandler::getNeutralFaceID()
{
    return neutralEmotionID;
}
//--------------------------------------------------------------
int EmotionHandler::getMalfunctionFaceID()
{
    return malfunctionEmotionID;
}
#pragma mark - Listeners
//--------------------------------------------------------------
void EmotionHandler::didTweenFinish(int &val)
{
    if(val == 4){
        hpState = HAPPILEE_WIN;
        purgingSound.stop();
        winningLatch = true;
        setImage(neutralEmotionID, 0);
    }
    else if(val == 5){
    
    }
}
//--------------------------------------------------------------
void EmotionHandler::happileeHasRebooted(string &str)
{
    setImage(neutralEmotionID, 0);
    malfunctionedLatch = false;
    winningLatch = false;
    welcomeSound.play();
    cout << str << endl;
}
//--------------------------------------------------------------
void EmotionHandler::malfunctioningTimerFinshed(string &str)
{
    malfunctionedLatch = true;
    cout << str << endl;
}
