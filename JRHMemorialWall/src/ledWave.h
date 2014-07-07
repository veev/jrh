//
//  ledWave.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#pragma once
#include "ofMain.h"
#include "DataManager.h";

class ledWave{
    
    public:
    int _x, _y, _w, _h;
    string type;
    
};

class ledWavePanels: public ledWave{
    
    public:
        ledWavePanels(int x, int y, int w, int h);
};

class ledWaveStrip: public ledWave{
    
    public:
        ledWaveStrip(int x, int y, int w, int h);
    
};