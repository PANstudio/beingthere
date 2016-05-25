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
                cout << m.getAddress() << endl;
                
                if (m.getAddress() == "/robot/RreH") {
                    ofNotifyEvent(reduceHealth, ts, this);
                }
                else if (m.getAddress() == "/robot/Rreset") {
                    ofNotifyEvent(resetHealth, ts, this);
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
                else if (m.getAddress() == "/robot/RsM") {
                    ofBuffer e = m.getArgAsBlob(0);
//                    ew.load(e);
                    cout << e.getData() << endl;
                    ofNotifyEvent(gotImage,ew, this);
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
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        string ts = "st";
        cout << m.getAddress() << endl;
        
        if (m.getAddress() == "/robot/RreH") {
            ofNotifyEvent(reduceHealth, ts, this);
        }
        else if (m.getAddress() == "/robot/Rreset") {
            ofNotifyEvent(resetHealth, ts, this);
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
        else if (m.getAddress() == "/robot/RsM") {
            ew.clear();
            ofLoadURL("http://127.0.0.1:7890/this.png");
//            ew.load(ofLoadURL("http://127.0.0.1:7890/this.png"));
//            ofBuffer e = m.getArgAsBlob(0);
////            ew.clear();
////            ew.load(e);
////            cout << "Got new map " << ew.getWidth() << " " << ew.getHeight() << endl;
//////            cout << e.getData() << endl;
////            ofNotifyEvent(gotImage,ew, this);
        }
    }
}
//--------------------------------------------------------------
void ReceiveCommands::draw()
{
    
}