#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    emotionProcessor.setup();
    emotionProcessor.startSpeakEasy();
    selectEmotion = 0;
    hpState = 0;
    
    receiver.setup(7890);
    receiver.startListening();
    
    setupListeners();
    
    emotionTimer.setup(5000, "Emotion Timer", true);
    emotionTimer.start();
    
    int numOfEmotions = emotionProcessor.getNumberOfEmotions();
    
    for (int i = 0; i < numOfEmotions; i++) {
        if (i != 9) {
            randomisedEmotions.push_back(i);
        }
    }
    
    shuffleEmotions();
}
//--------------------------------------------------------------
void ofApp::update()
{
    emotionProcessor.update();
    if (selectEmotion > randomisedEmotions.size()-1) {
        shuffleEmotions();
        selectEmotion = 0;
    }
    emotionTimer.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(255, 255, 255);
    drawFaceElement();
    emotionProcessor.drawImages();
//    drawIndicators();
    emotionProcessor.drawIndicators();
    emotionProcessor.drawEmotions();

    ofSetColor(0);
    ofDrawLine(mouseX, mouseY, mouseX+25, mouseY-25);
    ofDrawBitmapStringHighlight(ofToString(mouseX)+" "+ofToString(mouseY),
                                mouseX+25,
                                mouseY-25);
}
//--------------------------------------------------------------
void ofApp::exit()
{
    removeListeners();
    receiver.stopListening();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
        case 'g':
            hpState = HAPPILEE_GREEN;
            emotionProcessor.setHappileeState(HAPPILEE_GREEN);
            break;
        case 'y':
            hpState = HAPPILEE_YELLOW;
            emotionProcessor.setHappileeState(HAPPILEE_YELLOW);
            break;
        case 'r':
            hpState = HAPPILEE_RED;
            emotionProcessor.setHappileeState(HAPPILEE_RED);
            break;
        case 'R':
            emotionProcessor.resetMemory();
            emotionTimer.setup(4000, "Emotion Timer", true);
            emotionTimer.start();
            break;
        case 'w':
            emotionProcessor.setWinState();
            emotionProcessor.setImage(13, 2000);
            emotionTimer.stop();
            break;
        case 'd':
            emotionProcessor.setDeadState();
            break;
        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {       }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {       }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {       }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {       }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {       }
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {       }
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {       }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {       }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {       }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {       }
//--------------------------------------------------------------
void ofApp::drawFaceElement()
{
    ofPushStyle();
    ofSetColor(255, 216, 21);
    ofSetCircleResolution(200);
    ofDrawCircle(ofGetWidth()*0.5, ofGetHeight()*0.40, 160);
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::drawIndicators()
{
    ofPushStyle();
    int offsetX = 13;
    int offsetY = 10;
    int width = (ofGetWidth()*0.5)-(offsetX);
    int height = 80;
    
    // Blue Box Left Side
    ofSetColor(0, 181, 208);
    ofDrawRectRounded(offsetX,
                      (ofGetHeight()-height)-offsetY,
                      width-(offsetX*0.5),
                      height,
                      0);
    
    // Red Box Right Side
    ofSetColor(255, 67, 81);
    ofDrawRectRounded((ofGetWidth()-width)-offsetX+(offsetX*0.5),
                      (ofGetHeight()-height)-offsetY,
                      width-(offsetX*0.5),
                      height,
                      0);
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::setupListeners()
{
    ofAddListener(emotionTimer.timerStarted,this,&ofApp::timerStarted);
    ofAddListener(emotionTimer.timerFinished,this,&ofApp::timerEnded);
    
    ofAddListener(emotionProcessor.memoryProcessor.isDead, this, &ofApp::haveDied);
    ofAddListener(receiver.greenZone, this, &ofApp::inGreenZone);
    ofAddListener(receiver.yellowZone, this, &ofApp::inYellowZone);
    ofAddListener(receiver.redZone, this, &ofApp::inRedZone);
    ofAddListener(receiver.safeZone, this, &ofApp::inSafeZone);
    ofAddListener(receiver.reboot, this, &ofApp::rebootHappilee);
    ofAddListener(receiver.malfunction, this, &ofApp::malfunctionHappilee);
}
//--------------------------------------------------------------
void ofApp::removeListeners()
{
    ofRemoveListener(emotionTimer.timerStarted,this,&ofApp::timerStarted);
    ofRemoveListener(emotionTimer.timerFinished,this,&ofApp::timerEnded);
    ofRemoveListener(emotionProcessor.memoryProcessor.isDead, this, &ofApp::haveDied);
    ofRemoveListener(receiver.greenZone, this, &ofApp::inGreenZone);
    ofRemoveListener(receiver.yellowZone, this, &ofApp::inYellowZone);
    ofRemoveListener(receiver.redZone, this, &ofApp::inRedZone);
    ofRemoveListener(receiver.safeZone, this, &ofApp::inSafeZone);
    ofRemoveListener(receiver.reboot, this, &ofApp::rebootHappilee);
    ofRemoveListener(receiver.malfunction, this, &ofApp::malfunctionHappilee);
}
//--------------------------------------------------------------
void ofApp::timerStarted(string &val)
{
//    cout << "Timer Started" << endl;
}
//--------------------------------------------------------------
void ofApp::timerEnded(string &val)
{
    emotionProcessor.setImage(randomisedEmotions[selectEmotion],500);
    switch (hpState) {
        case HAPPILEE_GREEN:
            emotionTimer.setNewTimerLength(ofRandom(2000,4000));
            break;
        case HAPPILEE_YELLOW:
            emotionTimer.setNewTimerLength(ofRandom(750,1500));
            break;
        case HAPPILEE_RED:
            emotionTimer.setNewTimerLength(ofRandom(500,750));
            break;
        default:
            break;
    }
    selectEmotion++;
}
//--------------------------------------------------------------
void ofApp::haveDied(string &val)
{
    cout << "Happilee Has Malfunctioned" << endl;
    emotionTimer.stop();
    emotionProcessor.setDeadState();
}
//--------------------------------------------------------------
void ofApp::resetMemory(string &val)
{
    emotionProcessor.resetMemory();
    emotionTimer.setup(4000, "Emotion Timer", true);
    emotionTimer.start();
}
//--------------------------------------------------------------
void ofApp::inGreenZone(string &val)
{
    hpState = HAPPILEE_GREEN;
    emotionProcessor.setHappileeState(HAPPILEE_GREEN);
}
//--------------------------------------------------------------
void ofApp::inYellowZone(string &val)
{
    hpState = HAPPILEE_YELLOW;
    emotionProcessor.setHappileeState(HAPPILEE_YELLOW);
}
//--------------------------------------------------------------
void ofApp::inRedZone(string &val)
{
    hpState = HAPPILEE_RED;
    emotionProcessor.setHappileeState(HAPPILEE_RED);
}
//--------------------------------------------------------------
void ofApp::inSafeZone(string &val)
{
    emotionProcessor.setWinState();
    emotionProcessor.setImage(13, 2000);
    emotionTimer.stop();
}
//--------------------------------------------------------------
void ofApp::rebootHappilee(string &val)
{
    emotionProcessor.resetMemory();
    emotionTimer.setup(4000, "Emotion Timer", true);
    emotionTimer.start();
}
//--------------------------------------------------------------
void ofApp::malfunctionHappilee(string &val)
{
    emotionProcessor.setDeadState();
}
//--------------------------------------------------------------
void ofApp::fisherYatesShuffle(vector<int> &randomised)
{
    std::srand(std::time(nullptr));
//    cout << "BShuffle ";
//    std::copy(randomised.cbegin(), randomised.cend(),
//              std::ostream_iterator<int>(std::cout," "));
//    
    auto currentIndexCounter = randomised.size();
    for (auto iter = randomised.rbegin(); iter != randomised.rend(); iter++, --currentIndexCounter) {
        
        int randomIndex = std::rand()&currentIndexCounter;
        if (randomIndex > randomised.size() || *iter < 0) {
            cout << "Issue Here" << endl;
            return;
        }
        else {
            if (*iter != randomised.at(randomIndex)) {
                swap(randomised.at(randomIndex), *iter);
            }
        }
        
    }
//    cout << "AShuffle ";
//    std::copy(randomised.cbegin(), randomised.cend(),
//              std::ostream_iterator<int>(std::cout," "));
}
//--------------------------------------------------------------
void ofApp::shuffleEmotions()
{
    randomisedEmotions.clear();
    int numOfEmotions = emotionProcessor.getNumberOfEmotions();
    
    for (int i = 0; i < numOfEmotions; i++) {
        if (i != 9) {
            randomisedEmotions.push_back(i);
        }
    }
    
    fisherYatesShuffle(randomisedEmotions);
    
    vector<int>::iterator it;
    for (int i = 0; i < randomisedEmotions.size(); i++) {
        if (i % 2) {
            it = randomisedEmotions.begin()+i;
            randomisedEmotions.insert(it,9);
        }
    }
//    for (int i = 0; i < randomisedEmotions.size(); i++) {
//        if (i == randomisedEmotions.size()) {
//            cout << randomisedEmotions[i] << endl;
//        }
//        else {
//            cout << randomisedEmotions[i] << " ";
//        }
//    }
    cout << endl;
}