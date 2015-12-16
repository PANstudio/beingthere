//
//  ControlNode.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 16/12/2015.
//
//

#ifndef ControlNode_hpp
#define ControlNode_hpp

#include <stdio.h>
#include "ofMain.h"

class ControlNode : public ofRectangle {

    public:
        ControlNode(int x,int y,int id);
        ~ControlNode();
    
        void draw();
        void setOriginNode();
        void recalculateId();
    
        void mouseOver(int x,int y);
        void nodeClicked(int x,int y,int button);
    
    private:
        bool isActive;
        bool isOrigin;
        bool isOver;
    protected:
        int _id;
};

#endif /* ControlNode_hpp */
