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
    ofFbo * getFrame();
    ofImage getFrameAsImage();
    void loadTestMovie(string path);
    
    ofVideoPlayer 		testMovie;
    ofFbo               display;
    ofFbo *             displayPointer;
    ofImage             image;
};