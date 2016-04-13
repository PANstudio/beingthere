#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "MapGenerator.h"
#include "DisplayWindow.h"
#include "MyTimer.h"
#include "PlayerManager.h"
#include "ScoreBoard.h"
#include "StyledMap.h"
#include "BaseButton.h"
//#include "SimpleButton.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawWindows();

        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawCalibrationMode();
        void drawEditorMode();
        void drawGeneratorMode();
        void drawOperationMode();

        //--------------------------------------------------------------
        // *
        // * Second Window
        // *
        //--------------------------------------------------------------
        shared_ptr<DisplayWindow> displayWindow;

        //--------------------------------------------------------------
        // *
        // * Map Generator
        // *
        //--------------------------------------------------------------
        MapGenerator mapGenerator;
        vector<int> dLvs;
        int _level;
        string _difficulty;
        int _difficultyMode;
        bool _urs;
        float _rs;
        int _width;
        int _height;
        int _fillPercent;
        int _numberOfIslands;
        int _dangerAreaSize;
        int _smooth;
        int _growthNo;
        int _offsetEdge;
        int _fromCenter;
        int _gridX;
        int _gridY;
        int _gridW;
        int _gridH;
        int _spacing;
        int _numberOfXLines;
        int _numberOfYLines;
        int _spacingX;
        int _spacingY;
        int _iRR[2];
        int _iRY[2];
        int _iRG[2];
        int _blur;
        string feedBackMap;
        string saveDifficultly;
        string mode;
    
        //--------------------------------------------------------------
        // *
        // * Other Objects
        // *
        //--------------------------------------------------------------
        string event[10];
        int _Appmode;
        void setupVariables();
        PlayerManager playerManager;
        MyTimer countDown;
        Scoreboard scoreBoard;
        StyledMap styledMap;
        ofTrueTypeFont heading;
        bool _showShaded;
        bool _showPreviewWindow;
    
        //--------------------------------------------------------------
        // *
        // * Listeners
        // *
        //--------------------------------------------------------------
        void setupListeners();
        void removeListeners();
        void countDownStarted(string &str);
        void countDownFinished(string &str);
    
        void getMapEvent(struct event &ev);
        void reduceHealth(string &ev);

        void debugLog(string &ev);
    
        //--------------------------------------------------------------
        // *
        // * GUI
        // *
        //--------------------------------------------------------------
        void setupGUI();
        void setupOperationsButton();
        bool drawOperationsButtons;
        bool drawGui;
        bool drawMapGui;
        bool drawOperationalElementsGui;
        bool drawCalibrationGui;
    
    
        // GUI Objects
        ofxDatGui * gui;
        ofxDatGui * mapGui;
        ofxDatGui * styleGui;
        ofxDatGui * calibrationGui;
        ofxDatGui * operationElements;
    
        ofxDatGuiButton * addItem;
    
        ofxDatGuiScrollView * view;
        ofxDatGuiDropdown * appMode;
        ofxDatGuiButton * startLevel;
        ofxDatGuiButton * stopLevel;
        ofxDatGuiButton * resetLevel;
        ofxDatGuiFRM * fpsIndicator;
        ofxDatGuiLabel * title;
        ofxDatGuiDropdown * difficultyBar;
        ofxDatGuiMatrix * levelSelect;
        ofxDatGuiToggle * showSecondWindow;
        ofxDatGuiButton * saveMapRecord;
    
        void setGuiListeners(ofxDatGui* guiRef);
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
        void onMatrixEvent(ofxDatGuiMatrixEvent e);
        void onScrollViewEvent(ofxDatGuiScrollViewEvent e);
};
