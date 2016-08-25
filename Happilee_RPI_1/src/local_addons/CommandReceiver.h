//
//  CommandReceiver.h
//  Happilee
//
//  Created by David Haylock on 26/05/2016.
//
//

#ifndef CommandReceiver_h
#define CommandReceiver_h

#include <stdio.h>
#include "ofxOsc.h"
#include "ofMain.h"

//-----------------------
// * Green Zone = hplgreen
// * Yellow Zone = hplyellow
// * Red Zone = hplred
// * Safe Zone = hplsafe
// * Reset Memory = hplreset;
// * Malfunction = hplmalf;
// * Reboot = hplreboot

//-----------------------

class CommandReceiver : public ofThread {
    
public:
    void setup(int port);
    void update();
    void draw();
    
    void startListening();
    void stopListening();
    void threadedFunction();
    
    ofEvent<string>resetMemory;
    ofEvent<string>greenZone;
    ofEvent<string>yellowZone;
    ofEvent<string>redZone;
    ofEvent<string>malfunction;
    ofEvent<string>safeZone;
    ofEvent<string>reboot;
    
private:
    ofxOscReceiver receiver;
protected:
    
};
#endif /* CommandReceiver_h */
