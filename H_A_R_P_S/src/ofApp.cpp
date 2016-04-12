#include "ofApp.h"
#pragma mark - OF Methods
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("H.A.R.P.S");
    ofSetFullscreen(true);
    
    // This is independant of other setup routines so can be called before the gui
    styledMap.setup();

    setupGUI();
    setupVariables();
    setupOperationsButton();
        
    scoreBoard.loadScoreboard("scoreboard.json");
    scoreBoard.setup();
    
    mapGenerator.setup();
    mapGenerator.generateNewMap(100,100,3, 5, 20, 3, 4, 3.13, 5);
    styledMap.getMapImage(mapGenerator.getSmoothMap());
    
    playerManager.setup("localhost", 7890);
    playerManager.setNumberOfPlayers(3);
    
    if (mapGenerator.getFinderImage().isAllocated()) {
        playerManager.getFinderImage(mapGenerator.getSmoothMap());
    }
    
    countDown.setup(500, "Count Down", false);
    setupListeners();
}
//--------------------------------------------------------------
void ofApp::update()
{
    startLevel->update();
    stopLevel->update();
    resetLevel->update();
    fpsIndicator->update();
    appMode->update();
    difficultyBar->update();
    levelSelect->update();
    
    if (!appMode->getIsExpanded()) {
        appMode->setPosition(0, ofGetHeight()-appMode->getHeight());
    }
    else {
        appMode->setPosition(0, ofGetHeight()-appMode->getHeight());
    }
    
    view->update();
    styledMap.update();
    countDown.update();
    
    playerManager.listen();
    displayWindow->setHealthBars(playerManager.getPlayerHealth());
    displayWindow->getTimeLeft("");
    
    if (countDown.getTimeLeft() <= 10000) {
        displayWindow->setTimerColors(ofColor::red, 25);
    }
    else {
        displayWindow->setTimerColors(ofColor::green, 25);
    }
    
    if(mapGenerator.isAnimating()) {
        mapGenerator.animate();
    }
    
    displayWindow->calibrationScreen.setGridSpacing(_spacingX, _spacingY);
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0, 0, 0);
    
    switch (_Appmode) {
        case 0:
            drawCalibrationMode();
            break;
        case 1:
            drawEditorMode();
            break;
        case 2:
            drawGeneratorMode();
            break;
        case 3:
            drawOperationMode();
            break;
        default:
            break;
    }

    ofSetColor(ofColor::white);
    heading.drawString(mode, 15, 530);
 
    // Window Layout
