//
//  ScoreboardButton.h
//  H_A_R_P_S
//
//  Created by David Haylock on 16/01/2016.
//
//

#ifndef ScoreboardButton_h
#define ScoreboardButton_h

#include "ofMain.h"
#include "BaseButton.h"
//---------------------------------------------------
class ScoreboardButton : public BaseButton {
public:
    ScoreboardButton() {}
    //---------------------------------------------------
    ScoreboardButton(int x,int y,int w, int h,int orderBy,string name,ofColor c)
    {
        _orderBy = orderBy;
        this->set(x,y,w,h);
        _baseColor = c;
        _buttonName = name;
    }
    //---------------------------------------------------
    ~ScoreboardButton() {}
    //---------------------------------------------------
    void setupButton(int x,int y,int w, int h,int orderBy,string name,ofColor c)
    {
        _orderBy = orderBy;
        this->set(x,y,w,h);
        _baseColor = c;
        _buttonName = name;
    }
    
    int _orderBy;
    
};
#endif /* ScoreboardButton_h */
