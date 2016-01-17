#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setupVariables()
{
    _urs = false;
    _width = 100;
    _height = 100;
    _dangerAreaSize = 5;
    _rs = 3.13;
    _fillPercent = 5;
    _numberOfIslands = 10;
    _growthNo = 10;
    _smooth = 5;
    _offsetEdge = 5;
    _Appmode = 1;
    _numberOfXLines = 10;
    _numberOfYLines = 10;
    _spacingX = 10;
    _spacingY = 10;
    _showShaded = false;
    _iRR[0] = 25;
    _iRR[1] = 255;

    _iRY[0] = 25;
    _iRY[1] = 255;

    _iRG[0] = 25;
    _iRG[1] = 255;

    for(int i = 0; i < 10; i ++) {
        event[i] = "Player ";
    }
}
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("H.A.R.P.S");
    ofSetFullscreen(false);
    setupGUI();
    setupVariables();
    
    scoreBoard.loadScoreboard("scoreboard.json");
    scoreBoard.setup();
    
    mapGenerator.setup();
    mapGenerator.generateMap(50, 50, 0, 10, 25, 1, 3, 1.9, 3);
    
    playerManager.setup("localhost", 7890);
    playerManager.setNumberOfPlayers(3);
    playerManager.getFinderImage(mapGenerator.getFinderImage());
    
    countDown.setup(500, "Count Down", false, "ofxdatgui_assets/font-verdana.ttf");
    styledMap.setup(500,500);
}
//--------------------------------------------------------------
void ofApp::update()
{
    styledMap.update();
    countDown.update();
    playerManager.listen();
    displayWindow->setHealthBars(playerManager.getPlayerHealth());
    displayWindow->getTimeLeft(countDown.getTimeLeft());
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0, 0, 0);
    if (_Appmode == 0) {
        
    }
    else if (_Appmode == 1) {
        mapGenerator.drawEditor();
    }
    else if (_Appmode == 2) {
        mapGenerator.draw(false);
    }
    
    mapGenerator.drawComputerVision();
    mapGenerator.drawPolylines();

    mapGenerator.getPlayerCoordinates(playerManager.getPlayersCoords());
    playerManager.drawPlayerManager();
    playerManager.drawPlayerHealth(680,20,0.5);

    // Player Status Feedback
    ofDrawBitmapStringHighlight("Player Status", 510,13);
    for (int i = 0; i < 3; i++) {
        ofDrawBitmapString(event[i], 510,40+(i*60));
    }
    ofDrawBitmapStringHighlight(countDown.getTimeLeft(), 508,480);
    
    // Window Layout
    drawWindows();

    mapGenerator.drawFinderMap(500, 480);
    scoreBoard.draw(500, 500);
    
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
        case 'm':
            drawMapGui = !drawMapGui;
            mapGui->setVisible(drawMapGui);
            break;
        case 'v':
            drawCvGui = !drawCvGui;
            cvGui->setVisible(drawCvGui);
            break;
        case 't':
            drawTargetGui = !drawTargetGui;
            targetGui->setVisible(drawTargetGui);
            break;
        case 'p':
            drawPlayerGui = !drawPlayerGui;
            playerGui->setVisible(drawPlayerGui);
            break;
        case 'c':
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
    if (_Appmode == 1) {
        mapGenerator.mouseOver(x, y);
    }
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    if (_Appmode == 1) {
        mapGenerator.mouseDragged(x, y, button);
    }
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if (_Appmode == 1) {
        mapGenerator.mouseDown(x, y, button);
    }
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
    if (!drawMapGui) {
        ofDrawRectangle(0, 0, 400, 250);
        ofDrawRectangle(0, 250, 400, 300);
        ofDrawBitmapStringHighlight(feedBackMap, 5, 265);
    }
    else {
        ofDrawRectangle(0, 0, 400, mapGui->getHeight());
    }
    
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
    
    int spacing = 5;
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->setTheme(new ofxDatGuiThemeSmoke());
    gui->addHeader("H_A_R_P_S");
    gui->addFRM(10.0f);
    gui->addBreak();
    
    gui->addBreak();
    vector<string> AppMode = {"CALIBRATION MODE",
        "EDITOR MODE",
        "GENERATION MODE",
        "STYLE MODE",
        "OPERATION MODE"
    };
    
    gui->addDropdown("App Mode", AppMode);
    gui->getDropdown("App Mode")->select(0);
    gui->addBreak();
    
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

    gui->addBreak();
    gui->addMatrix("Levels", levels.size(),true);
    gui->getMatrix("Levels")->setRadioMode(true);

    gui->addBreak();
    gui->addToggle("Show Shaded Map");
    gui->addBreak();
    gui->addButton("Start Level");
    
    gui->addBreak();
    gui->addButton("Stop Level");
    
    mapGui = new ofxDatGui(501,0);
    mapGui->setTheme(new ofxDatGuiThemeSmoke());
    mapGui->setWidth(400);
    mapGui->addHeader("Map Generation");
    mapGui->addSlider("Map Width", 0, 100, 0);
    mapGui->addSlider("Map Height", 0, 100, 0);
    mapGui->addSlider("Tile Size", 0.00, 100.00, 0);
    mapGui->addSlider("Offset Edge", 0, 100, 0);
    mapGui->addSlider("Random Seed", 0.00, 2000.00, 0);
    mapGui->addSlider("Obsticles", 0.00, 100.00, 0);
    mapGui->addSlider("Danger Area Size", 0, 25, 0);
    mapGui->addSlider("Smoothing Loops", 0, 25, 0);
    mapGui->addSlider("Growth Loops", 0, 25, 0);
    mapGui->addBreak();
    mapGui->addButton("Clear Map");
    mapGui->addBreak();
    mapGui->addButton("Generate Map");
    mapGui->addBreak();
    mapGui->addButton("Generate Custom Map");
    mapGui->addBreak();
    mapGui->addButton("Flush Map");
    
    mapGui->addBreak();
    mapGui->addHeader("Save Settings");
    mapGui->addDropdown("Set Difficulty", difficulty);
    mapGui->addButton("Save");
    
    cvGui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    cvGui->setTheme(new ofxDatGuiThemeSmoke());
    cvGui->addHeader("Computer Vision Settings");
    cvGui->addSlider("Green Threshold", 0,255,200);
    cvGui->addSlider("Yellow Threshold", 0,255,200);
    cvGui->addSlider("Red Threshold", 0,255,200);
    
    cvGui->addSlider("Blur Amount", 0, 21,9);
    cvGui->addSlider("Simplify Contour", 0.0, 5.0,0.5);
    
    playerGui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    playerGui->setTheme(new ofxDatGuiThemeSmoke());
    playerGui->addHeader("Player Settings");
    playerGui->addSlider("Player Size", 0,25, 10);
    playerGui->addColorPicker("Player Color");
    playerGui->addSlider("Player Pulse Rate", 0,250, 10);
    playerGui->addButton("Spawn New Start Posistion");
    
    targetGui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    targetGui->setTheme(new ofxDatGuiThemeSmoke());
    targetGui->addHeader("Target Settings");
    targetGui->addSlider("Target Size", 0,25, 10);
    targetGui->addColorPicker("Target Color");
    targetGui->addSlider("Target Pulse Rate", 0,250, 10);
    targetGui->addButton("Spawn New End Posistion");
    
    
    calibrationGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    calibrationGui->setTheme(new ofxDatGuiThemeSmoke());
    calibrationGui->addHeader("Calibration Settings");
    calibrationGui->addToggle("From Centre / Top Left", false);
    calibrationGui->addSlider("Grid X", 0,100, 50); // This is CM
    calibrationGui->addSlider("Grid Y", 0,100, 50); // This is CM
    calibrationGui->addSlider("Spacing X", 0,200, 10); // This is CM
    calibrationGui->addSlider("Spacing Y", 0,200, 10); // This is CM
    calibrationGui->addSlider("Grid Offset X", 0,ofGetWidth(), 10); // This is CM
    calibrationGui->addSlider("Grid Offset Y", 0,ofGetHeight(), 10); // This is
    calibrationGui->addButton("Calibrate");
    
    
    // Set Element Colors
    gui->getButton("Start Level")->setStripeColor(ofColor::mediumSpringGreen);
    gui->getButton("Stop Level")->setStripeColor(ofColor::red);
    
    mapGui->getButton("Flush Map")->setStripeColor(ofColor::red);
    mapGui->getButton("Clear Map")->setStripeColor(ofColor::mediumPurple);
    mapGui->getButton("Generate Map")->setStripeColor(ofColor::red);
    
    cvGui->getSlider("Green Threshold")->setStripeColor(ofColor::green);
    cvGui->getSlider("Yellow Threshold")->setStripeColor(ofColor::yellow);;
    cvGui->getSlider("Red Threshold")->setStripeColor(ofColor::red);
    calibrationGui->getButton("Calibrate")->setStripeColor(ofColor::red);
    

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
    
    int offsetX = mapGui->getWidth();


    cvGui->setPosition(offsetX, (ofGetHeight()-cvGui->getHeight()));

    offsetX += cvGui->getWidth();
    
    targetGui->setPosition(offsetX, (ofGetHeight()-targetGui->getHeight()));
    
    offsetX += targetGui->getWidth();
    
    playerGui->setPosition(offsetX, (ofGetHeight()-playerGui->getHeight()));
    
    calibrationGui->setPosition(ofGetWidth()-calibrationGui->getWidth(),gui->getHeight());
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
    if (e.target->is("Map Width")) _width = e.target->getValue();
    else if (e.target->is("Map Height")) _height = e.target->getValue();
    else if (e.target->is("Offset Edge")) _offsetEdge = e.target->getValue();
    else if (e.target->is("Random Seed")) _rs = e.target->getValue();
    else if (e.target->is("Tile Size")) _fillPercent = e.target->getValue();
    else if (e.target->is("Obsticles")) _numberOfIslands = e.target->getValue();
    else if (e.target->is("Danger Area Size")) _dangerAreaSize = e.target->getValue();
    else if (e.target->is("Growth Loops")) _growthNo = e.target->getValue();
    else if (e.target->is("Smoothing Loops")) _smooth = e.target->getValue();
    else if (e.target->is("Grid Offset X")) _gridX = e.target->getValue();
    else if (e.target->is("Grid Offset Y")) _gridY = e.target->getValue();
    else if (e.target->is("Grid X")) _numberOfXLines = e.target->getValue();
    else if (e.target->is("Grid Y")) _numberOfYLines = e.target->getValue();
    else if (e.target->is("Spacing X")) _spacingX = e.target->getValue();
    else if (e.target->is("Spacing Y")) _spacingY = e.target->getValue();
    else if (e.target->is("Red Threshold")) _iRR[1] = e.target->getValue();
    else if (e.target->is("Yellow Threshold")) _iRY[1] = e.target->getValue();
    else if (e.target->is("Green Threshold")) _iRG[1] = e.target->getValue();
    else if (e.target->is("Blur Amount")) _blur = e.target->getValue();
    
}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is("Generate Map")) {
        mapGenerator.generateMap(_width, _height,_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
        playerManager.getFinderImage(mapGenerator.getFinderImage());
    }
    else if (e.target->is("Flush Map")) {
        mapGenerator.update(_blur,_iRR,_iRY,_iRG);
        styledMap.setShapes(mapGenerator.getDeadlyOutlines(),mapGenerator.getDangerOutlines());
    }
    else if (e.target->is("Generate Custom Map")) {
        mapGenerator.generateCustomMap(_width, _height,_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
        playerManager.getFinderImage(mapGenerator.getFinderImage());
    }
    else if (e.target->is("Use Random Seed")) {
        _urs = e.target->getEnabled();
    }
    else if (e.target->is("Show Shaded Map")) {
        _showShaded = e.target->getEnabled();
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
    else if(e.target->is("Save")) {
        Map m;
        m.width = _width;
        m.height = _height;
        m.difficulty = saveDifficultly;
        m.level = 1; //todo
        m.offsetEdge = _offsetEdge;
        m.tileSize = _fillPercent;
        m.numberOfClouds = _numberOfIslands;
        m.smoothingValue = _smooth;
        m.growthLoops = _growthNo;
        m.seedValue = _rs;
        m.dangerAreaSize = _dangerAreaSize;
        m.dangerAreaToxicity = 1; //todo
        m.deadAreaToxicity = 1; //todo
        m.timeNeededToSolveMap = 5000; //todp
        mapGenerator.saveMap(m);
    }
}
//--------------------------------------------------------------
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{   }
//--------------------------------------------------------------
void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{   }
//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    if(e.target->is("App Mode")) {
        if (e.target->getLabel() == "CALIBRATION MODE") {
            _Appmode = 0;
            cout << _Appmode << endl;
            displayWindow->doCalibration(true);
        }
        else if (e.target->getLabel() == "EDITOR MODE") {
            _Appmode = 1;
            cout << _Appmode << endl;
            displayWindow->doCalibration(false);
        }
        else if (e.target->getLabel() == "GENERATION MODE") {
            _Appmode = 2;
            cout << _Appmode << endl;
            displayWindow->doCalibration(false);
        }
        else if (e.target->getLabel() == "OPERATION MODE") {
            _Appmode = 3;
            cout << _Appmode << endl;
            displayWindow->doCalibration(false);
        }
        
//        else if (e.target->getLabel() == "OPERATION MODE") {
//            
//        }
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
    else if(e.target->is("Set Difficulty")) {
        saveDifficultly = e.target->getLabel();
        if (saveDifficultly == "NOVICE") {

        }
        else if (_difficulty == "ROOKIE") {
           
        }
        else if (_difficulty == "NORMAL") {
           
        }
        else if (_difficulty == "HARD") {
           
        }
        else if (_difficulty == "REALLY HARD") {
           
        }
        else if (_difficulty == "IMPOSSIBLE") {
           
        }
        else if (_difficulty == "GOD LIKE") {
           
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
        playerManager.getFinderImage(mapGenerator.getFinderImage());
    }
}