//
//  ledWave.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "ledWave.h"

ledWavePanels::ledWavePanels(int x, int y, int w, int h){
    _x = x;
    _y = y;
    _w = w;
    _h = h;
}

ledWaveStrip::ledWaveStrip(int x, int y, int w){
    _x = x;
    _y = y;
    _w = w;
    _h = 1;
}