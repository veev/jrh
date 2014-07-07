//
//  visualSystem.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/7/14.
//
//

#pragma once
#include "ofMain.h"

class visualSystem{
    
    public:
    visualSystem();
    ofFbo getFrame();
    void loadTestMovie(string path);
    
    ofVideoPlayer 		testMovie;
    ofFbo               display;
};