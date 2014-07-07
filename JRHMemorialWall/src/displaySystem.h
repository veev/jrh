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

class displaySystem{
    public:
    
    displaySystem();
    void addPanelsWave(int x, int y, int w, int h);
    void addStripWave(int x, int y, int w, int h);
    void draw();
    void drawWaves();
    void updateDisplay(ofFbo frame);
    
    vector<ledWave> waves;  // create an empty vector of floats
    
private:
    ofFbo _frame;
};