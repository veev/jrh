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

ledWaveStrips::ledWaveStrips(int x, int y, int w, int h, int idNum, string topAddress, string bottomAddress, int numLeds, string host, int port) : ledWave(x,y,w,h,idNum){
    
   // cout<<"ledWaveStrips::ledWaveStrips("<<endl;
    
    type = DataManager::STRIPS;
    
    _topStripAddress = topAddress;
    _bottomStripAddress = bottomAddress;
    _numLeds = numLeds;
    
    topStripImage.allocate(numLeds, 1, OF_IMAGE_COLOR);
    bottomStripImage.allocate(numLeds, 1, OF_IMAGE_COLOR);
    
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

/*void ledWaveStrips::updateImage(ofImage image){
    ofImage newImage = image;
    newImage.update();
    newImage.crop(_x, _y, _w, 1);
    newImage.update();
    
    topStripImage = newImage;
    
    topStripImage.update();
    topStripImage = image;
    imageToCrop = image;
    
    topStripImage.update();
    imageToCrop.update();*/
//}

void ledWaveStrips::updateFbo(ofFbo * fbo){
    
    // cout<<"ledWaveStrips::updateFbo"<<endl;
    
    //TOP STRIP
    fbo->readToPixels(topStripImage);
    topStripImage.crop(_x, _y, _w, 1);
    //resize the image to the correct ledstrip size
    topStripImage.resize(_numLeds, 1);
    topStripImage.update();
    topStripPixels.setFromPixels(topStripImage.getPixels(), _numLeds, 1, 3);
    
    //BOTTOM STRIP
    fbo->readToPixels(bottomStripImage);
    bottomStripImage.crop(_x, _y+_h-1, _w, 1);
    //resize the image to the correct ledstrip size
    bottomStripImage.resize(_numLeds, 1);
    bottomStripImage.update();

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

void ledWaveStrips::drawToStrips(){
    //cout<<"ledWaveStrips::drawToStrips"<<endl;
    
    //set pixel alpha value as brightness
    //ofPixels * pixels = topStripImage.getPixelsRef();
    for(int i=0; i<topStripPixels.size();i++){
        ofColor c = topStripPixels.getColor(i, 0);
        c.setBrightness(c.a);
       // topStripPixels.setColor(i, c);
    }
    
   // topStripPixels.setNumChannels(3);
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