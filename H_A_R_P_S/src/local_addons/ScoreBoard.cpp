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
        int count = 0;
        for (int y = 0; y < 7; y++) {
            for (int x = 0; x < 2; x++) {
                buttons.push_back(ScoreboardButton(ofGetWidth()-100+(x*50), 100+(y*50), 40, 40, count, ofToString(count), ofColor::white));
                count++;
            }
        }
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
    
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].draw();
    }
}
//----------------------------------------------------------
void Scoreboard::addNewPlayerToBoard(ScoreboardElements elements)
{
    scoreBoardData.push_back(elements);
}
//----------------------------------------------------------
// *
// *    Sorting System
// *
//----------------------------------------------------------
void Scoreboard::sortByQuickest(bool acendingOrder)
{
    if (acendingOrder) {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return ofToInt(a.timeCompleted) < ofToInt(b.timeCompleted);
        });
    }
    else {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return ofToInt(a.timeCompleted) > ofToInt(b.timeCompleted);
        });
    }
}
//----------------------------------------------------------
void Scoreboard::sortByPlayerName(bool acendingOrder)
{
    
}
//----------------------------------------------------------
void Scoreboard::sortByObsticles(bool acendingOrder)
{
    if (acendingOrder) {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return a.objects < b.objects;
        });
    }
    else {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return a.objects > b.objects;
        });
    }
}
//----------------------------------------------------------
void Scoreboard::sortByDifficultly(bool acendingOrder)
{
    if (acendingOrder) {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return a.difficulty < b.difficulty;
        });
    }
    else {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return a.difficulty > b.difficulty;
        });
    }
}
//----------------------------------------------------------
void Scoreboard::sortByDate(bool acendingOrder)
{
    
}
//----------------------------------------------------------
void Scoreboard::sortByLocation(bool acendingOrder)
{
    
}
//----------------------------------------------------------
void Scoreboard::sortByHealth(bool acendingOrder)
{
    if (acendingOrder) {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return a.healthRemaining < b.healthRemaining;
        });
    }
    else {
        sort(scoreBoardData.begin(), scoreBoardData.end(), [](const ScoreboardElements &a, const ScoreboardElements &b){
            return a.healthRemaining > b.healthRemaining;
        });
    }
}
//----------------------------------------------------------