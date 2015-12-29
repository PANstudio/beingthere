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
    
    for(int i = 0; i < 10; i ++) {
        event[i] = "Player ";
    }
}
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("H.A.R.P.S");
    ofSetFullscreen(true);
    setupGUI();
    setupVariables();
    scoreBoard.loadScoreboard("scoreboard.json");
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
    mapGenerator.getPlayerCoordinates(playerManager.getPlayersCoords());
    ofDrawBitmapStringHighlight(feedBackMap, 508,13);
    
    // Player Status Feedback
    ofDrawBitmapStringHighlight("Player Status", 510,400);
    for (int i = 0; i < 3; i++) {
        ofDrawBitmapStringHighlight(event[i], 510,418+(i*18));
    }
    playerManager.drawPlayerManager();
    playerManager.drawPlayerHealth(680,415,0.5);
    ofDrawBitmapStringHighlight(countDown.getTimeLeft(), 508,480);
    scoreBoard.draw(508, 508);

    // Window Layout
    drawWindows();
}
//--------------------------------------------------------------
void ofApp::exit()
{
    // Delete GUI Objects
    delete gui;
    delete mapGui;
    delete cvGui;
    delete playerGui;
    delete targetGui;
    delete calibrationGui;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
        case OF_KEY_RETURN:
            drawGui = !drawGui;
            gui->setVisible(drawGui);
            break;
        case '1':
            drawMapGui = !drawMapGui;
            mapGui->setVisible(drawMapGui);
            break;
        case '2':
            drawCvGui = !drawCvGui;
            cvGui->setVisible(drawCvGui);
            break;
        case '3':
            drawPlayerGui = !drawPlayerGui;
            playerGui->setVisible(drawPlayerGui);
            break;
        case '4':
            drawTargetGui = !drawTargetGui;
            targetGui->setVisible(drawTargetGui);
            break;
        case '5':
            drawCalibrationGui = !drawCalibrationGui;
            calibrationGui->setVisible(drawCalibrationGui);
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
    for (int i = 0; i < 3; i++) {
        if (msg.message == ofToString(i)+": OK") {
            event[i] = "Player "+ofToString(i)+" OK";
            playerManager.stopReducingPlayerHealth(i);
        }
        else if (msg.message == ofToString(i)+": Danger") {
            event[i] = "Player "+ofToString(i)+" Danger";
        }
        else if (msg.message == ofToString(i)+": Deadly") {
            event[i] = "Player "+ofToString(i)+" Deadly";
            playerManager.startReducingPlayerHealth(i);
        }
        
        if (msg.message == ofToString(i)+" Reducer Finished" ) {
            playerManager.reducePlayerHealth(i, 5);
        }
    }
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
//--------------------------------------------------------------
void ofApp::drawWindows()
{
    ofPushMatrix();
    ofTranslate(500, 0);
    ofPushStyle();
    ofNoFill();
    ofSetColor(ofColor::ivory);
    ofDrawRectangle(0, 0, 400, 500);
    ofDrawRectangle(0, 500, 400, 200);
    ofPopStyle();
    ofPopMatrix();
}
//--------------------------------------------------------------
// *
// * GUI
// *
//--------------------------------------------------------------
void ofApp::setupGUI()
{
    
    drawMapGui = false;
    drawCvGui = false;
    drawPlayerGui = false;
    drawTargetGui = false;
    drawCalibrationGui = false;
    
    int spacing = 7;
    gui = new ofxDatGui(0,500);
    gui->addHeader("H_A_R_P_S");
    gui->addFRM(1.0f);
    gui->addBreak();
    
    gui->addBreak(spacing);
    vector<string> AppMode = {"CALIBRATION MODE",
        "EDITOR MODE",
        "GENERATION MODE",
        "OPERATION MODE"
    };
    
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
//    gui->addDropdown("Select Level", levels);
//    gui->getDropdown("Select Level")->select(0);

    gui->addBreak(spacing);
    gui->addMatrix("Levels", levels.size(),true);
    gui->getMatrix("Levels")->setRadioMode(true);

    gui->addBreak(spacing);
    gui->addButton("Start Level");
    gui->addButton("Stop Level");
    
    
    mapGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    mapGui->addHeader("Map Generation");
    mapGui->addSlider("Map Width", 0, 150, 100);
    mapGui->addSlider("Map Height", 0, 150, 100);
    mapGui->addSlider("Tile Size", 0.00, 100.00, 50);
    mapGui->addSlider("Offset Edge", 0, 100, 10);
    mapGui->addSlider("Random Seed", 0.00, 150.00, 3.14);
    mapGui->addSlider("Number of Obsticles", 0.00, 100.00, 20);
    mapGui->addSlider("Danger Area Size", 0, 25, 20);
    mapGui->addSlider("Smoothing Loops", 0, 25, 5);
    mapGui->addSlider("Growth Loops", 0, 25, 10);
    mapGui->addBreak(spacing);
    mapGui->addButton("Clear Map");
    mapGui->addBreak(spacing);
    mapGui->addButton("Generate Map");
    mapGui->addBreak(spacing);
    mapGui->addButton("Generate Custom Map");
    mapGui->addBreak(spacing);
    mapGui->addButton("Flush Map");
    
    cvGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    cvGui->addHeader("Computer Vision Settings");
    cvGui->addSlider("Green Threshold", 0,255,200);
    cvGui->addSlider("Yellow Threshold", 0,255,200);
    cvGui->addSlider("Red Threshold", 0,255,200);
    cvGui->addSlider("Blur Amount", 0, 21,9);
    cvGui->addSlider("Simplify Contour", 0.0, 5.0,0.5);
    
    playerGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    playerGui->addHeader("Player Settings");
    playerGui->addSlider("Player Size", 0,25, 10);
    playerGui->addColorPicker("Player Color");
    playerGui->addSlider("Player Pulse Rate", 0,250, 10);
    playerGui->addButton("Spawn New Start Posistion");
    
    targetGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    targetGui->addHeader("Target Settings");
    targetGui->addSlider("Target Size", 0,25, 10);
    targetGui->addColorPicker("Target Color");
    targetGui->addSlider("Target Pulse Rate", 0,250, 10);
    targetGui->addButton("Spawn New End Posistion");
    
    
    calibrationGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    calibrationGui->addHeader("Calibration Settings");
    calibrationGui->addToggle("From Centre / Top Left", false);
    calibrationGui->addSlider("Grid X", 0,100, 50); // This is CM
    calibrationGui->addSlider("Grid Y", 0,100, 50); // This is CM
    calibrationGui->addSlider("Spacing X", 0,200, 10); // This is CM
    calibrationGui->addSlider("Spacing Y", 0,200, 10); // This is CM
    calibrationGui->addSlider("Grid Offset X", 0,ofGetWidth(), 10); // This is CM
    calibrationGui->addSlider("Grid Offset Y", 0,ofGetHeight(), 10); // This is
    calibrationGui->addButton("Calibrate");

    setGuiListeners(gui);
    setGuiListeners(mapGui);
    setGuiListeners(cvGui);
    setGuiListeners(playerGui);
    setGuiListeners(targetGui);
    setGuiListeners(calibrationGui);
    
    mapGui->setVisible(false);
    cvGui->setVisible(false);
    playerGui->setVisible(false);
    targetGui->setVisible(false);
    calibrationGui->setVisible(false);
}
//--------------------------------------------------------------
void ofApp::setGuiListeners(ofxDatGui *guiRef)
{
    // Listeners
    guiRef->onButtonEvent(this, &ofApp::onButtonEvent);
    guiRef->onSliderEvent(this, &ofApp::onSliderEvent);
    guiRef->onTextInputEvent(this, &ofApp::onTextInputEvent);
    guiRef->on2dPadEvent(this, &ofApp::on2dPadEvent);
    guiRef->onDropdownEvent(this, &ofApp::onDropdownEvent);
    guiRef->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    guiRef->onMatrixEvent(this, &ofApp::onMatrixEvent);
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
    else if (e.target->is("Grid Offset X")) _gridX = e.target->getValue();
    else if (e.target->is("Grid Offset Y")) _gridY = e.target->getValue();
    else if (e.target->is("Grid X")) _numberOfXLines = e.target->getValue();
    else if (e.target->is("Grid Y")) _numberOfYLines = e.target->getValue();
    else if (e.target->is("Spacing X")) _spacingX = e.target->getValue();
    else if (e.target->is("Spacing Y")) _spacingY = e.target->getValue();
}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is("Generate Map")) {
        mapGenerator.generateMap(_width, _height,_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
    }
    else if (e.target->is("Flush Map")) {
        mapGenerator.update();
    }
    else if (e.target->is("Generate Custom Map")) {
        mapGenerator.generateCustomMap(_width, _height,_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
    }
    else if (e.target->is("Use Random Seed")) {
        _urs = e.target->getEnabled();
    }
    else if(e.target->is("Calibrate")) {
        displayWindow->setCalibration(_numberOfXLines, _numberOfYLines, _spacingX, _spacingY);
    }
    else if (e.target->is("Start Level")) {
        countDown.setNewTimerLength(ofRandom(10000));
        countDown.start();
    }
    else if (e.target->is("Stop Level")) {
        countDown.stop();
    }
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
//    gui->getFolder("Map Generation")->collapse();
//    gui->getFolder("CV Settings")->collapse();
//    gui->getFolder("Player")->collapse();
//    gui->getFolder("Target")->collapse();
//    gui->getFolder("Calibration")->expand();
}
//--------------------------------------------------------------
void ofApp::drawGenerationGUI(bool visible)
{
//    gui->getFolder("Map Generation")->expand();
//    gui->getFolder("CV Settings")->expand();
//    gui->getFolder("Player")->collapse();
//    gui->getFolder("Target")->collapse();
//    gui->getFolder("Calibration")->collapse();
}
//--------------------------------------------------------------
void ofApp::drawOperationGUI(bool visible)
{
//    gui->getFolder("Map Generation")->collapse();
//    gui->getFolder("CV Settings")->collapse();
//    gui->getFolder("Player")->collapse();
//    gui->getFolder("Target")->collapse();
//    gui->getFolder("Calibration")->collapse();
}
//--------------------------------------------------------------
void ofApp::drawEditorGUI(bool visible)
{
//    gui->getFolder("Map Generation")->expand();
//    gui->getFolder("CV Settings")->collapse();
//    gui->getFolder("Player")->collapse();
//    gui->getFolder("Target")->collapse();
//    gui->getFolder("Calibration")->collapse();
}
//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    if(e.target->is("App Mode")) {
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
            gui->getMatrix("Levels")->setVisible(dLvs[_difficultyMode]);
            gui->update();
        }
        else if (_difficulty == "ROOKIE") {
            _difficultyMode = 1;
            gui->getMatrix("Levels")->setVisible(dLvs[_difficultyMode]);
            gui->update();
        }
        else if (_difficulty == "NORMAL") {
            _difficultyMode = 2;
            gui->getMatrix("Levels")->setVisible(dLvs[_difficultyMode]);
            gui->update();
        }
        else if (_difficulty == "HARD") {
            _difficultyMode = 3;
            gui->getMatrix("Levels")->setVisible(dLvs[_difficultyMode]);
            gui->update();
        }
        else if (_difficulty == "REALLY HARD") {
            _difficultyMode = 4;
            gui->getMatrix("Levels")->setVisible(dLvs[_difficultyMode]);
            gui->update();
        }
        else if (_difficulty == "IMPOSSIBLE") {
            _difficultyMode = 5;
            gui->getMatrix("Levels")->setVisible(dLvs[_difficultyMode]);
            gui->update();
        }
        else if (_difficulty == "GOD LIKE") {
            _difficultyMode = 6;
            gui->getMatrix("Levels")->setVisible(dLvs[_difficultyMode]);
            gui->update();
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
    if(e.target->is("Levels")) {
        cout << e.child << endl;
        _level = e.child+1;
        Map m;
        m = mapGenerator.getMap(_difficulty, _level);
        feedBackMap = m.MapDetailsString().str();
        countDown.setNewTimerLength(m.timeNeededToSolveMap);
        mapGenerator.generateMap(m);
    }
}