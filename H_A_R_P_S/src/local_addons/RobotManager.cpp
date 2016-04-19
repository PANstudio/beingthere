//--------------------------------------------------------------
//
//  RobotManager.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 14/11/2015.
//
//--------------------------------------------------------------
#include "RobotManager.h"

//--------------------------------------------------------------
void RobotManager::setup()
{
    ofxOscSender sender;
    for (int i = 0; i < receiversHostname.size(); i++) {
        sender.setup(receiversHostname[i], 7890);
        senders.insert(std::pair<string, ofxOscSender>(receiversHostname[i],sender));
    }
    commandsSent.resize(receiversHostname.size());
}
//--------------------------------------------------------------
void RobotManager::loadCommands()
{
    ofxJSONElement commandFile;
    
    if(!commandFile.open("commands.json")) {
        ofLogError() << "File not Loaded: COMMANDS";
        return;
    }
    else {
        int noRobots = commandFile["Robots"].size();
        for (int i = 0; i < noRobots; i++) {
            receiversHostname.push_back(commandFile["Robots"][i]["host"].asString());
        }
        
        int commandsNo = commandFile["RobotCommands"].size();
        for (int i = 0; i < commandsNo; i++) {
            commands.insert(std::pair<int, string>(commandFile["RobotCommands"][i]["id"].asInt(),commandFile["RobotCommands"][i]["command"].asString()));
        }
    }
}
//--------------------------------------------------------------
void RobotManager::fireCommand(int whichRobot, int command)
{
    ofxOscMessage e;
    e.setAddress("/robot/"+commands[command]);
    senders[receiversHostname[whichRobot]].sendMessage(e);
    string cmds = "Robot "+ofToString(whichRobot) + " "+commands[command] + " " + ofToString(command);
    commandsSent[whichRobot].push_back(cmds);
}
//--------------------------------------------------------------
void RobotManager::draw(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    for (int i = 0; i < commandsSent.size(); i++) {
        if (commandsSent[i].size() > 10) {
            commandsSent[i].pop_front();
        }
    }
    
    for (int i = 0; i < commandsSent.size(); i++) {
        for (int cm = 0; cm < commandsSent[i].size(); cm++) {
            ofSetColor(255);
            ofDrawBitmapString(commandsSent[i][cm], 15+(i*200), 15+(cm*15));
        }
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void RobotManager::close()
{
    for (int i = 0; i < senders.size(); i++) {
        senders[receiversHostname[i]].disableBroadcast();
    }
}