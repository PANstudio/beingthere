//
//  ReceiveCommands.cpp
//  HARPSRobotSimulator
//
//  Created by David Haylock on 18/04/2016.
//
//

#include "ReceiveCommands.h"

//--------------------------------------------------------------
void ReceiveCommands::setup(int port)
{
    receiver.setup(port);
}
//--------------------------------------------------------------
void ReceiveCommands::startListening()
{
    startThread();
}
//--------------------------------------------------------------
void ReceiveCommands::stopListening()
{
    stopThread();
}
//--------------------------------------------------------------
void ReceiveCommands::threadedFunction()
{
    while (isThreadRunning()) {
        if (lock()) {
            while (receiver.hasWaitingMessages()) {
                ofxOscMessage m;
                receiver.getNextMessage(m);
                string ts = "st";
                
                if (m.getAddress() == "/robot/RreH") {
                    ofNotifyEvent(resetHealth, ts, this);
                }
                else if (m.getAddress() == "/robot/Rreset") {
                    ofNotifyEvent(reduceHealth, ts, this);
                }
                else if (m.getAddress() == "/robot/Rmalf") {
                    ofNotifyEvent(malfunction, ts, this);
                }
                else if (m.getAddress() == "/robot/Rstr") {
                    ofNotifyEvent(start, ts, this);
                }
                else if (m.getAddress() == "/robot/Rinst") {
                    ofNotifyEvent(instruction, ts, this);
                }
                else if (m.getAddress() == "/robot/RfL") {
                    ofNotifyEvent(flashLights, ts, this);
                }
                else if (m.getAddress() == "/robot/RiD") {
                    ofNotifyEvent(inDanger, ts, this);
                }
                else if (m.getAddress() == "/robot/RoK") {
                    ofNotifyEvent(okDanger, ts, this);
                }
            }
            unlock();
            sleep(10);
        }
    }
}
//--------------------------------------------------------------
void ReceiveCommands::update()
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
void ReceiveCommands::draw()
{
    
}