#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "MapGenerator.h"
//#include "DisplayWindow.h"
#include "MyTimer.h"
#include "PlayerManager.h"
#include "RobotManager.h"
#include "ScoreBoard.h"
#include "StyledMap.h"
#include "BaseButton.h"
#include "MapViewer.h"
#include "SplashScreen.h"
#include "MapMesh.h"
#include "ofxIO.h"
#include "ImageServer.h"

struct guiStruct {
    guiStruct() {}
    guiStruct(int _id,string _name){
        id = _id;
        name = _name;
    }
    int id;
    string name;
};

bool operator<(const guiStruct &a,const guiStruct &b){return a.name < b.name;}

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
        void mouseScrolled(int x, int y, float scrollX, float scrollY);
        void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawCalibrationMode();
        void drawEditorMode();
        void drawGeneratorMode();
        void drawOperationMode();
    
        pixelServer server;
    
        //--------------------------------------------------------------
        // *
        // * Second Window
        // *
        //--------------------------------------------------------------
//        shared_ptr<DisplayWindow> displayWindow;

        //--------------------------------------------------------------
        // *
        // * Map Generator
        // *
        //--------------------------------------------------------------
        MapGenerator mapGenerator;
        MapMesh mapMesh;
    
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
    
        int lRT;
        int lGT;
        int lYT;
    
        bool malfunctioned[3];
    
        string feedBackMap;
        string saveDifficultly;
        string mode;
        string previousState[3];
    
    
    
        //--------------------------------------------------------------
        // *
        // * Directory Listener
        // *
        //--------------------------------------------------------------
        void setupDirectoryWatcher();
        void onDirectoryWatcherItemAdded(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt);
        void onDirectoryWatcherItemRemoved(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt);
        void onDirectoryWatcherItemModified(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt);
        void onDirectoryWatcherItemMovedFrom(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt);
        void onDirectoryWatcherItemMovedTo(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt);
        void onDirectoryWatcherError(const Poco::Exception& exc);
    
        ofx::IO::DirectoryWatcherManager watcher;
        ofx::IO::HiddenFileFilter fileFilter;
        string latestMap;
    
        //--------------------------------------------------------------
        // *
        // * Other Objects
        // *
        //--------------------------------------------------------------
        string event[10];
        int _Appmode;
        void setupVariables();
        bool bUnitMalfunctioned[3];

        PlayerManager playerManager;
        RobotManager robotManager;
        SplashScreen splashScreen;
        Scoreboard scoreBoard;
        MapViewer mapViewer;
        StyledMap styledMap;
        MyTimer countDown;
    

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
        void setupGuis();
        void setupOperationsGui();
        void setupGeneratorGui();
    
        void drawGeneratorGui();
        void drawEditorGui();
    
        void updateGui();
        bool drawOperationsButtons;
        bool drawGui;
        bool drawMapGui;
        bool drawOperationalElementsGui;
        bool drawCalibrationGui;
    
        //---------------------------------
        // *
        // *    Operations Gui
        // *
        //---------------------------------
        ofxDatGuiScrollView * view;
        ofxDatGuiDropdown * appMode;
        ofxDatGuiButton * startLevel;
        ofxDatGuiButton * stopLevel;
        ofxDatGuiButton * resetLevel;
        ofxDatGuiFRM * fpsIndicator;
        ofxDatGuiLabel * title;
        ofxDatGuiToggle * showMesh;
        ofxDatGuiDropdown * difficultyBar;
        ofxDatGuiMatrix * levelSelect;
        ofxDatGuiToggle * showSecondWindow;
        ofxDatGuiButton * saveMapRecord;
    
        void setupCommandsGui(map<int,cmds> _commands);
        vector <ofxDatGuiButton*> commands;
    
        //---------------------------------
        // *
        // *    Map Generation Gui
        // *
        //---------------------------------
    
        std::map<int, ofxDatGuiComponent*> genComponents;
        std::map<string, ofxDatGuiComponent*> genStrComponents;
    
        ofxDatGuiSlider * mapWidth;
        ofxDatGuiSlider * mapHeight;
        ofxDatGuiSlider * tileSize;
        ofxDatGuiSlider * offsetEdge;
        ofxDatGuiSlider * randomSeed;
        ofxDatGuiSlider * obsticles;
        ofxDatGuiSlider * dangerAreaSize;
        ofxDatGuiSlider * smoothingLoops;
        ofxDatGuiSlider * growthLoops;
    
        ofxDatGuiButton * save;
        ofxDatGuiButton * clearMap;
        ofxDatGuiButton * generateMap;
        ofxDatGuiButton * generateCustomMap;
        ofxDatGuiButton * animateMap;
        ofxDatGuiButton * saveSettings;
    
        ofxDatGuiSlider * lowRedThreshold;
        ofxDatGuiSlider * highRedThreshold;
        ofxDatGuiSlider * lowGreenThreshold;
        ofxDatGuiSlider * highGreenThreshold;
        ofxDatGuiSlider * lowYellowThreshold;
        ofxDatGuiSlider * highYellowThreshold;
        ofxDatGuiSlider * blurImage;
    
        //---------------------------------
        // *
        // *    Player Scale
        // *
        //---------------------------------
        ofxDatGuiToggle * doScaling;
        ofxDatGuiSlider * scaleX;
        ofxDatGuiSlider * scaleY;
    
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
