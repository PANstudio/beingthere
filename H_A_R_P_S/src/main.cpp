#include "ofMain.h"
#include "ofApp.h"
//#include "DisplayWindow.h"
//#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

    ofSetupOpenGL(1200, 800, OF_WINDOW);
    ofRunApp(new ofApp());
//    ofGLFWWindowSettings settings;
//    
//    settings.width = 1100;
//    settings.height = 800;
//    settings.setPosition(ofVec2f(0,0));
//    settings.resizable = true;
//    settings.monitor = 0;
//    settings.multiMonitorFullScreen = false;
//    shared_ptr<ofAppBaseWindow> operatorWindow = ofCreateWindow(settings);
    
    
//    settings.width = 550;
//    settings.height = 550;
//    settings.setPosition(ofVec2f(0,0));
//    settings.resizable = true;
//    settings.shareContextWith = ofGetMainLoop()->getCurrentWindow();
//    settings.monitor = 1;
//    settings.multiMonitorFullScreen = false;
//    shared_ptr<ofAppBaseWindow> displayWindow = ofCreateWindow(settings);

//    shared_ptr<ofApp> mainApp(new ofApp);
//    shared_ptr<DisplayWindow> displayWindowApp(new DisplayWindow);
//    mainApp->displayWindow = displayWindowApp;

    
//    ofRunApp(displayWindow,displayWindowApp);
//    ofRunApp(operatorWindow,mainApp);
//    ofRunMainLoop();

}
