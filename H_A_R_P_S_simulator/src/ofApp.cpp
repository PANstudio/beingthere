#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    setupGUI();
}
//--------------------------------------------------------------
void ofApp::update()
{

}
//--------------------------------------------------------------
void ofApp::draw()
{
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
    gui->addHeader("H_A_R_P_S");
    gui->addFRM(1.0f);
    gui->addBreak();
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
    if (e.target->is("Number of Players")) {
        numberOfPlayers = ofToInt(e.target->getLabel());
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