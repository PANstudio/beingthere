#include "ofApp.h"
#pragma mark - OF Methods
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("Happilee");
    ofSetFullscreen(false);
    ofSetVerticalSync(true);
    
    // This is independant of other setup routines so can be called before the gui
    styledMap.setup();

    robotManager.loadCommands();
    
    setupCommandsGui(robotManager.getCommands());
    
    
    setupGuis();
    setupVariables();
    setupDirectoryWatcher();
    
    robotManager.setup();
    
    scoreBoard.loadScoreboard("scoreboard.json");
    scoreBoard.setup();
    
    mapGenerator.setup();
    mapGenerator.setGreenThreshold(64);
    mapGenerator.setRedThreshold(128);
    
    mapGenerator.generateNewMap(100,100,3, 5, 20, 3, 4, 3.13, 5);

    styledMap.getMapImage(mapGenerator.getSmoothMap());
    
    playerManager.setup("localhost", 7890);
    playerManager.setNumberOfPlayers(1);
    
    if (mapGenerator.getFinderImage().isAllocated()) {
        playerManager.getFinderImage(mapGenerator.getSmoothMap());
    }
    
    for (int i = 0; i < 3; i++) {
        bUnitMalfunctioned[i] = false;
    }
    
    countDown.setup(500, "Count Down", false);
    setupListeners();
    
    mapViewer.setup();
    splashScreen.load();
    server.setup();
}
//--------------------------------------------------------------
void ofApp::update()
{
    updateGui();
    
    
    styledMap.update();
    
    server.update(2048);
    splashScreen.update();
    mapGenerator.updateCV(lRT, lGT);
    
    playerManager.listen();
//    displayWindow->setHealthBars(playerManager.getPlayerHealth());

//    ofFbo f;
//    f.getTexture().getTextureData().bFlipTexture =
    
//    if (countDown.getTimeLeft() <= 10000) {
//        displayWindow->setTimerColors(ofColor::red, 25);
//    }
//    else {
//        displayWindow->setTimerColors(ofColor::green, 25);
//    }
    
    if(mapGenerator.isAnimating()) {
        mapGenerator.animate();
    }
    
//    displayWindow->calibrationScreen.setGridSpacing(_spacingX, _spacingY);

    countDown.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
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
        case 4:
            mapViewer.draw();
            break;
        default:
            break;
    }
    fpsIndicator->draw();
    appMode->draw();
    title->draw();
    showSecondWindow->draw();
    
    playerManager.drawDebug();
