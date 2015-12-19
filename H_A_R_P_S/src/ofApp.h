#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "MapGenerator.hpp"
#include "DisplayWindow.hpp"
#include "MyTimer.hpp"
#include "PlayerManager.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
        //--------------------------------------------------------------
        // *
        // * Second Window
        // *
        //--------------------------------------------------------------
        shared_ptr<DisplayWindow> displayWindow;
    
        string testEvent;

        int _Appmode;
        void setupVariables();
    
        PlayerManager playerManager;
        MyTimer countDown;
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
        string feedBackMap;
    
        //--------------------------------------------------------------
        // *
        // * GUI
        // *
        //--------------------------------------------------------------
        void setupGUI();
        bool drawGui;
        // GUI Objects
        ofxDatGui * gui;
        ofxDatGuiFolder * _mapFolder;
    
        void drawCalibrationGUI(bool visible);
        void drawGenerationGUI(bool visible);
        void drawOperationGUI(bool visible);
        void drawEditorGUI(bool visible);
    
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
        void onMatrixEvent(ofxDatGuiMatrixEvent e);
		
};
