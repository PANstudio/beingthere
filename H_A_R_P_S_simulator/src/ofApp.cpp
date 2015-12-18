#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    setupGUI();
    gridPattern.setup(10, 10, 10, 10, 50, 50);
    playerManager.setup("localhost",7890);
    playerManager.setNumberOfPlayers(3);
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("H.A.R.P.S Simulator");
    playerManager.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    gridPattern.draw();
    playerManager.drawPlayerManager();
    if (drawGui) {
        gui->draw();
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    drawGui = !drawGui;
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

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
void ofApp::setupGUI()
{
    int spacing = 7;
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
//    gui->setWidth(200);
    gui->addHeader("H_A_R_P_S");
    gui->addFRM(1.0f);
    gui->addBreak();

    gui->addColorPicker("Background");
    
    ofxDatGuiFolder * grid = gui->addFolder("Grid",ofColor::blueSteel);
    grid->addSlider("Grid Size X", 0.000, 200.000);
    grid->addSlider("Grid Size Y", 0.000, 200.000);
    grid->addSlider("Grid Spacing X", 10.000, 100.000);
    grid->addSlider("Grid Spacing Y", 10.000, 100.000);
    grid->addSlider("Grid Offset X", 10.000, 100.000);
    grid->addSlider("Grid Offset Y", 10.000, 100.000);
    grid->addButton("Regenerate Grid");

    vector<string> players;
    players.push_back("1");
    players.push_back("2");
    players.push_back("3");
    players.push_back("4");
    gui->addDropdown("Number of Players", players);

    ofxDatGuiFolder * emulators = gui->addFolder("Emulator",ofColor::blueSteel);
    emulators->addSlider("Speed", 0.000, 10.000);
    emulators->addSlider("Random Seed", 0.000, 100.000);
    emulators->addSlider("Smoothing", 0.000, 10.000);
    
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
    if (e.target->is("Speed")) speed = e.target->getValue();
    else if (e.target->is("Random Seed")) randomSeed = e.target->getValue();
    else if (e.target->is("Smoothing")) smoothing = e.target->getValue();
    else if (e.target->is("Grid Size X")) gridSizeX = e.target->getValue();
    else if (e.target->is("Grid Size Y")) gridSizeY = e.target->getValue();
    else if (e.target->is("Grid Spacing X")) spacingX = e.target->getValue();
    else if (e.target->is("Grid Spacing Y")) spacingY = e.target->getValue();
    else if (e.target->is("Grid Offset X")) gridOffsetX = e.target->getValue();
    else if (e.target->is("Grid Offset Y")) gridOffsetY = e.target->getValue();
    
}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if(e.target->is("Regenerate Grid")) gridPattern.setup(gridSizeX, gridSizeY, gridOffsetX, gridOffsetY, spacingX, spacingY);
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
    if (e.target->is("Number of Players")) {
        numberOfPlayers = ofToInt(e.target->getLabel());
    }
}
//--------------------------------------------------------------
void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    ofBackground(e.color);
}
//--------------------------------------------------------------
void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    
}