//    string statusStr =  "status: " + server.getStateStr();
//    statusStr += " -- sent "+ofToString(server.getPctSent(), 2)+"%";
//    
//    ofSetColor(255, 0, 255);
//    ofDrawBitmapString(statusStr, 510,520);
    
    if (!splashScreen.isDone()) {
        splashScreen.draw();
    }
  
}
//--------------------------------------------------------------
void ofApp::exit()
{
//    displayWindow->close();
    // Delete GUI Objects
    delete view;
    mapViewer.close();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
        case OF_KEY_RETURN:
            drawGui = !drawGui;
            break;
        case 'm':
            drawMapGui = !drawMapGui;
            break;
        case 'o':
            drawOperationalElementsGui = !drawOperationalElementsGui;
            break;
        case 'c':
            drawCalibrationGui = !drawCalibrationGui;
            break;
        case '1':
            robotManager.fireCommand(0, HPL_GREEN_ZONE);
            break;
        case '2':
            robotManager.fireCommand(0, HPL_YELLOW_ZONE);
            break;
        case '3':
            robotManager.fireCommand(0, HPL_RED_ZONE);
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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY )
{
    switch (_Appmode) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            mapViewer.scroll(scrollY);
            break;
        default:
            break;
    }
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
    for (int i = 0; i < 3; i++) {
        if (ev.id == ofToString(i)) {
//            switch (ev.area) {
//                case <#constant#>:
//                    <#statements#>
//                    break;
//                    
//                default:
//                    break;
//            }
            
            
//            if (previousState[i] != ev.area) {
            if (!bUnitMalfunctioned[i]) {
                if (ev.area == "OK") {
                    event[i] = "Player "+ofToString(i)+" OK";
                    playerManager.stopReducingPlayerHealth(i);
                    robotManager.fireCommand(i, HPL_GREEN_ZONE);
                }
                else if (ev.area == "Danger") {
                    event[i] = "Player "+ofToString(i)+" Danger";
                    robotManager.fireCommand(i, HPL_YELLOW_ZONE);
                }
                else if (ev.area == "Deadly") {
                    if (playerManager.getPlayerHealth()[i].noHealth()) {
                        event[i] = "Player "+ofToString(i)+" Malfunction";
                        robotManager.fireCommand(i, HPL_MALFUNCTION);
                        bUnitMalfunctioned[i] = true;
                    }
                    else {
                        event[i] = "Player "+ofToString(i)+" Deadly";
                        playerManager.startReducingPlayerHealth(i);
                    }
                }
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::reduceHealth(string &ev)
{
    for (int i = 0; i < 3; i++) {
        if (ev == ofToString(i)+" Reducer Finished" ) {
            playerManager.reducePlayerHealth(i, 5);
            robotManager.fireCommand(i, HPL_RED_ZONE);
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
//        displayWindow->drawPreview(500, 500);
        ofPopStyle();
        ofPopMatrix();
    }
//    displayWindow->calibrationScreen.drawSpreadsheet();
//    displayWindow->calibrationScreen.drawCurrentReadings(0, 525);
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
    styledMap.getMapImage(mapGenerator.getSmoothMap());
    styledMap.draw(ofGetWidth()-500, 0,500, 500);
    drawEditorGui();
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
    styledMap.draw(500, 500, 250, 250);
    drawGeneratorGui();
}
//--------------------------------------------------------------
void ofApp::drawOperationMode()
{
    ofSetColor(255,255);
    styledMap.draw(0, 0);

    // Player Status Feedback
    ofDrawBitmapStringHighlight("Player Status", 230,520);
    for (int i = 0; i < 3; i++) {
        ofDrawBitmapString(event[i], 230,535+(i*60));
    }
    
//    ofDrawBitmapStringHighlight(countDown.getTimeLeftStr(), 508,480);
    mapGenerator.getPlayerCoordinates(playerManager.getPlayersCoords());
    
    playerManager.drawPlayerManager();
    playerManager.drawPlayerHealth(15,520,0.5);
    
    if (_showPreviewWindow) {
        ofPushMatrix();
        ofPushStyle();
//        displayWindow->drawPreview(510, view->getY()+view->getHeight());
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
    saveMapRecord->draw();
    scaleX->draw();
    scaleY->draw();
    
    for (int i = 0; i < commands.size(); i++) {
        commands[i]->draw();
    }
    
    robotManager.draw(500, 500);
    
    mapMesh.draw();
}
#pragma mark - Directory Watcher
//--------------------------------------------------------------
// *
// * Directory Watcher
// *
//--------------------------------------------------------------
void ofApp::setupDirectoryWatcher()
{
    watcher.registerAllEvents(this);
    std::string folderToWatch = ofToDataPath("tempMaps", true);
    bool listExistingItemsOnStart = false;
    
    watcher.addPath(folderToWatch, listExistingItemsOnStart, &fileFilter);
}
//--------------------------------------------------------------
void ofApp::onDirectoryWatcherItemAdded(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt)
{
    ofLogNotice() << "Added: " << evt.item.path();
}
//--------------------------------------------------------------
void ofApp::onDirectoryWatcherItemRemoved(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt)
{
    ofLogNotice() << "Removed: " << evt.item.path();
}
//--------------------------------------------------------------
void ofApp::onDirectoryWatcherItemModified(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt)
{
    ofLogNotice() << "Modified: " << evt.item.path();
    latestMap = evt.item.path();
}
//--------------------------------------------------------------
void ofApp::onDirectoryWatcherItemMovedFrom(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt)
{
    ofLogNotice("ofApp::onDirectoryWatcherItemMovedFrom") << "Moved From: " << evt.item.path();
}
//--------------------------------------------------------------
void ofApp::onDirectoryWatcherItemMovedTo(const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt)
{
    ofLogNotice("ofApp::onDirectoryWatcherItemMovedTo") << "Moved To: " << evt.item.path();
}
//--------------------------------------------------------------
void ofApp::onDirectoryWatcherError(const Poco::Exception& exc)
{
    ofLogError("ofApp::onDirectoryWatcherError") << "Error: " << exc.displayText();
}
#pragma mark - GUI Setup
//--------------------------------------------------------------
// *
// * GUI
// *
//--------------------------------------------------------------
void ofApp::setupGuis()
{
    drawOperationalElementsGui = false;
    drawCalibrationGui = false;
    
    int spacing = 5;
    mapGenerator.loadMaps("config.json");
    setupOperationsGui();
    setupGeneratorGui();

    view = new ofxDatGuiScrollView("Styles", 8);
    view->setWidth(250);
    view->setPosition(ofGetWidth()-250,125);
    view->onScrollViewEvent(this, &ofApp::onScrollViewEvent);
    for(int i = 0; i < styledMap.getGradientsNames().size(); i++) {
        view->add(styledMap.getGradientsNames()[i]);
    }
}
//--------------------------------------------------------------
void ofApp::setupCommandsGui(map<int,cmds> _commands)
{
    int y = 0;
    for (int i = 0; i < _commands.size(); i++) {
        ofxDatGuiButton * cmdBtn;
        cmdBtn = new ofxDatGuiButton(_commands.at(i).cmdname);
        cmdBtn->setPosition(501,y);
        cmdBtn->setWidth(300);
        y += cmdBtn->getHeight();
        cmdBtn->onButtonEvent(this, &ofApp::onButtonEvent);
        commands.push_back(cmdBtn);
    }
}
//--------------------------------------------------------------
void ofApp::drawGeneratorGui()
{
    for (int i = 0; i < genComponents.size(); i++) {
        genComponents[i]->draw();
    }
}
//--------------------------------------------------------------
void ofApp::drawEditorGui()
{
    genComponents[9]->draw();
    genComponents[11]->draw();
}
//--------------------------------------------------------------
void ofApp::setupGeneratorGui()
{
    mapWidth = new ofxDatGuiSlider("Map Width", 0, 100, 100);
    mapWidth->setWidth(250,100);
    mapWidth->setPrecision(0);
    mapWidth->setPosition(0,501);
    mapWidth->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(0, mapWidth));
    
    mapHeight = new ofxDatGuiSlider("Map Height", 0, 100, 100);
    mapHeight->setWidth(250,100);
    mapHeight->setPrecision(0);
    mapHeight->setPosition(mapWidth->getWidth(),501);
    mapHeight->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(1, mapHeight));
    
    tileSize = new ofxDatGuiSlider("Tile Size", 0, 10, 5);
    tileSize->setWidth(250,100);
    tileSize->setPrecision(0);
    tileSize->setPosition(0,mapWidth->getY()+mapWidth->getHeight());
    tileSize->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(2, tileSize));
    
    offsetEdge = new ofxDatGuiSlider("Offset Edge", 0, 50, 5);
    offsetEdge->setWidth(250,100);
    offsetEdge->setPrecision(0);
    offsetEdge->setPosition(mapWidth->getWidth(),mapWidth->getY()+mapWidth->getHeight());
    offsetEdge->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(3, offsetEdge));
    
    randomSeed = new ofxDatGuiSlider("Random Seed", 0, 5000, 0);
    randomSeed->setWidth(500,100);
    randomSeed->setPosition(0,tileSize->getY()+tileSize->getHeight());
    randomSeed->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(4, randomSeed));
    
    obsticles = new ofxDatGuiSlider("Obsticles", 0, 100, 0);
    obsticles->setWidth(500,100);
    obsticles->setPrecision(0);
    obsticles->setPosition(0,randomSeed->getY()+randomSeed->getHeight());
    obsticles->onSliderEvent(this,&ofApp::onSliderEvent);

    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(5, obsticles));
    
    dangerAreaSize = new ofxDatGuiSlider("Danger Area Size", 0, 25, 0);
    dangerAreaSize->setWidth(500,150);
    dangerAreaSize->setPrecision(0);
    dangerAreaSize->setPosition(0,obsticles->getY()+obsticles->getHeight());
    dangerAreaSize->onSliderEvent(this,&ofApp::onSliderEvent);

    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(6, dangerAreaSize));
    
    smoothingLoops = new ofxDatGuiSlider("Smoothing Loops", 0, 25, 0);
    smoothingLoops->setWidth(500,150);
    smoothingLoops->setPrecision(0);
    smoothingLoops->setPosition(0,dangerAreaSize->getY()+dangerAreaSize->getHeight());
    smoothingLoops->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(7, smoothingLoops));
    
    growthLoops = new ofxDatGuiSlider("Growth Loops", 0, 25, 0);
    growthLoops->setWidth(500,150);
    growthLoops->setPrecision(0);
    growthLoops->setPosition(0,smoothingLoops->getY()+smoothingLoops->getHeight());
    growthLoops->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(8, growthLoops));
    
    clearMap = new ofxDatGuiButton("Clear Map");
    clearMap->setWidth(500);
    clearMap->setPosition(0,growthLoops->getY()+growthLoops->getHeight());
    clearMap->onButtonEvent(this,&ofApp::onButtonEvent);

    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(9, clearMap));
