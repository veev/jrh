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
    
    //allocate the fbo size
    _fbo.allocate(w, h);
    image.allocate(w, h, OF_IMAGE_COLOR);
}

ledWavePanels::ledWavePanels(int x, int y, int w, int h) : ledWave(x,y,w,h){
    type = DataManager::PANELS;
    
}

ledWaveStrip::ledWaveStrip(int x, int y, int w, int h) : ledWave(x,y,w,h){
    type = DataManager::STRIPS;
}

void ledWave::updateFbo(ofFbo * fbo){
    //get the right portion of the fbo and place it into the wave object
    fbo->readToPixels(image);
    
    //**from OF docs:**
    //This crops the pixels to a new width and height.
    //As a word of caution this reallocates memory and can be a bit expensive if done a lot.
    image.crop(_x,_y,_w,_h);
    
    _fbo.begin();
    image.draw(0,0);
    _fbo.end();
}

void ledWave::draw(int y){
    _fbo.draw(0,y);
}

bool ledWave::hitTest(int x, int y){
    if(x > _x ){
        if (x < _x + _w){
            if(y > _y){
                if(y < _y+_h){
                    return true;
                }
            }
        }
    }
    return false;
}