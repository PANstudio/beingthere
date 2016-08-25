#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
//	ofSetupOpenGL(800,480,OF_WINDOW);
    ofGLESWindowSettings settings;
    settings.setGLESVersion(2);
    settings.width = 800;
    settings.height = 480;
    ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
