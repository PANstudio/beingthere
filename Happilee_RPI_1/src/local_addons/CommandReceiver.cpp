//
//  CommandReceiver.cpp
//  Happilee
//
//  Created by David Haylock on 26/05/2016.
//
//

#include "CommandReceiver.h"

//--------------------------------------------------------------
void CommandReceiver::setup(int port)
{
    receiver.setup(port);
}
//--------------------------------------------------------------
void CommandReceiver::startListening()
{
    startThread();
}
//--------------------------------------------------------------
void CommandReceiver::stopListening()
{
    stopThread();
}
//--------------------------------------------------------------
void CommandReceiver::threadedFunction()
{
    while (isThreadRunning()) {
        if (lock()) {
            while (receiver.hasWaitingMessages()) {
                ofxOscMessage m;
                receiver.getNextMessage(m);
                string ts = "st";
                cout << m.getAddress() << endl;
                if (m.getAddress() == "/robot/hplgreen") {
                    ofNotifyEvent(greenZone, ts, this);
                }
                else if (m.getAddress() == "/robot/hplyellow") {
                    ofNotifyEvent(yellowZone, ts, this);
                }
                else if (m.getAddress() == "/robot/hplred") {
                    ofNotifyEvent(redZone, ts, this);
                }
                else if (m.getAddress() == "/robot/hplsafe") {
                    ofNotifyEvent(safeZone, ts, this);
                }
                else if (m.getAddress() == "/robot/hplreset") {
                    ofNotifyEvent(resetMemory, ts, this);
                }
                else if (m.getAddress() == "/robot/hplmalf") {
                    ofNotifyEvent(malfunction, ts, this);
                }
                else if (m.getAddress() == "/robot/hplreboot") {
                    ofNotifyEvent(reboot, ts, this);
                }
            }
            unlock();
            sleep(10);
        }
    }
}
//--------------------------------------------------------------
void CommandReceiver::update()
{
    //    while (receiver.hasWaitingMessages()) {
    //        ofxOscMessage m;
    //        receiver.getNextMessage(m);
    //        string ts = "st";
    //
    //        if (m.getAddress() == "/robot/RreH") {
    //            ofNotifyEvent(resetHealth, ts, this);
    //        }
    //        else if (m.getAddress() == "/robot/Rreset") {
    //            ofNotifyEvent(reduceHealth, ts, this);
    //        }
    //        else if (m.getAddress() == "/robot/Rmalf") {
    //            ofNotifyEvent(malfunction, ts, this);
    //        }
    //        else if (m.getAddress() == "/robot/Rstr") {
    //            ofNotifyEvent(start, ts, this);
    //        }
    //        else if (m.getAddress() == "/robot/Rinst") {
    //            ofNotifyEvent(instruction, ts, this);
    //        }
    //        else if (m.getAddress() == "/robot/RfL") {
    //            ofNotifyEvent(flashLights, ts, this);
    //        }
    //        else if (m.getAddress() == "/robot/RiD") {
    //            ofNotifyEvent(inDanger, ts, this);
    //        }
    //        else if (m.getAddress() == "/robot/RoK") {
    //            ofNotifyEvent(okDanger, ts, this);
    //        }
    //    }
}
//--------------------------------------------------------------
void CommandReceiver::draw()
{
    
}