#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setupVariables()
{
    _urs = false;
    _width = 100;
    _height = 100;
    _dangerAreaSize = 5;
    _rs = 3.13;
    _fillPercent = 10;
    _numberOfIslands = 10;
    _growthNo = 10;
    _smooth = 5;
    _offsetEdge = 5;
    _Appmode = 1;
    _numberOfXLines = 10;
    _numberOfYLines = 10;
    _spacingX = 10;
    _spacingY = 10;
}
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("H.A.R.P.S");
    
    // Yep its in the name
    setupGUI();
    setupVariables();
    mapGenerator.generateMap(50, 50, 0, 10, 25, 1, 3, 1.9, 3);
    playerManager.setup("localhost", 7890);
    playerManager.setNumberOfPlayers(3);
    countDown.setup(500, "Count Down", false, "ofxdatgui_assets/font-verdana.ttf");
}
//--------------------------------------------------------------
void ofApp::update()
{
    countDown.update();
    playerManager.listen();
    displayWindow->setHealthBars(playerManager.getPlayerHealth());
    displayWindow->getTimeLeft(countDown.getTimeLeft());
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0, 0, 0);
    mapGenerator.draw();
    mapGenerator.drawComputerVision();
    mapGenerator.drawPolylines();
    playerManager.drawPlayerManager();
    playerManager.drawPlayerHealth(550,500,0.5);
    countDown.draw(550, 450);
    ofDrawBitmapStringHighlight(testEvent, 500,15);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
        case OF_KEY_RETURN:
            drawGui = !drawGui;
            gui->setVisible(drawGui);
            break;
        case 'a':
            mapGenerator.generateMap(100, 100, 0, 5, 10, 2, 100, 140, 3);
            break;
        case '>':
            countDown.setNewTimerLength(ofRandom(10000));
            countDown.start();
            break;
        case '<':
            countDown.stop();
            break;
        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    mapGenerator.mouseOver(x, y);
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    mapGenerator.mouseDragged(x, y, button);
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    mapGenerator.mouseDown(x, y, button);
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    testEvent = msg.message;
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
//--------------------------------------------------------------
// *
// * GUI
// *
//--------------------------------------------------------------
void ofApp::setupGUI()
{
    int spacing = 7;
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->addHeader("H_A_R_P_S");
    gui->addFRM(1.0f);
    gui->addBreak();
    
    gui->addBreak(spacing);
    vector<string> AppMode = {"CALIBRATION MODE", "EDITOR MODE","GENERATION MODE", "OPERATION MODE"};
    
    gui->addDropdown("App Mode", AppMode);
    gui->getDropdown("App Mode")->select(0);
    gui->addBreak(spacing);
    
    vector<string> difficulty;
    vector<string> levels = {"1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10"
    };
    
    mapGenerator.loadMaps("config.json");
    for(int i = 0; i < mapGenerator.getMapsInfo().size(); i++) {
        difficulty.push_back(mapGenerator.getMapsInfo()[i].Difficulty);
        dLvs.push_back(mapGenerator.getMapsInfo()[i].numberOfLevels);
    }
    
    gui->addDropdown("Select Difficulty", difficulty);
    gui->getDropdown("Select Difficulty")->select(0);
    gui->getDropdown("Select Difficulty")->collapse();
    gui->addDropdown("Select Level", levels);
    gui->getDropdown("Select Level")->select(0);
    
    gui->addBreak(spacing);
    gui->addButton("Flush Map");
    
    gui->addBreak(spacing);
    gui->addButton("Start Level");
    gui->addButton("Stop Level");
    
    gui->addBreak(spacing);
    ofxDatGuiFolder * mapFolder = gui->addFolder("Map Generation",ofColor::blueSteel);
    mapFolder->addSlider("Map Width", 0, 150, 100);
    mapFolder->addSlider("Map Height", 0, 150, 100);
    mapFolder->addSlider("Tile Size", 0.00, 100.00, 50);
    mapFolder->addSlider("Offset Edge", 0, 100, 10);
    mapFolder->addSlider("Random Seed", 0.00, 150.00, 3.14);
    mapFolder->addSlider("Number of Obsticles", 0.00, 100.00, 20);
    mapFolder->addSlider("Danger Area Size", 0, 25, 20);
    mapFolder->addSlider("Smoothing Loops", 0, 25, 5);
    mapFolder->addSlider("Growth Loops", 0, 25, 10);
    mapFolder->addBreak(spacing);
    mapFolder->addButton("Clear Map");
    mapFolder->addBreak(spacing);
    mapFolder->addButton("Generate Map");
    mapFolder->addBreak(spacing);
    mapFolder->addButton("Generate Custom Map");
    
    gui->addBreak(spacing);
    ofxDatGuiFolder * cvFolder = gui->addFolder("CV Settings",ofColor::white);
    cvFolder->addSlider("Green Threshold", 0,255,200);
    cvFolder->addSlider("Yellow Threshold", 0,255,200);
    cvFolder->addSlider("Red Threshold", 0,255,200);
    cvFolder->addSlider("Blur Amount", 0, 21,9);
    cvFolder->addSlider("Simplify Contour", 0.0, 5.0,0.5);
    
    gui->addBreak(spacing);
    ofxDatGuiFolder * playerFolder = gui->addFolder("Player",ofColor::white);
    playerFolder->addSlider("Player Size", 0,25, 10);
    playerFolder->addColorPicker("Player Color");
    playerFolder->addSlider("Player Pulse Rate", 0,250, 10);
    playerFolder->addButton("Spawn New Start Posistion");
    
    gui->addBreak(spacing);
    ofxDatGuiFolder * targetFolder = gui->addFolder("Target",ofColor::white);
    ofRectangle r = ofRectangle(0,0,100,100);
    targetFolder->addSlider("Target Size", 0,25, 10);
    targetFolder->addColorPicker("Target Color");
    targetFolder->addSlider("Target Pulse Rate", 0,250, 10);
    targetFolder->addButton("Spawn New End Posistion");
    
    gui->addBreak(spacing);
    ofxDatGuiFolder * calibrationFolder = gui->addFolder("Calibration",ofColor::white);
    calibrationFolder->addToggle("From Centre / Top Left", false);
    calibrationFolder->addSlider("Grid Position X", 0,ofGetWidth(), 10); // This is CM
    calibrationFolder->addSlider("Grid Position Y", 0,ofGetHeight(), 10); // This is CM
    calibrationFolder->addSlider("Grid Size", 0,2000, 500); // This is CM
    calibrationFolder->addSlider("Number of X Lines", 0,50, 10); // This is CM
    calibrationFolder->addSlider("Number of Y Lines", 0,50, 10); // This is CM
    calibrationFolder->addSlider("Spacing X", 0,200, 10); // This is CM
    calibrationFolder->addSlider("Spacing Y", 0,200, 10); // This is CM
    
    gui->addFooter();
    
    // Listeners
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    gui->on2dPadEvent(this, &ofApp::on2dPadEvent);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    gui->onMatrixEvent(this, &ofApp::onMatrixEvent);
}
//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target->is("datgui opacity")) gui->setOpacity(e.scale);
    else if (e.target->is("Map Width")) _width = e.target->getValue();
    else if (e.target->is("Map Height")) _height = e.target->getValue();
    else if (e.target->is("Offset Edge")) _offsetEdge = e.target->getValue();
    else if (e.target->is("Random Seed")) _rs = e.target->getValue();
    else if (e.target->is("Tile Size")) _fillPercent = e.target->getValue();
    else if (e.target->is("Number of Obsticles")) _numberOfIslands = e.target->getValue();
    else if (e.target->is("Danger Area Size")) _dangerAreaSize = e.target->getValue();
    else if (e.target->is("Growth Loops")) _growthNo = e.target->getValue();
    else if (e.target->is("Smoothing Loops")) _smooth = e.target->getValue();
    else if (e.target->is("Grid Size")) _spacing = e.target->getValue();
    else if (e.target->is("Grid Position X")) _gridX = e.target->getValue();
    else if (e.target->is("Grid Position Y")) _gridY = e.target->getValue();
    else if (e.target->is("Number of X Lines")) _numberOfXLines = e.target->getValue();
    else if (e.target->is("Number of Y Lines")) _numberOfYLines = e.target->getValue();
    else if (e.target->is("Spacing X")) _spacingX = e.target->getValue();
    else if (e.target->is("Spacing Y")) _spacingY = e.target->getValue();
}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is("Generate Map")) mapGenerator.generateMap(_width, _height,_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
    else if (e.target->is("Flush Map")) mapGenerator.update();
//    else if (e.target->is("Clear Map")) mapGenerator.ClearMap();
    else if (e.target->is("Generate Custom Map")) mapGenerator.generateCustomMap(_width, _height,_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
    else if (e.target->is("Use Random Seed")) _urs = e.target->getEnabled();
//    else if (e.target->is("Start Level")) countdown.start();
//    else if (e.target->is("Stop Level")) countdown.stop();
}
//--------------------------------------------------------------
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{   }
//--------------------------------------------------------------
void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{   }
//--------------------------------------------------------------
void ofApp::drawCalibrationGUI(bool visible)
{
    gui->getFolder("Map Generation")->collapse();
    gui->getFolder("CV Settings")->collapse();
    gui->getFolder("Player")->collapse();
    gui->getFolder("Target")->collapse();
    gui->getFolder("Calibration")->expand();
}
//--------------------------------------------------------------
void ofApp::drawGenerationGUI(bool visible)
{
    gui->getFolder("Map Generation")->expand();
    gui->getFolder("CV Settings")->expand();
    gui->getFolder("Player")->collapse();
    gui->getFolder("Target")->collapse();
    gui->getFolder("Calibration")->collapse();
}
//--------------------------------------------------------------
void ofApp::drawOperationGUI(bool visible)
{
    gui->getFolder("Map Generation")->collapse();
    gui->getFolder("CV Settings")->collapse();
    gui->getFolder("Player")->collapse();
    gui->getFolder("Target")->collapse();
    gui->getFolder("Calibration")->collapse();
}
//--------------------------------------------------------------
void ofApp::drawEditorGUI(bool visible)
{
    gui->getFolder("Map Generation")->expand();
    gui->getFolder("CV Settings")->collapse();
    gui->getFolder("Player")->collapse();
    gui->getFolder("Target")->collapse();
    gui->getFolder("Calibration")->collapse();
}
//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    if(e.target->is("Select Level")) {
        _level = ofToInt(e.target->getLabel());
        Map m;
        m = mapGenerator.getMap(_difficulty, _level);
        feedBackMap = m.MapDetailsString().str();
//        countdown.setNewTimerLength(m.timeNeededToSolveMap);
//        targetCell.SpawnTarget(m.endPosition*3);
        mapGenerator.generateMap(m);
    }
    else if(e.target->is("App Mode")) {
        if (e.target->getLabel() == "CALIBRATION MODE") {
            _Appmode = 0;
            drawCalibrationGUI(false);
            displayWindow->doCalibration(true);
        }
        else if (e.target->getLabel() == "GENERATION MODE") {
            _Appmode = 1;
            drawGenerationGUI(false);
            displayWindow->doCalibration(false);
        }
        else if (e.target->getLabel() == "OPERATION MODE") {
            _Appmode = 2;
            drawOperationGUI(false);
            displayWindow->doCalibration(false);
        }
        else if (e.target->getLabel() == "EDITOR MODE") {
            _Appmode = 3;
            drawEditorGUI(false);
            displayWindow->doCalibration(false);
        }
    }
    else if(e.target->is("Select Difficulty")) {
        _difficulty = e.target->getLabel();
        if (_difficulty == "NOVICE") {
            _difficultyMode = 0;
            for (int i = 0; i < gui->getDropdown("Select Level")->size(); i++) {
                if (i < dLvs[0]) {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(true);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(true);
                }
                else {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(false);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(false);
                }
            }
        }
        else if (_difficulty == "ROOKIE") {
            _difficultyMode = 1;
            for (int i = 0; i < gui->getDropdown("Select Level")->size(); i++) {
                if (i < dLvs[1]) {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(true);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(true);
                }
                else {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(false);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(false);
                }
            }
        }
        else if (_difficulty == "NORMAL") {
            _difficultyMode = 2;
            for (int i = 0; i < gui->getDropdown("Select Level")->size(); i++) {
                if (i < dLvs[2]) {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(true);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(true);
                }
                else {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(false);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(false);
                }
            }
        }
        else if (_difficulty == "Hard") {
            _difficultyMode = 3;
            for (int i = 0; i < gui->getDropdown("Select Level")->size(); i++) {
                if (i < dLvs[3]) {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(true);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(true);
                }
                else {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(false);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(false);
                }
            }
        }
        else if (_difficulty == "Really Hard") {
            _difficultyMode = 4;
            for (int i = 0; i < gui->getDropdown("Select Level")->size(); i++) {
                if (i < dLvs[4]) {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(true);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(true);
                }
                else {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(false);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(false);
                }
            }
        }
        else if (_difficulty == "Impossible") {
            _difficultyMode = 5;
            for (int i = 0; i < gui->getDropdown("Select Level")->size(); i++) {
                if (i < dLvs[5]) {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(true);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(true);
                }
                else {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(false);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(false);
                }
            }
        }
        else if (_difficulty == "God Like") {
            _difficultyMode = 6;
            for (int i = 0; i < gui->getDropdown("Select Level")->size(); i++) {
                if (i < dLvs[6]) {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(true);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(true);
                }
                else {
                    gui->getDropdown("Select Level")->getChildAt(i)->setEnabled(false);
                    gui->getDropdown("Select Level")->getChildAt(i)->setVisible(false);
                }
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    
}
//--------------------------------------------------------------
void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    
}

