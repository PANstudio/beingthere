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
#include "MyTimer.h"

enum HAPPILEE_STATE {
    HAPPILEE_GREEN = 0,
    HAPPILEE_YELLOW,
    HAPPILEE_RED,
    HAPPILEE_MALFUNCTION,
    HAPPILEE_WIN,
    HAPPILEE_PURGING,
    HAPPILEE_REBOOTING
};

class EmotionHandler {
    
    public:
        //! Setup
        void setup(int initialMemory,int _lowMemoryAmount,int _malfunctionTimerLength);
    
        //! Set Reduction Amounts
        void setReductionAmount(int greenLevel,int yellowLevel,int redLevel);
    
        //! Load Images
        void loadImages();
    
        //! Load Fonts
        void loadFonts();
    
        //! Load Sounds
        void loadSounds();
    
        //! Update
        void update();
    
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
        
        void malfunctioningTimerFinshed(string &str);
    
        void happileeHasRebooted(string &str);
    
    private:
    
        int _HappileeMemory;
        ofDirectory emotionsDirectory;
        ofDirectory cleanSoundsDirectory;
        ofDirectory distortedSoundsDirectory;
    
        vector <ofImage> emotionImages;
        vector <string> emotionStrings;
        ofSoundPlayer *emotionSoundsClean;
        ofSoundPlayer *emotionSoundsDistorted;
    
        ofSoundPlayer purgingSound;
        ofSoundPlayer welcomeSound;
        ofSoundPlayer goodbyeSound;
        ofSoundPlayer malfunctioningSound;
        ofSoundPlayer malfunctioningDing;
    
    
        int lastImagePosition;
        int newImagePosition;
    
        int lastEmotionPosition;
        int newEmotionPosition;
    
        void didTweenFinish(int &val);
    
        HappileeMalfunctioned hpMalfunctioned;
        HappileeRebooting hpRebooting;
    
//        ofShader shader;
    
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
    
        MyTimer malfunctioningTimer;
        bool malfunctionedLatch;
    
        string dots;
    
        int whichEmotion;
        int neutralEmotionID;
        int malfunctionEmotionID;
    
        int greenReductionAmount;
        int yellowReductionAmount;
        int redReductionAmount;
    
        int malfunctionTimerLength;
    
        ofShader alphaMask;
        ofImage alphaMaskImage;
        HAPPILEE_STATE hpState;
    
        ofTrueTypeFont regularIndicatorFont;
        ofTrueTypeFont lightIndicatorFont;
        ofTrueTypeFont darkIndicatorFont;
        ofTrueTypeFont boldIndicatorFont;
    
    protected:
    
    int offsetX;
        int offsetY;
        int width;
        int height;
        int centerX;
        int centerBoxY;
        ofPoint receivingImagePos;
        ofPoint warningImagePos;
        int lowMemoryAmount;
    
        ofColor fontColor;
        ofColor faceColor;
};

#endif /* EmotionHandler_h */
