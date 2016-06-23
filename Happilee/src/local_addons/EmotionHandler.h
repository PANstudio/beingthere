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
#include "ofxPostGlitch.h"
#include "HappileeScenes.h"

enum HAPPILEE_STATE {
    HAPPILEE_GREEN = 0,
    HAPPILEE_YELLOW,
    HAPPILEE_RED,
    HAPPILEE_MALFUNCTION,
    HAPPILEE_WIN,
    HAPPILEE_PURGING
};

class EmotionHandler {
    
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
    
        //! Draw Hatching
        void drawHatching();
    
        //! Sets a Random Image
        void setImage(int whichImage,int maxTweenTime);
    
        //! Clear Images from Memory
        void cleanUp();
    
        //! How many emotions are in the folder
        int getNumberOfEmotions();
    
        //! Get the ID Number of the Neutral Face
        int getNeutralFaceID();
    
        //! Get the ID Number of the Malfunction Face
        int getMalfunctionFaceID();
    
        //! Set the Happilee Mode
        void setHappileeState(HAPPILEE_STATE state);
    
        //! Reset the Memory
        void resetMemory();
    
        //! Do Win State
        void setWinState();
    
        //! Do Dead State
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
    
        HappileeMalfunctioned hpMalfunctioned;
    
        ofxTween moveImage;
        ofxTween moveEmotion;
        ofxTween purgingEmotions;
        ofxTween malfunctioning;
        ofxEasingExpo expo;
        ofxEasingCubic cub;
        ofxEasingLinear line;
    
        ofFbo faceTexture;
        ofxPostGlitch interferance;
    
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
        int neutralEmotionID;
        int malfunctionEmotionID;
    
        ofShader alphaMask;
        ofImage alphaMaskImage;
        HAPPILEE_STATE hpState;
    
        ofTrueTypeFont regularIndicatorFont;
        ofTrueTypeFont lightIndicatorFont;
        ofTrueTypeFont darkIndicatorFont;
        ofTrueTypeFont boldIndicatorFont;
};

#endif /* EmotionHandler_h */
