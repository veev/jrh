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
    _fbo.allocate(w, h, GL_RGBA);
    image.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
    
}

ledWaveStrips::ledWaveStrips(int x, int y, int w, int h, int idNum, string topAddress, string bottomAddress, int numLeds, string host, int port) : ledWave(x,y,w,h,idNum){
    
   // cout<<"ledWaveStrips::ledWaveStrips("<<endl;
    
    type = DataManager::STRIPS;
    
    _topStripAddress = topAddress;
    _bottomStripAddress = bottomAddress;
    _numLeds = numLeds;
    
    topStripImage.allocate(_w, 1, OF_IMAGE_COLOR);
    bottomStripImage.allocate(_w, 1, OF_IMAGE_COLOR);
    
    topStripPixels.allocate(numLeds, 1, OF_IMAGE_COLOR);
    bottomStripPixels.allocate(numLeds, 1, OF_IMAGE_COLOR);
    
  //  cout<<"DataManager::getLEDStripHost(): "<<DataManager::getLEDStripHost()<<endl;
    
  //  cout<<"host: "<<host<<endl;
  //  cout<<"port: "<<port<<endl;
    
    lgs = new lumigeekSender();
    
    lgs->setup(host, port, numLeds);

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


void ledWaveStrips::updateFbo(ofFbo * fbo, bool mirror){
    
    // cout<<"ledWaveStrips::updateFbo"<<endl;
    
    //TOP STRIP
    ofImage imageToCrop;
    imageToCrop.allocate(600, 400, OF_IMAGE_COLOR);
    fbo->readToPixels(imageToCrop);
    topStripImage.cropFrom(imageToCrop, _x, _y, _w, 1);

    //resize the image to the correct ledstrip size
    topStripImage.resize(_numLeds, 1);
    topStripImage.update();
    
    if(mirror)
        topStripImage.mirror(false, true);
    
    topStripPixels.setFromPixels(topStripImage.getPixels(), _numLeds, 1, 3);
    
    //BOTTOM STRIP
    bottomStripImage.cropFrom(imageToCrop, _x, _y+_h-1, _w, 1);
    //resize the image to the correct ledstrip size
    bottomStripImage.resize(_numLeds, 1);
    bottomStripImage.update();
    if(mirror)
        bottomStripImage.mirror(false, true);
    bottomStripPixels.setFromPixels(bottomStripImage.getPixels(), _numLeds, 1, 3);
    
    
}




void ledWavePanels::draw(int y){
  //  cout<<"ledWavePanels::draw(int " << y << endl;
 //   cout<<"_fbo: "<<_fbo.<< endl;
    _fbo.draw(0,y);
}

void ledWaveStrips::draw(int x, int y){
    topStripImage.draw(x, y);
    bottomStripImage.draw(x, y+5);
}

void ledWaveStrips::drawToStrips(bool mirror){
    
    lgs->send(topStripPixels.getPixels(), _topStripAddress);
    lgs->send(bottomStripPixels.getPixels(), _bottomStripAddress);
    
}

//STRIPS
unsigned char * ledWaveStrips::getTopStripPixels(){
    
    unsigned char * pixels = topStripImage.getPixels();
    return pixels;
}


unsigned char * ledWaveStrips::getBottomStripPixels(){
    return bottomStripImage.getPixels();
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

void ledWaveStrips::clear(){
    
    lgs->clear();
    
}