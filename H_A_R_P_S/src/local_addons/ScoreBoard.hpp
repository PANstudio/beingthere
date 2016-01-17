//
//  ScoreBoard.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 19/12/2015.
//
//

#ifndef ScoreBoard_hpp
#define ScoreBoard_hpp

#include <stdio.h>
#include <algorithm>
#include "ofMain.h"
#include "ofxTween.h"
#include "ofxJSON.h"
#include "ScoreboardButton.h"
#include "ofxSpreadsheet.h"

//----------------------------------------------------------
struct ScoreboardElements {
    
    ScoreboardElements(string _playerName,bool _didComplete,string _location, string _timeCompleted, int _healthRemaining,int _difficult,int _level,int _objects,int _toxicity,string _timestamp)
    {
        playerName = _playerName;
        didComplete = _didComplete;
        location = _location;
        timeCompleted = _timeCompleted;
        healthRemaining = _healthRemaining;
        difficulty = _difficult;
        level = _level;
        objects = _objects;
        toxicity = _toxicity;
        timestamp = _timestamp;
    }
    vector <string> getDetails() {
        vector<string> detail;
        detail.push_back(playerName);
        detail.push_back(ofToString(didComplete));
        detail.push_back(location);
        detail.push_back(timeCompleted);
        detail.push_back(ofToString(healthRemaining));
        detail.push_back(ofToString(difficulty));
        detail.push_back(ofToString(level));
        detail.push_back(ofToString(objects));
        detail.push_back(ofToString(toxicity));
        detail.push_back(timestamp);
        return detail;
    }
    
    string playerName;
    bool didComplete;
    string location;
    string timeCompleted;
    int healthRemaining;
    int difficulty;
    int level;
    int objects;
    int toxicity;
    string timestamp;
};

//----------------------------------------------------------
class Scoreboard {
public:
    void loadScoreboard(string file);
    void setup();
    void update();
    void draw(int x, int y);
    void addNewPlayerToBoard(ScoreboardElements elements);

    deque <ScoreboardButton> buttons;
    
    void sortByQuickest(bool acendingOrder);
    void sortByPlayerName(bool acendingOrder);
    void sortByObsticles(bool acendingOrder);
    void sortByDifficultly(bool acendingOrder);
    void sortByDate(bool acendingOrder);
    void sortByLocation(bool acendingOrder);
    void sortByHealth(bool acendingOrder);
    
private:
    deque<ScoreboardElements> scoreBoardData;
    ofxSpreadsheet spreadsheet;
};
#endif /* ScoreBoard_hpp */
