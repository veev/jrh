//
//  visualSystem.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#pragma once
#include "ofMain.h"
#include "ledWave.h"

class visualSystem{
    public:
    
    visualSystem();
    void addPanelsWave(int x, int y, int w, int h);
    void addStripWave(int x, int y, int w);
    void drawWaves();
    
    vector<ledWave> waves;  // create an empty vector of floats
};