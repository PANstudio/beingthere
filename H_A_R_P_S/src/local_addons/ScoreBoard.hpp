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

    void sortQuickestComplete();
    void sortMostObjects();
    void sortByDate();
    void sortByLocation();
    void sortByHealth();
    
//    bool sortByRemaining(const ScoreboardElements a,const ScoreboardElements b);
private:
    deque<ScoreboardElements> scoreBoardData;
};
#endif /* ScoreBoard_hpp */
