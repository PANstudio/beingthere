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
    NodeReadings(int _nodeID ,float _RXDistX, float _RXDistY, float _TX1RXDist, float _TX1_RSSI1, float _C1_1, float _C1_2, float _C1_3, float _C1_4, float _C1_5, float _C1_6, float _TX2_RSS2, float _C2_1, float _C2_2, float _C2_3, float _C2_4, float _C2_5, float _C2_6, float _TX3_RSS3, float _C3_1, float _C3_2, float _C3_3, float _C3_4, float _C3_5, float _C3_6)
    {
        nodeID = _nodeID;
        RXDistX = _RXDistX;
        RXDistY = _RXDistY;
        TX1RXDist = _TX1RXDist;

        TX1_RSSI1 = _TX1_RSSI1;
        C1_1 = _C1_1;
        C1_2 = _C1_2;
        C1_3 = _C1_3;
        C1_4 = _C1_4;
        C1_5 = _C1_5;
        C1_6 = _C1_6;
        
        TX2_RSS2 = _TX2_RSS2;
        C2_1 = _C2_1;
        C2_2 = _C2_2;
        C2_3 = _C2_3;
        C2_4 = _C2_4;
        C2_5 = _C2_5;
        C2_6 = _C2_6;
        
        TX3_RSS3 = _TX3_RSS3;
        C3_1 = _C3_1;
        C3_2 = _C3_2;
        C3_3 = _C3_3;
        C3_4 = _C3_4;
        C3_5 = _C3_5;
        C3_6 = _C3_6;
        
        cout << "---------------" << endl;
        cout << "Node " << _nodeID << endl;
        cout << "RXDistX " <<  _RXDistX << endl;
        cout << "RXDistY " <<  _RXDistY << endl;
        cout << "TX1RXDist " <<  _TX1RXDist << endl;
        cout << "TX1_RSSI1 " <<  _TX1_RSSI1 << endl;
        cout << "C1_1 " <<  _C1_1 << endl;
        cout << "C1_2 " <<  _C1_2 << endl;
        cout << "C1_3 " <<  _C1_3 << endl;
        cout << "C1_4 " <<  _C1_4 << endl;
        cout << "C1_5 " <<  _C1_5 << endl;
        cout << "C1_6 " <<  _C1_6 << endl;
        cout << "TX2_RSS2 " <<  _TX2_RSS2 << endl;
        cout << "C2_1 " <<  _C2_1 << endl;
        cout << "C2_2 " <<  _C2_2 << endl;
        cout << "C2_3 " <<  _C2_3 << endl;
        cout << "C2_4 " <<  _C2_4 << endl;
        cout << "C2_5 " <<  _C2_5 << endl;
        cout << "C2_6 " <<  _C2_6 << endl;
        cout << "TX3_RSS3 " <<  _TX3_RSS3 << endl;
        cout << "C3_1 " <<  _C3_1 << endl;
        cout << "C3_2 " <<  _C3_2 << endl;
        cout << "C3_3 " <<  _C3_3 << endl;
        cout << "C3_4 " <<  _C3_4 << endl;
        cout << "C3_5 " <<  _C3_5 << endl;
        cout << "C3_6 " <<  _C3_6 << endl;
        
    }
    void draw()
    {
        stringstream strs;
        strs << "---------------" << endl;
        strs << "Node " << nodeID << endl;
        strs << "RXDistX " <<  RXDistX << " RXDistY " <<  RXDistY << " TX1RXDist " <<  TX1RXDist << endl;
        strs << "TX1_RSSI1 " <<  TX1_RSSI1 << endl;
        strs << "C1_1 " <<  C1_1 << " C1_2 " <<  C1_2 << " C1_3 " <<  C1_3 << " C1_4 " <<  C1_4 << " C1_5 " << C1_5 << " C1_6 " <<  C1_6 << endl;
        strs << "TX2_RSS2 " <<  TX2_RSS2 << endl;
        strs << "C2_1 " <<  C2_1 << " C2_2 " <<  C2_2 << " C2_3 " <<  C2_3 << " C2_4 " <<  C2_4 << " C2_5 " << C2_5 << " C2_6 " <<  C2_6 << endl;
        strs << "TX3_RSS3 " <<  TX3_RSS3 << endl;
        strs << "C3_1 " <<  C3_1 << " C3_2 " <<  C3_2 << " C3_3 " <<  C3_3 << " C3_4 " <<  C3_4 << " C3_5 " << C3_5 << " C3_6 " <<  C3_6 << endl;
        
        ofDrawBitmapStringHighlight(strs.str(), 15, 15);
    }
    //-----------------------------------------------------
    NodeReadings(int _nodeID,float _var1 = 0,float _var2 = 0,float _var3 = 0,float _var4 = 0,float _var5 = 0,float _var6 = 0) {

    }

    int nodeID;
    
    vector<float>data;
    
    float var1;
    float var2;
    float var3;
    float var4;
    float var5;
    float var6;
    
    float RXDistX;
    float RXDistY;
    float TX1RXDist;
    
    float TX1_RSSI1;
    float C1_1;
    float C1_2;
    float C1_3;
    float C1_4;
    float C1_5;
    float C1_6;
    
    float TX2_RSS2;
    float C2_1;
    float C2_2;
    float C2_3;
    float C2_4;
    float C2_5;
    float C2_6;
    
    float TX3_RSS3;
    float C3_1;
    float C3_2;
    float C3_3;
    float C3_4;
    float C3_5;
    float C3_6;
};

class ControlNode : public ofRectangle {

    public:
        ControlNode(int x,int y,float gridSpacingX,float gridSpacingY,int id);
        ~ControlNode();
    
        void updatePosition(int x,int y);
        void updateRXDist(float x,float y);
        void draw();
        void setOriginNode();
        void recalculateId();

        void setValues(float _var1,float _var2,float _var3,float _var4,float _var5,float _var6);
    
        void setValues(NodeReadings rs);
    
        void mouseOver(int x,int y);
        void nodeClicked(int x,int y,int button);
        vector<string> getReadings();
        float _x;
        float _y;
        bool isActive;
        int _id;
        float _gridSpacingX;
        float _gridSpacingY;
    private:
        NodeReadings nReading;
        bool isOrigin;
        bool isOver;
        float initialX;
        float initialY;
    protected:

};

#endif /* ControlNode_hpp */
