//
//  ledWave.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "ledWave.h"

ledWave::ledWave(int x, int y, int w, int h){
    _x = x;
    _y = y;
    _w = w;
    _h = h;
}

ledWavePanels::ledWavePanels(int x, int y, int w, int h) : ledWave(x,y,w,h){
    type = DataManager::PANELS;
}

ledWaveStrip::ledWaveStrip(int x, int y, int w, int h) : ledWave(x,y,w,h){
    type = DataManager::STRIPS;
}

void ledWave::updateFbo(ofFbo * fbo){
    
    //get the right portion of the fbo and place it into the wave object
    
    
    
}