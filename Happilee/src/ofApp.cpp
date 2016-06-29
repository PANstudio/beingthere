#include "ofApp.h"

#pragma mark - OF Functions
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetDataPathRoot("../Resources/data/");
    hapConfig.load("config/HappileeConfiguration.json");
    
    // Setup the Emotion Processors
    emotionProcessor.setup(hapConfig.getConfig().memoryAmount,
                           hapConfig.getConfig().lowMemoryAmount
                           );
    
    emotionProcessor.setReductionAmount(hapConfig.getConfig().greenMemoryReduction,
                                        hapConfig.getConfig().yellowMemoryReduction,
                                        hapConfig.getConfig().redMemoryReduction
                                        );
    selectEmotion = 0;
    hpState = 0;
    
    receiver.setup(7890);
    receiver.startListening();
    
    setupListeners();
    
    emotionTimer.setup(5000, "Emotion Timer", true);
    emotionTimer.start();
    
    shuffleEmotions();
}
//--------------------------------------------------------------
void ofApp::update()
{
    if (selectEmotion > randomisedEmotions.size()-1) {
        shuffleEmotions();
        selectEmotion = 0;
    }
    emotionProcessor.update();
    emotionTimer.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(255, 255, 255);
    emotionProcessor.drawImages();
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
            shuffleEmotions();
            emotionTimer.setup(4000, "Emotion Timer", true);
            emotionTimer.start();
            hpState = HAPPILEE_GREEN;
            emotionProcessor.setHappileeState(HAPPILEE_GREEN);
            break;
        case 'w':
            emotionProcessor.setWinState();
            emotionProcessor.setImage(13, 2000);
            emotionTimer.stop();
            break;
        case 'd':
            emotionProcessor.setDeadState();
            emotionTimer.stop();
            break;
        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::drawDebugInfo()
{
    
}
#pragma mark - Listeners
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
void ofApp::timerStarted(string &val) {     }
//--------------------------------------------------------------
void ofApp::timerEnded(string &val)
{
    emotionProcessor.setImage(randomisedEmotions[selectEmotion],500);
    switch (hpState) {
        case HAPPILEE_GREEN:
            emotionTimer.setNewTimerLength(
                                           ofRandom(
                                                    hapConfig.getConfig().greenMemoryReductionTimerLength-1000,
                                                    hapConfig.getConfig().greenMemoryReductionTimerLength+1000)
                                           );
            break;
        case HAPPILEE_YELLOW:
            emotionTimer.setNewTimerLength(
                                           ofRandom(
                                                    hapConfig.getConfig().yellowMemoryReductionTimerLength-750,
                                                    hapConfig.getConfig().yellowMemoryReductionTimerLength+750)
                                           );
            break;
        case HAPPILEE_RED:
            emotionTimer.setNewTimerLength(ofRandom(
                                                    hapConfig.getConfig().redMemoryReductionTimerLength-250,
                                                    hapConfig.getConfig().redMemoryReductionTimerLength+250)
                                           );
            break;
        default:
            break;
    }
    selectEmotion++;
}
//--------------------------------------------------------------
void ofApp::happileeSuccessfullyRebooted(string &val)
{
    
}
#pragma mark - Events
//--------------------------------------------------------------
// *
// *    These are events that trigger the Happilee Actions
// *
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
    emotionTimer.start();
}
//--------------------------------------------------------------
void ofApp::malfunctionHappilee(string &val)
{
    emotionProcessor.setDeadState();
}
#pragma mark - Emotion Handlers
//--------------------------------------------------------------
// *
// *    Fisher Yates Shuffle Mechanism
// *
//--------------------------------------------------------------
void ofApp::fisherYatesShuffle(vector<int> &randomised)
{
    std::srand(std::time(nullptr));
    
    int randomisedSize = randomised.size();
    cout << "Before Shuffling ";
    std::copy(randomised.cbegin(), randomised.cend(),
              std::ostream_iterator<int>(std::cout," "));
    
    for (int i = randomisedSize-1 ; i > 0; i--) {
        int idx = (rand() % (i+1));
        swap(randomised[idx], randomised[i]);
    }
    cout << endl;
    
    cout << "After Shuffle ";
    std::copy(randomised.cbegin(), randomised.cend(),
              std::ostream_iterator<int>(std::cout," "));
    cout << endl;
}
//--------------------------------------------------------------
// *
// *    Shuffle Emotions
// *
//--------------------------------------------------------------
void ofApp::shuffleEmotions()
{
    randomisedEmotions.clear();

    int numOfEmotions = emotionProcessor.getNumberOfEmotions();
    cout << "Number of Emotion Faces: "<< numOfEmotions <<  endl;
    cout << "ID of Neutral Face: "<< emotionProcessor.getNeutralFaceID() <<  endl;
    cout << "ID of Malfunction Face: "<< emotionProcessor.getMalfunctionFaceID() <<  endl;
    for (int i = 0; i < numOfEmotions; i++) {
        if ((i == emotionProcessor.getNeutralFaceID()) || (i == emotionProcessor.getMalfunctionFaceID()))
        {        }
        else {
            randomisedEmotions.push_back(i);
        }
    }

    // Shuffle time
    fisherYatesShuffle(randomisedEmotions);
    
    // Add in the Neutral State
    vector<int>::iterator it;
    for (int i = 0; i < randomisedEmotions.size(); i++) {
        if (i % 2) {
            it = randomisedEmotions.begin()+i;
            randomisedEmotions.insert(it,9);
        }
    }
    it = randomisedEmotions.begin();
    randomisedEmotions.insert(it,9);
    
    // Print out the Shuffled Line
    for (int i = 0; i < randomisedEmotions.size(); i++) {
        if (i == randomisedEmotions.size()) {
            cout << randomisedEmotions[i] << endl;
        }
        else {
            cout << randomisedEmotions[i] << " ";
        }
    }
    cout << endl;
}