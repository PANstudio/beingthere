//
//  MapEditorButtons.hpp
//  H_A_R_P_S
//
//  Created by David Haylock on 10/01/2016.
//
//

#ifndef MapEditorButtons_hpp
#define MapEditorButtons_hpp

#include <stdio.h>
#include "ofMain.h"

class MapButtons {
    public:
        void setupButtons(int size) {
            
            
            
        }
    
        void makeBigger();
        void makeSmaller();
    
        void fireEvent(int button);
        int getWhichBlock();
    
        void draw(int x,int y);
    
    private:
    
    
};

#endif /* MapEditorButtons_hpp */
