#include "ofMain.h"
#include "ofApp.h"
#include "DisplayWindow.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

    ofGLFWWindowSettings settings;
    
    settings.width = 1100;
    settings.height = 800;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    settings.monitor = 0;
    settings.multiMonitorFullScreen = false;
    shared_ptr<ofAppBaseWindow> operatorWindow = ofCreateWindow(settings);
    
    
    settings.width = 750;
    settings.height = 750;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    settings.monitor = 1;
    settings.multiMonitorFullScreen = false;
    shared_ptr<ofAppBaseWindow> displayWindow = ofCreateWindow(settings);

    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<DisplayWindow> displayWindowApp(new DisplayWindow);
    mainApp->displayWindow = displayWindowApp;
    
    ofRunApp(displayWindow,displayWindowApp);
    ofRunApp(operatorWindow,mainApp);
    ofRunMainLoop();

}