//    genStrComponents.insert(std::pair<string, ofxDatGuiComponent*>("Clear Map", clearMap));
    
    generateMap = new ofxDatGuiButton("Generate Map");
    generateMap->setWidth(500);
    generateMap->setPosition(0,clearMap->getY()+clearMap->getHeight());
    generateMap->onButtonEvent(this,&ofApp::onButtonEvent);

    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(10, generateMap));
    
    generateCustomMap = new ofxDatGuiButton("Generate Custom Map");
    generateCustomMap->setWidth(500);
    generateCustomMap->setPosition(0,generateMap->getY()+generateMap->getHeight());
    generateCustomMap->onButtonEvent(this,&ofApp::onButtonEvent);

    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(11, generateCustomMap));
    
    highRedThreshold = new ofxDatGuiSlider("Red High Thresh", 0, 255, 0);
    highRedThreshold->setWidth(250,150);
    highRedThreshold->setPrecision(0);
    highRedThreshold->setPosition(501,251);
    highRedThreshold->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(12, highRedThreshold));
    
    highYellowThreshold = new ofxDatGuiSlider("Yellow High Thresh", 0, 255, 0);
    highYellowThreshold->setWidth(250,150);
    highYellowThreshold->setPrecision(0);
    highYellowThreshold->setPosition(501+highRedThreshold->getWidth(),251);
    highYellowThreshold->onSliderEvent(this,&ofApp::onSliderEvent);

    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(13, highYellowThreshold));
    
    highGreenThreshold = new ofxDatGuiSlider("Green High Thresh", 0, 255, 0);
    highGreenThreshold->setWidth(250,150);
    highGreenThreshold->setPrecision(0);
    highGreenThreshold->setPosition(501+(250*2),251);
    highGreenThreshold->onSliderEvent(this,&ofApp::onSliderEvent);
    
    genComponents.insert(std::pair<int, ofxDatGuiComponent*>(14, highGreenThreshold));

}
//--------------------------------------------------------------
void ofApp::setupOperationsGui()
{
    int height = ofGetHeight();

    vector<string> AppMode = {"CALIBRATION MODE",
        "EDITOR MODE",
        "GENERATION MODE",
        "MAP VIEWER",
        "OPERATION MODE"
    };
    
    title = new ofxDatGuiLabel("Happilee");
    title->setStripe(ofColor::mediumSlateBlue, 5);
    title->setWidth(200);
    
    appMode = new ofxDatGuiDropdown("App Mode",AppMode);
    appMode->setWidth(200);
    appMode->expand();
    appMode->setPosition(0, height-appMode->getHeight());
    appMode->onDropdownEvent(this, &ofApp::onDropdownEvent);
    
    startLevel = new ofxDatGuiButton("Start Level");
    startLevel->setWidth(150);
    startLevel->setPosition(appMode->getWidth(), height-startLevel->getHeight());
    startLevel->setStripe(ofColor::mediumSpringGreen, 5);
    startLevel->onButtonEvent(this, &ofApp::onButtonEvent);
    
    stopLevel = new ofxDatGuiButton("Stop Level");
    stopLevel->setWidth(150);
    stopLevel->setPosition(startLevel->getX()+startLevel->getWidth(), height-stopLevel->getHeight());
    stopLevel->setStripe(ofColor::red, 5);
    stopLevel->onButtonEvent(this, &ofApp::onButtonEvent);

    fpsIndicator = new ofxDatGuiFRM();
    fpsIndicator->setWidth(100, 10);
    fpsIndicator->setLabel("");
    fpsIndicator->setStripeVisible(false);
    fpsIndicator->setPosition(ofGetWidth()-fpsIndicator->getWidth(), height-fpsIndicator->getHeight());
    
    
    vector<string> difficulty;
    for(int i = 0; i < mapGenerator.getMapsInfo().size(); i++) {
        difficulty.push_back(mapGenerator.getMapsInfo()[i].Difficulty);
        dLvs.push_back(mapGenerator.getMapsInfo()[i].numberOfLevels);
    }
    
    difficultyBar = new ofxDatGuiDropdown("Select Difficulty", difficulty);
    difficultyBar->setStripe(ofColor::orange, 5);
    difficultyBar->setPosition(500+300, 0);
    difficultyBar->setWidth(250);
    
    difficultyBar->onDropdownEvent(this, &ofApp::onDropdownEvent);
    
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
    levelSelect->setWidth(450, 100);
    levelSelect->setPosition(500+300+difficultyBar->getWidth(), 0);
    levelSelect->onMatrixEvent(this, &ofApp::onMatrixEvent);
    
    resetLevel = new ofxDatGuiButton("Reset Health");
    resetLevel->setWidth(100);
    resetLevel->setPosition(stopLevel->getX()+stopLevel->getWidth(), height-resetLevel->getHeight());
    resetLevel->onButtonEvent(this, &ofApp::onButtonEvent);
    
    title->setPosition(ofGetWidth()-(fpsIndicator->getWidth()+title->getWidth()), height-fpsIndicator->getHeight());
    
    showSecondWindow = new ofxDatGuiToggle("Show Preview Window", false);
    showSecondWindow->setWidth(200);
    showSecondWindow->setPosition(resetLevel->getX()+resetLevel->getWidth(), height-showSecondWindow->getHeight());
    showSecondWindow->onButtonEvent(this, &ofApp::onButtonEvent);
    
    saveMapRecord = new ofxDatGuiButton("Save Map");
    saveMapRecord->setWidth(150);
    saveMapRecord->setPosition(showSecondWindow->getX()+showSecondWindow->getWidth(), height-saveMapRecord->getHeight());
    saveMapRecord->onButtonEvent(this, &ofApp::onButtonEvent);
    
    scaleX = new ofxDatGuiSlider("Scale X", 0, 1000, 500);
    scaleX->setPosition(levelSelect->getX(), levelSelect->getHeight());
    scaleX->setWidth(450, 100);
    scaleX->onSliderEvent(this, &ofApp::onSliderEvent);
    
    scaleY = new ofxDatGuiSlider("Scale Y", 0, 1000, 500);
    scaleY->setPosition(scaleX->getX(), levelSelect->getHeight()+scaleX->getHeight());
    scaleY->setWidth(450, 100);
    scaleY->onSliderEvent(this, &ofApp::onSliderEvent);
    
}
//--------------------------------------------------------------
void ofApp::updateGui()
{
    startLevel->update();
    stopLevel->update();
    resetLevel->update();
    fpsIndicator->update();
    appMode->update();
    difficultyBar->update();
    levelSelect->update();
    showSecondWindow->update();
    saveMapRecord->update();
    scaleX->update();
    scaleY->update();
    
    
    switch (_Appmode) {
        case 0:
            break;
        case 1:
            genComponents[9]->update();
            genComponents[11]->update();
            break;
        case 2:
            for (int i = 0; i < genComponents.size(); i++) {
                genComponents[i]->update();
            }
            break;
        case 3:
            view->update();
            for (int i = 0; i < commands.size(); i++) {
                commands.at(i)->update();
            }
            break;
        default:
            break;
    }
    
    if (!appMode->getIsExpanded()) {
        appMode->setPosition(0, ofGetHeight()-appMode->getHeight());
    }
    else {
        appMode->setPosition(0, ofGetHeight()-appMode->getHeight());
    }
    
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
    else if (e.target->is("Scale X")) playerManager.scalePositionX(e.target->getValue());
    else if (e.target->is("Scale Y")) playerManager.scalePositionY(e.target->getValue());
    else if (e.target->is("Green High Thresh")) {
        lGT = e.target->getValue();
        mapGenerator.setGreenThreshold(e.target->getValue());
    }
    else if (e.target->is("Red High Thresh")) {
        lRT = e.target->getValue();
        mapGenerator.setRedThreshold(e.target->getValue());
    }
}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is("Generate Map")) {
        mapGenerator.generateMap(_offsetEdge, _fillPercent,_numberOfIslands,_smooth,_growthNo,_rs,_dangerAreaSize);
//        mapGenerator.updateCV(lRT, lGT);
        playerManager.getFinderImage(mapGenerator.getSmoothMap());
        styledMap.getMapImage(mapGenerator.getSmoothMap());
//        displayWindow->setMapImage(styledMap.getStyledMap());
        mapMesh.clear();
        mapMesh.getMapImage(mapGenerator.getSmoothMap(),styledMap.getStyledMap());
    }
    else if (e.target->is("Generate Custom Map")) {
        mapGenerator.generateCustomMap(_smooth,_growthNo,_dangerAreaSize);
        playerManager.getFinderImage(mapGenerator.getSmoothMap());
        styledMap.getMapImage(mapGenerator.getSmoothMap());
//        displayWindow->setMapImage(styledMap.getStyledMap());
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
//        displayWindow->setCalibration(_numberOfXLines, _numberOfYLines, _spacingX, _spacingY);
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
    else if(e.target->is("Save Map")) {
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
        string vas = "maps/thumbnails/"+ofGetTimestampString()+".jpg";
        ofSaveImage(styledMap.getStyledMap(), vas);
        
        ofImage oscMap;
        oscMap.setFromPixels(styledMap.getStyledMap().getPixels().getData(), styledMap.getStyledMap().getWidth(), styledMap.getStyledMap().getHeight(), OF_IMAGE_COLOR);
        oscMap.resize(styledMap.getStyledMap().getWidth()/2, styledMap.getStyledMap().getHeight()/2);
        ofSaveImage(oscMap, "tempMaps/"+ofGetTimestampString()+".png");
        
        mapGenerator.saveMap(vas,styledMap.getCurrentStyle(),m);
    }
    else if (e.target->is("Reset Health")) {
        playerManager.resetHealth();
        for (int i = 0; i < 3; i++) {
            bUnitMalfunctioned[i] = false;
        }
        robotManager.fireCommand(0, HPL_RESET_MEMORY);
    }
    else if (e.target->is("Malfunction")) {
        robotManager.fireCommand(0, HPL_MALFUNCTION);
    }
    else if (e.target->is("Reboot Happilee")) {
        robotManager.fireCommand(0, HPL_REBOOT);
    }
    else if (e.target->is("Green Zone")) {
        robotManager.fireCommand(0, HPL_GREEN_ZONE);
    }
    else if (e.target->is("Yellow Zone")) {
        robotManager.fireCommand(0, HPL_YELLOW_ZONE);
    }
    else if (e.target->is("Red Zone")) {
        robotManager.fireCommand(0, HPL_RED_ZONE);
    }
    else if (e.target->is("Safe Zone")) {
        robotManager.fireCommand(0, HPL_SAFE_ZONE);
    }
    else if (e.target->is("Reset Memory")) {
        robotManager.fireCommand(0, HPL_RESET_MEMORY);
    }
//    else if (e.target->is("Reduce Health")) {
//        robotManager.fireCommand(0, HPL_REDUCE_HEALTH);
//    }
//    else if (e.target->is("Malfunction")) {
//        robotManager.fireCommand(0, HPL_MALFUNCTION);
//    }
//    else if (e.target->is("Start")) {
//        robotManager.fireCommand(0, HPL_START);
//    }
//    else if (e.target->is("Instructions")) {
//        robotManager.fireCommand(0, HPL_INSTRUCTIONS);
//    }
//    else if (e.target->is("Flash Lights")) {
//        robotManager.fireCommand(0, HPL_FLASH_LIGHTS);
//    }
//    else if (e.target->is("Turn Off Screen")) {
//        robotManager.fireCommand(0, HPL_TURN_OFF_SCREEN);
//    }
//    else if (e.target->is("Turn On Screen")) {
//        robotManager.fireCommand(0, HPL_TURN_ON_SCREEN);
//    }
//    else if (e.target->is("Extend Aerial")) {
//        robotManager.fireCommand(0, HPL_EXTEND_AERIAL);
//    }
//    else if (e.target->is("Retract Aerial")) {
//        robotManager.fireCommand(0, HPL_RETRACT_AERIAL);
//    }
//    else if (e.target->is("In Danger")) {
//        robotManager.fireCommand(0, HPL_IN_DANGER);
//    }
//    else if (e.target->is("Ok")) {
//        robotManager.fireCommand(0, HPL_IS_OK);
//    }
//    else if (e.target->is("Send Map")) {
//        unsigned char * pix = styledMap.getStyledMap().getPixels();
//        server.sendPixels(pix);
//    }
    
}
//--------------------------------------------------------------
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{   }
//--------------------------------------------------------------
void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    if (e.target->is("Calibration Nodes")) {
//        displayWindow->calibrationScreen.moveNodes(e.x, e.y);
    }
}
//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    if(e.target->is("App Mode")) {
        if (e.target->getLabel() == "CALIBRATION MODE") {
            _Appmode = 0;
            mode = "Calibration Mode";
//            displayWindow->doCalibration(true);
        }
        else if (e.target->getLabel() == "EDITOR MODE") {
            _Appmode = 1;
            mode = "Editor Mode";
            genComponents[9]->setPosition(0, 501);
            generateCustomMap->setPosition(0,genComponents[9]->getY()+genComponents[9]->getHeight());
//            displayWindow->doCalibration(false);
        }
        else if (e.target->getLabel() == "GENERATION MODE") {
            _Appmode = 2;
            mode = "Generation Mode";
            genComponents[9]->setPosition(0,growthLoops->getY()+growthLoops->getHeight());
            generateCustomMap->setPosition(0,generateMap->getY()+generateMap->getHeight());
        }
        else if (e.target->getLabel() == "OPERATION MODE") {
            mode = "Operation Mode";
            _Appmode = 3;
//            displayWindow->doCalibration(false);
        }
        else if (e.target->getLabel() == "MAP VIEWER") {
            mode = "Map Viewer";
            _Appmode = 4;
//            displayWindow->doCalibration(false);
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
//        displayWindow->setMapImage(styledMap.getStyledMap());
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
    previousState[0] = "";
    previousState[1] = "";
    previousState[2] = "";
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
    lGT = 0;
    lYT = 0;
    lRT = 0;
    _iRY[0] = 25;
    _iRY[1] = 255;
    
    _iRG[0] = 25;
    _iRG[1] = 255;
    
    for(int i = 0; i < 10; i ++) {
        event[i] = "Player ";
    }
    heading.load("ofxdatgui_assets/font-verdana.ttf",20);
}

