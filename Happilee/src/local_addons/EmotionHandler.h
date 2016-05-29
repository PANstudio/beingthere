//
//  EmotionHandler.h
//  Happilee
//
//  Created by David Haylock on 26/05/2016.
//
//

#ifndef EmotionHandler_h
#define EmotionHandler_h



#include <stdio.h>
#include "ofMain.h"
#include "ofxTween.h"
#include "MemoryBar.h"

enum HAPPILEE_STATE {
    HAPPILEE_GREEN = 0,
    HAPPILEE_YELLOW,
    HAPPILEE_RED,
    HAPPILEE_MALFUNCTION,
    HAPPILEE_WIN,
    HAPPILEE_PURGING
};

class EmotionHandler: public ofThread {
    
    public:
        //! Setup
        void setup();
    
        //! Load Images
        void loadImages();
    
        //! Load Fonts
        void loadFonts();
    
        //! Load Sounds
        void loadSounds();
    
        //! Update
        void update();
    
        //! Draw
        void drawDebug();
    
        //! Draw Images
        void drawImages();
    
        //! Draw Indicators
        void drawIndicators();
    
        //! Draw Emotions
        void drawEmotions();
    
        //! Sets a Random Image
        void setImage(int whichImage,int maxTweenTime);
    
        //! Clear Images from Memory
        void cleanUp();
    
        //! Speak Easy
        void threadedFunction();
    
        //! How many emotions are in the folder
        int getNumberOfEmotions();
    
        void setHappileeState(HAPPILEE_STATE state);
    
        void startSpeakEasy();
    
        void resetMemory();
    
        void setWinState();
    
        void setDeadState();
    
        MemoryBar memoryProcessor;
    
    private:
    
        ofDirectory emotionsDirectory;
        ofDirectory cleanSoundsDirectory;
        ofDirectory distortedSoundsDirectory;
    
        vector <ofImage> emotionImages;
        vector <string> emotionStrings;
        ofSoundPlayer *emotionSoundsClean;
        ofSoundPlayer *emotionSoundsDistorted;
    
    
        int lastImagePosition;
        int newImagePosition;
    
        int lastEmotionPosition;
        int newEmotionPosition;
    
        void didTweenFinish(int &val);

        ofxTween moveImage;
        ofxTween moveEmotion;
        ofxTween purgingEmotions;
        ofxEasingExpo expo;
        ofxEasingCubic cub;
        ofxEasingLinear line;
    
        ofFbo wordsContainer;
        ofFbo hatchTexture;
    
        ofImage receivingEmotionImage;
        ofImage warningImage;
    
        ofRectangle r1;
        bool moveImageLatch;
        bool changeStringLatch;
        bool lowMemory;
        string dots;
        int whichEmotion;
    
    
        HAPPILEE_STATE hpState;
    
        ofTrueTypeFont regularIndicatorFont;
        ofTrueTypeFont lightIndicatorFont;
        ofTrueTypeFont darkIndicatorFont;
        ofTrueTypeFont boldIndicatorFont;
    
};

#endif /* EmotionHandler_h */
