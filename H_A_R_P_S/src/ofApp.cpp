#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // Yep its in the name
    setupGUI();
    mapGenerator.generateMap(100, 100, 0, 5, 10, 2, 100, 1.9, 3);
}
//--------------------------------------------------------------
void ofApp::update()
{

}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0, 0, 0);
    mapGenerator.draw();
    
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

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
   
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
    
//    mapGenerator.LoadMaps("config.json");
//    for(int i = 0; i < mapGenerator.getMapsInfo().size(); i++) {
//        difficulty.push_back(mapGenerator.getMapsInfo()[i].Difficulty);
//        dLvs.push_back(mapGenerator.getMapsInfo()[i].numberOfLevels);
//    }
    
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
    mapFolder->addSlider("Offset Edge", 0, 100, 10);
    mapFolder->addSlider("Random Seed", 0.00, 150.00, 3.14);
    mapFolder->addSlider("Fill Percent", 0.00, 100.00, 50);
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

}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{

}
//--------------------------------------------------------------
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{

}
//--------------------------------------------------------------
void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{

}
//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{

}
//--------------------------------------------------------------
void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    
}
//--------------------------------------------------------------
void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    
}

