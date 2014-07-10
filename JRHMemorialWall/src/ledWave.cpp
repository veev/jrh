//
//  ledWave.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "ledWave.h"

ledWave::ledWave(int x, int y, int w, int h, int idNum){
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _idNum = idNum;
}

ledWavePanels::ledWavePanels(int x, int y, int w, int h, int idNum) : ledWave(x,y,w,h,idNum){
    type = DataManager::PANELS;
    
    //allocate the fbo size
    _fbo.allocate(w, h);
    image.allocate(w, h, OF_IMAGE_COLOR);
    
}

ledWaveStrips::ledWaveStrips(int x, int y, int w, int h, int idNum) : ledWave(x,y,w,h,idNum){
    type = DataManager::STRIPS;
    
    topStrip.allocate(w, 1, OF_IMAGE_COLOR);
    bottomStrip.allocate(w, 1, OF_IMAGE_COLOR);

}

void ledWavePanels::updateFbo(ofFbo * fbo){
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

void ledWaveStrips::updateFbo(ofFbo * fbo){
    //get the right portion of the fbo and place it into the wave object
    fbo->readToPixels(topStrip);
    fbo->readToPixels(bottomStrip);
    
    //**from OF docs:**
    //This crops the pixels to a new width and height.
    //As a word of caution this reallocates memory and can be a bit expensive if done a lot.
    
    //crop the top line of pixels
    topStrip.crop(_x,_y,_w,1);
    
    //crop the bottom line of pixels
    bottomStrip.crop(_x,_y+_h-1,_w,1);
}


void ledWavePanels::draw(int y){
    cout<<"ledWavePanels::draw(int " << y << endl;
 //   cout<<"_fbo: "<<_fbo.<< endl;
    _fbo.draw(0,y);
}

unsigned char * ledWaveStrips::getTopStripPixels(){
    return topStrip.getPixels();
}

unsigned char * ledWaveStrips::getBottomStripPixels(){
    return bottomStrip.getPixels();
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