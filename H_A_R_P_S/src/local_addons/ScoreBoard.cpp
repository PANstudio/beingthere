//
//  ScoreBoard.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 19/12/2015.
//
//

#include "ScoreBoard.hpp"
//----------------------------------------------------------
void Scoreboard::loadScoreboard(string file)
{
    scoreBoardData.clear();
    ofxJSONElement scoreBoard;
    
    if(!scoreBoard.open(file)) {
        cout << "Scoreboard File not Loaded" << endl;
        return;
    }
    else {
        int numberOfEntries = scoreBoard["data"].size();
        for (int i = 0; i < numberOfEntries; i++) {
            scoreBoardData.push_back(ScoreboardElements(scoreBoard["data"][i]["playername"].asString(),
                                        scoreBoard["data"][i]["didcomplete"].asBool(),
                                        scoreBoard["data"][i]["location"].asString(),
                                        scoreBoard["data"][i]["timecompleted"].asString(),
                                        scoreBoard["data"][i]["healthremaining"].asInt(),
                                        scoreBoard["data"][i]["difficult"].asInt(),
                                        scoreBoard["data"][i]["level"].asInt(),
                                        scoreBoard["data"][i]["objects"].asInt(),
                                        scoreBoard["data"][i]["toxicity"].asInt(),
                                        scoreBoard["data"][i]["timestamp"].asString())
                                     );
        }
    }
}
//----------------------------------------------------------
void Scoreboard::setup()
{
    
}
//----------------------------------------------------------
void Scoreboard::update()
{
    
}
//----------------------------------------------------------
void Scoreboard::draw(int x, int y)
{
    stringstream boardData;
    boardData << "---------------------------------------------" << endl;
    for (auto data : scoreBoardData) {
        boardData << "| " <<  data.playerName << " " << data.didComplete << " " << data.timeCompleted << " " << data.objects << " " << data.healthRemaining << " " << data.location << " " << data.timestamp << " |" << endl;
    }
    boardData << "---------------------------------------------" << endl;
    ofSetColor(ofColor::ivory);
    ofDrawBitmapString(boardData.str(), x,y);
}
//----------------------------------------------------------
void Scoreboard::addNewPlayerToBoard(ScoreboardElements elements)
{
    scoreBoardData.push_back(elements);
}
//----------------------------------------------------------
void Scoreboard::sortQuickestComplete()
{
    
}
//----------------------------------------------------------
void Scoreboard::sortMostObjects()
{
    
}
//----------------------------------------------------------
void Scoreboard::sortByDate()
{
    
}
//----------------------------------------------------------
void Scoreboard::sortByLocation()
{
    
}
//----------------------------------------------------------
void Scoreboard::sortByHealth()
{
//    std::sort(scoreBoardData.begin(), scoreBoardData.end());
//    std::sort(scoreBoardData.begin(), scoreBoardData.end(),sortByRemaining);
}