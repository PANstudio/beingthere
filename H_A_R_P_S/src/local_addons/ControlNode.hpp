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

struct NodeReadings {
    
    //-----------------------------------------------------
    NodeReadings() {    }
    //-----------------------------------------------------
    ~NodeReadings() {    }
    //-----------------------------------------------------
    NodeReadings(int _nodeID,float _var1 = 0,float _var2 = 0,float _var3 = 0,float _var4 = 0,float _var5 = 0,float _var6 = 0) {
        nodeID = _nodeID;
        var1 = _var1;
        var2 = _var2;
        var3 = _var3;
        var4 = _var4;
        var5 = _var5;
        var6 = _var6;
        
        cout << "---------------" << endl;
        cout << "Node " << _nodeID << endl;
        cout << "Var 1 " << _var1 << endl;
        cout << "Var 2 " << _var2 << endl;
        cout << "Var 3 " << _var3 << endl;
        cout << "Var 4 " << _var4 << endl;
        cout << "Var 5 " << _var5 << endl;
        cout << "Var 6 " << _var6 << endl;
    }
    
    int nodeID;
    float var1;
    float var2;
    float var3;
    float var4;
    float var5;
    float var6;
};

class ControlNode : public ofRectangle {

    public:
        ControlNode(int x,int y,int id);
        ~ControlNode();
    
        void draw();
        void setOriginNode();
        void recalculateId();

        void setValues(float _var1,float _var2,float _var3,float _var4,float _var5,float _var6);
    
        void mouseOver(int x,int y);
        void nodeClicked(int x,int y,int button);
        vector<string> getReadings();
        int _x;
        int _y;
        bool isActive;
    private:
        NodeReadings nReading;
        bool isOrigin;
        bool isOver;
    protected:
        int _id;
};

#endif /* ControlNode_hpp */
