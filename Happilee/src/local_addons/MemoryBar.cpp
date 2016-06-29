//
//  MemoryBar.cpp
//  Happilee
//
//  Created by David Haylock on 27/05/2016.
//
//

#include "MemoryBar.h"

//--------------------------------------------------------------
void MemoryBar::setup(float initialMemory)
{
    memoryRemaining = initialMemory;
    resetMemory(initialMemory);
    ofAddListener(reducer.end_E, this, &MemoryBar::tweenFinished);
}
//--------------------------------------------------------------
void MemoryBar::update()
{
    if (memoryRemaining <= 0 && !hasDied) {
        string mal = "Died";
        ofNotifyEvent(isDead,mal, this);
        hasDied = true;
    }
}
//--------------------------------------------------------------
void MemoryBar::resetMemory(float initialMemory)
{
    memoryRemaining = initialMemory;
    reducer.setParameters(1, expo, ofxTween::easeIn, 0, memoryRemaining, 5000, 10);
    hasDied = false;
    _hasRebooted = false;
}
//--------------------------------------------------------------
void MemoryBar::reduceMemory(float amount)
{
    if (!hasDied) {
        float newMemory = memoryRemaining - amount;
        reducer.setParameters(0, expo, ofxTween::easeInOut, memoryRemaining,newMemory, 250, 0);
    }
}
//--------------------------------------------------------------
void MemoryBar::tweenFinished(int &val)
{
    memoryRemaining = reducer.update();
    if (val == 1) {
        _hasRebooted = true;
    }
}
//--------------------------------------------------------------
bool MemoryBar::hasRebooted()
{
    return _hasRebooted;
}
//--------------------------------------------------------------
float MemoryBar::getMemoryRemaining()
{
    return reducer.update();
}