//    drawWindows();
    
    fpsIndicator->draw();
    appMode->draw();
    title->draw();
}
//--------------------------------------------------------------
void ofApp::exit()
{
    displayWindow->close();
    // Delete GUI Objects
    delete gui;
    delete mapGui;
    delete calibrationGui;
    delete view;
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
        case 'o':
            drawOperationalElementsGui = !drawOperationalElementsGui;
            operationElements->setVisible(drawOperationalElementsGui);
            break;
        case 'c':
            drawCalibrationGui = !drawCalibrationGui;
            calibrationGui->setVisible(drawCalibrationGui);
            break;
        case ' ':
            mapGenerator.reGenerateClouds();
//            displayWindow->calibrationScreen.saveCalibrationData();
//            displayWindow->setupSegmentDisplay();
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
    scoreBoard.mouseOver(x, y);
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    if (_Appmode == 1) {
        mapGenerator.mouseDragged(x, y, button);
    }
    scoreBoard.mouseDown(x, y, button);
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if (_Appmode == 1) {
        mapGenerator.mouseDown(x, y, button);
    }
    scoreBoard.mouseDown(x, y, button);
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

}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
#pragma mark - OF Methods
//--------------------------------------------------------------
// *
// *
// *
//--------------------------------------------------------------
void ofApp::drawWindows()
{
    ofPushMatrix();
    ofTranslate(500, 0);
    ofPushStyle();
    ofNoFill();
    ofSetColor(ofColor::white);
    if (_Appmode == 1) {
        ofDrawRectangle(0, 0, 400, 175);
        ofDrawBitmapStringHighlight("Editors",7,160);
        ofDrawRectangle(0, 175, 400, 325);
    }
    else if (_Appmode == 2) {
        ofDrawRectangle(0, 0, 400, 145);
        ofDrawBitmapStringHighlight("Computer Vision",7,130);
        ofDrawRectangle(0, 145, 400, 355);
    }
    else if (_Appmode == 3) {
        ofDrawRectangle(0, 0, 400, 250);
        ofDrawRectangle(0, 250, 400, 250);
        ofDrawBitmapString(feedBackMap, 5, 265);
    }
    ofPopStyle();
    ofPopMatrix();
}
#pragma mark - Setup Listeners
//--------------------------------------------------------------
// *
// * Listeners
// *
//--------------------------------------------------------------
void ofApp::setupListeners()
{
    ofAddListener(countDown.timerStarted, this, &ofApp::countDownStarted);
    ofAddListener(countDown.timerFinished, this, &ofApp::countDownFinished);
    ofAddListener(mapGenerator.eventListener, this, &ofApp::getMapEvent);
    ofAddListener(playerManager.reducerTimer[0].timerFinished, this, &ofApp::reduceHealth);
}
//--------------------------------------------------------------
void ofApp::removeListeners()
{
    ofRemoveListener(countDown.timerStarted, this, &ofApp::countDownStarted);
    ofRemoveListener(countDown.timerFinished, this, &ofApp::countDownFinished);
    ofRemoveListener(mapGenerator.eventListener, this, &ofApp::getMapEvent);
    ofRemoveListener(playerManager.reducerTimer[0].timerFinished, this, &ofApp::reduceHealth);
}
//--------------------------------------------------------------
void ofApp::countDownStarted(string &str)
{
    cout << "Count Down Started  " << str << endl;
}
//--------------------------------------------------------------
void ofApp::countDownFinished(string &str)
{
    cout << "Count Down Finished " << str << endl;
}
//--------------------------------------------------------------
void ofApp::getMapEvent(struct event &ev)
{
    cout << ev.id << " " << ev.area << endl;
    for (int i = 0; i < 3; i++) {
        if (ev.id == ofToString(i)) {
            if (ev.area == "OK") {
                event[i] = "Player "+ofToString(i)+" OK";
                playerManager.stopReducingPlayerHealth(i);
            }
            else if (ev.area == "Danger") {
                event[i] = "Player "+ofToString(i)+" Danger";
                //                playerManager.stopReducingPlayerHealth(i);
            }
            else if (ev.area == "Deadly") {
                event[i] = "Player "+ofToString(i)+" Deadly";
                playerManager.startReducingPlayerHealth(i);
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::reduceHealth(string &ev)
{
    cout << ev << endl;
    for (int i = 0; i < 3; i++) {
        if (ev == ofToString(i)+" Reducer Finished" ) {
            playerManager.reducePlayerHealth(i, 5);
        }
    }
}
#pragma mark - Draw
//--------------------------------------------------------------
// *
// * Draw Modes
// *
//--------------------------------------------------------------
void ofApp::drawCalibrationMode()
{
    mode = "Calibration Mode";
    if (_showPreviewWindow) {
        ofPushMatrix();
        ofPushStyle();
        displayWindow->drawPreview(500, 500);
        ofPopStyle();
        ofPopMatrix();
    }
    displayWindow->calibrationScreen.drawSpreadsheet();
    displayWindow->calibrationScreen.drawCurrentReadings(350, 500);
}
//--------------------------------------------------------------
void ofApp::drawEditorMode()
{
    mode = "Editor Mode";
    ofPushStyle();
    ofNoFill();
    ofSetColor(ofColor::white);
    ofDrawRectangle(500, 0, 400, 175);
    ofPopStyle();
    mapGenerator.drawEditor();
    styledMap.draw(500, 250, 250, 250);
}
//--------------------------------------------------------------
void ofApp::drawGeneratorMode()
{
    mode = "Generator Mode";
    ofDrawRectangle(500, 0, 400, 145);
    ofDrawBitmapStringHighlight("Computer Vision",7,130);
    mapGenerator.draw(false);
    mapGenerator.drawComputerVision(500,0);
    mapGenerator.getPlayerCoordinates(playerManager.getPlayersCoords());
    styledMap.draw(500, 250, 250, 250);
}
//--------------------------------------------------------------
void ofApp::drawOperationMode()
{
    mapGenerator.drawFinderMap(901, 0);
    styledMap.draw(0, 0);

    // Player Status Feedback
    ofDrawBitmapStringHighlight("Player Status", 510,13);
    for (int i = 0; i < 3; i++) {
        ofDrawBitmapString(event[i], 510,40+(i*60));
    }
    ofDrawBitmapStringHighlight(countDown.getTimeLeftStr(), 508,480);
    mapGenerator.getPlayerCoordinates(playerManager.getPlayersCoords());
    
    playerManager.drawPlayerManager();
    playerManager.drawPlayerHealth(680,20,0.5);
    
    if (_showPreviewWindow) {
        ofPushMatrix();
        ofPushStyle();
        displayWindow->drawPreview(500, 500);
        ofPopStyle();
        ofPopMatrix();
    }
    // Draw Style Selector
    view->draw();
    styledMap.drawGradients(view->getX(), view->getY()-50);
    startLevel->draw();
    stopLevel->draw();
    resetLevel->draw();
    difficultyBar->draw();
    levelSelect->draw();
}
#pragma mark - GUI Setup
//--------------------------------------------------------------
// *
// * GUI
// *
//--------------------------------------------------------------
void ofApp::setupGUI()
{
    drawOperationalElementsGui = false;
    drawCalibrationGui = false;
    
    int spacing = 5;
    gui = new ofxDatGui(0,550);
    
    
    
    
    mapGenerator.loadMaps("config.json");

    
    gui->addButton("Flush Map");
    gui->addBreak();
    
    gui->addToggle("Show Preview Window");
    gui->addBreak();
    
    mapGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    mapGui->setWidth(350);
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

    ofxDatGuiFolder* vision = mapGui->addFolder("Vision",ofColor::beige);
    vision->addSlider("Green Threshold", 0,255,200);
    vision->addSlider("Yellow Threshold", 0,255,200);
    vision->addSlider("Red Threshold", 0,255,200);
    vision->addSlider("Blur Amount", 0, 21,9);
    vision->addSlider("Simplify Contour", 0.0, 5.0,0.5);
    mapGui->addBreak();
    
    mapGui->addButton("Clear Map");
    mapGui->addBreak();
    mapGui->addButton("Generate Map");
    mapGui->addBreak();
    mapGui->addButton("Generate Custom Map");
    mapGui->addBreak();
    mapGui->addButton("Animate Map");
    mapGui->addBreak();
    mapGui->addButton("Generate New Map");
    mapGui->addBreak();
    mapGui->addHeader("Save Settings");
    mapGui->addButton("Save");
    
    operationElements = new ofxDatGui(901,300);
    operationElements->setWidth(250);
    operationElements->addHeader("Operational");
    operationElements->addDropdown("Map Style", styledMap.getGradientsNames());
    
    ofxDatGuiFolder * player = operationElements->addFolder("Player");
    player->addSlider("Player Size", 0,25, 10);
    player->addColorPicker("Player Color");
    player->addSlider("Player Pulse Rate", 0,250, 10);
    player->addButton("Spawn New Start Posistion");
    ofxDatGuiFolder * target = operationElements->addFolder("Target");
    target->addSlider("Target Size", 0,25, 10);
    target->addColorPicker("Target Color");
    target->addSlider("Target Pulse Rate", 0,250, 10);
    target->addButton("Spawn New End Posistion");
    
    
    calibrationGui = new ofxDatGui(501,250);
    calibrationGui->addHeader("Calibration Settings");
    calibrationGui->addToggle("From Centre / Top Left", false);
    calibrationGui->add2dPad("Calibration Nodes", ofRectangle(0, 0, 500, 500));
    calibrationGui->addSlider("Spacing X", 0,200, 50); // This is CM
    calibrationGui->addSlider("Spacing Y", 0,200, 50); // This is CM
    calibrationGui->addButton("Calibrate");
    
    
    // Set Element Colors
    gui->getButton("Start Level")->setStripeColor(ofColor::mediumSpringGreen);
    gui->getButton("Stop Level")->setStripeColor(ofColor::red);
    
    mapGui->getButton("Flush Map")->setStripeColor(ofColor::red);
    mapGui->getButton("Clear Map")->setStripeColor(ofColor::mediumPurple);
    mapGui->getButton("Generate Map")->setStripeColor(ofColor::red);
    
    mapGui->getSlider("Green Threshold")->setStripeColor(ofColor::green);
    mapGui->getSlider("Yellow Threshold")->setStripeColor(ofColor::yellow);;
    mapGui->getSlider("Red Threshold")->setStripeColor(ofColor::red);
    calibrationGui->getButton("Calibrate")->setStripeColor(ofColor::red);
    

    view = new ofxDatGuiScrollView("Styles", 8);
    view->setWidth(250);
    view->setPosition((gui->getPosition().x+gui->getWidth()), gui->getPosition().y+50);
    view->onScrollViewEvent(this, &ofApp::onScrollViewEvent);
    for(int i = 0; i < styledMap.getGradientsNames().size(); i++) {
        view->add(styledMap.getGradientsNames()[i]);
    }
    
    setGuiListeners(gui);
    setGuiListeners(mapGui);
    setGuiListeners(operationElements);
    setGuiListeners(calibrationGui);

    mapGui->setVisible(false);
    operationElements->setVisible(false);
    calibrationGui->setVisible(false);
    
    gui->getDropdown("Select Difficulty")->select(0);
    gui->getDropdown("Select Difficulty")->collapse();
}
//--------------------------------------------------------------
void ofApp::setupOperationsButton()
{

    vector<string> AppMode = {"CALIBRATION MODE",
        "EDITOR MODE",
        "GENERATION MODE",
        "STYLE MODE",
        "OPERATION MODE"
    };
    
    title = new ofxDatGuiLabel("Hapilee");
    appMode = new ofxDatGuiDropdown("App Mode",AppMode);
    appMode->expand();
    
    startLevel = new ofxDatGuiButton("Start Level");
    stopLevel = new ofxDatGuiButton("Stop Level");
    resetLevel = new ofxDatGuiButton("Reset Level");
    fpsIndicator = new ofxDatGuiFRM();
    
    
    vector<string> difficulty;
    for(int i = 0; i < mapGenerator.getMapsInfo().size(); i++) {
        difficulty.push_back(mapGenerator.getMapsInfo()[i].Difficulty);
        dLvs.push_back(mapGenerator.getMapsInfo()[i].numberOfLevels);
    }
    
    difficultyBar = new ofxDatGuiDropdown("Select Difficulty", difficulty);
    difficultyBar->setStripe(ofColor::orange, 5);
    difficultyBar->setPosition(500+300, 0);
    difficultyBar->setWidth(250);
    
    
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

    levelSelect = new ofxDatGuiMatrix("Levels",levels.size(),true);
    levelSelect->setRadioMode(true);
    levelSelect->setPosition(500+300+difficultyBar->getWidth(), 0);
    levelSelect->onMatrixEvent(this, &ofApp::onMatrixEvent);
    
    appMode->setWidth(200);
    startLevel->setWidth(200);
    stopLevel->setWidth(200);
    resetLevel->setWidth(200);
    title->setStripe(ofColor::mediumSlateBlue, 5);
    title->setWidth(200);
    fpsIndicator->setWidth(200, 100);
    fpsIndicator->setStripeVisible(false);
    
    
    int height = ofGetHeight();
    
    title->setPosition(ofGetWidth()-(fpsIndicator->getWidth()+title->getWidth()), height-fpsIndicator->getHeight());
    appMode->setPosition(0, height-appMode->getHeight());
    startLevel->setPosition(appMode->getWidth(), height-startLevel->getHeight());
    stopLevel->setPosition(startLevel->getX()+startLevel->getWidth(), height-stopLevel->getHeight());
    resetLevel->setPosition(stopLevel->getX()+stopLevel->getWidth(), height-resetLevel->getHeight());
    fpsIndicator->setPosition(ofGetWidth()-fpsIndicator->getWidth(), height-fpsIndicator->getHeight());
    
    startLevel->setStripe(ofColor::mediumSpringGreen, 5);
    stopLevel->setStripe(ofColor::red, 5);
    
    startLevel->onButtonEvent(this, &ofApp::onButtonEvent);
    stopLevel->onButtonEvent(this, &ofApp::onButtonEvent);
    resetLevel->onButtonEvent(this, &ofApp::onButtonEvent);
    appMode->onDropdownEvent(this, &ofApp::onDropdownEvent);
    difficultyBar->onDropdownEvent(this, &ofApp::onDropdownEvent);
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
#pragma mark - GUI Listeners
//--------------------------------------------------------------
// *
// *    GUI Listeners
// *
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
        mapGenerator.generateMap(_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
        playerManager.getFinderImage(mapGenerator.getSmoothMap());
        styledMap.getMapImage(mapGenerator.getSmoothMap());
        displayWindow->setMapImage(styledMap.getStyledMap());
    }
    else if (e.target->is("Flush Map")) {
        mapGenerator.generatePolylines(_blur,_iRR[1],_iRY[1],_iRG[1]);
    }
    else if (e.target->is("Generate Custom Map")) {
        mapGenerator.generateCustomMap(_smooth,_growthNo,_dangerAreaSize);
        playerManager.getFinderImage(mapGenerator.getSmoothMap());
        styledMap.getMapImage(mapGenerator.getSmoothMap());
        displayWindow->setMapImage(styledMap.getStyledMap());
    }
    else if (e.target->is("Animate Map")) {
        mapGenerator.startAnimation(_numberOfIslands,_smooth,_growthNo,_rs);
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
        countDown.setNewTimerLength(ofRandom(10000,60000));
        countDown.start();
    }
    else if (e.target->is("Stop Level")) {
        countDown.stop();
    }
    else if (e.target->is("Clear Map")) {
        mapGenerator.clearMap();
    }
    else if (e.target->is("Show Preview Window")) {
        _showPreviewWindow = e.target->getEnabled();
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
{
    if (e.target->is("Calibration Nodes")) {
        displayWindow->calibrationScreen.moveNodes(e.x, e.y);
    }
}
//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    if(e.target->is("App Mode")) {
        if (e.target->getLabel() == "CALIBRATION MODE") {
            _Appmode = 0;
            mode = "Calibration Mode";
            mapGui->setVisible(false);
            displayWindow->doCalibration(true);
        }
        else if (e.target->getLabel() == "EDITOR MODE") {
            _Appmode = 1;
            mode = "Editor Mode";
            mapGui->setVisible(false);
            displayWindow->doCalibration(false);
        }
        else if (e.target->getLabel() == "GENERATION MODE") {
            _Appmode = 2;
            mode = "Generation Mode";
            displayWindow->doCalibration(false);
            mapGui->setVisible(true);
        }
        else if (e.target->getLabel() == "OPERATION MODE") {
            mode = "Operation Mode";
            _Appmode = 3;
            mapGui->setVisible(false);
            displayWindow->doCalibration(false);
        }
    }
    else if(e.target->is("Select Difficulty")) {
        _difficulty = e.target->getLabel();
        if (_difficulty == "NOVICE") {
            _difficultyMode = 0;
            levelSelect->setVisible(dLvs[_difficultyMode]);

        }
        else if (_difficulty == "ROOKIE") {
            _difficultyMode = 1;
            levelSelect->setVisible(dLvs[_difficultyMode]);
        }
        else if (_difficulty == "NORMAL") {
            _difficultyMode = 2;
            levelSelect->setVisible(dLvs[_difficultyMode]);
        }
        else if (_difficulty == "HARD") {
            _difficultyMode = 3;
            levelSelect->setVisible(dLvs[_difficultyMode]);
        }
        else if (_difficulty == "REALLY HARD") {
            _difficultyMode = 4;
            levelSelect->setVisible(dLvs[_difficultyMode]);
        }
        else if (_difficulty == "IMPOSSIBLE") {
            _difficultyMode = 5;
            levelSelect->setVisible(dLvs[_difficultyMode]);
        }
        else if (_difficulty == "GOD LIKE") {
            _difficultyMode = 6;
            levelSelect->setVisible(dLvs[_difficultyMode]);
        }
    }
    else if(e.target->is("Set Difficulty")) {
        saveDifficultly = e.target->getLabel();
    }
    else if(e.target->is("Map Style")) {
        cout << styledMap.getGradientsNames()[e.child] << endl;
        styledMap.setGradient(styledMap.getGradientsNames()[e.child]);
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
        playerManager.getFinderImage(mapGenerator.getSmoothMap());
        styledMap.getMapImage(mapGenerator.getSmoothMap());
        displayWindow->setMapImage(styledMap.getStyledMap());
    }
}
//--------------------------------------------------------------
void ofApp::onScrollViewEvent(ofxDatGuiScrollViewEvent e)
{
    cout << styledMap.getGradientsNames()[e.index] << endl;
    styledMap.setGradient(styledMap.getGradientsNames()[e.index]);
}
//--------------------------------------------------------------
void ofApp::setupVariables()
{
    _urs = false;
    _showPreviewWindow = false;
    _width = 100;
    _height = 100;
    _dangerAreaSize = 5;
    _rs = 3.13;
    _fillPercent = 5;
    _numberOfIslands = 10;
    _growthNo = 10;
    _smooth = 5;
    _offsetEdge = 5;
    _Appmode = 3;
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
    heading.load("ofxdatgui_assets/font-verdana.ttf",20);
}

