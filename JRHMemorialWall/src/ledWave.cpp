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

ledWaveStrips::ledWaveStrips(int x, int y, int w, int h, int idNum, string topAddress, string bottomAddress) : ledWave(x,y,w,h,idNum){
    type = DataManager::STRIPS;
    
    _topStripAddress = topAddress;
    _bottomStripAddress = bottomAddress;
    
    topStripFBO.allocate(w, 1, GL_RGB);
    
    topStripImage.allocate(w, 1, OF_IMAGE_COLOR);
   // topStripPixels.allocate(800, 600, OF_PIXELS_RGB);

    
    bottomStripImage.allocate(w, 1, OF_IMAGE_COLOR);
    
   // topStripPixels.clear();
   // topStripImage.clear();
 //   bottomStripPixels.allocate(w, 1, OF_IMAGE_COLOR);
    
   // imageToCrop.allocate(800,600, OF_IMAGE_COLOR);

    
  /*  topStrip.allocate(w, 1, OF_IMAGE_COLOR_ALPHA);
    bottomStrip.allocate(w, 1, OF_IMAGE_COLOR_ALPHA);
    topStripImage.allocate(w, 1, OF_IMAGE_COLOR_ALPHA);
    bottomStripImage.allocate(w, 1, OF_IMAGE_COLOR_ALPHA);*/

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

void ledWaveStrips::updateImage(ofImage image){
    ofImage newImage = image;
    newImage.update();
    newImage.crop(_x, _y, _w, 1);
    newImage.update();
    
    topStripImage = newImage;
    
    //topStripImage.cropFrom(image, _x, _y, _w, 1);
    topStripImage.update();
    /*topStripImage = image;
    imageToCrop = image;
    
    topStripImage.update();
    imageToCrop.update();*/
}

void ledWaveStrips::updateFbo(ofFbo * fbo){
    
    cout<<"ledWaveStrips::updateFbo"<<endl;
    
    ofFbo newFbo;
    newFbo = *fbo;
   
    fbo->readToPixels(topStripImage);
    //topStripImage.setFromPixels(topStripPixels);
    
    //colors.clear();
   
    
    topStripImage.crop(_x, _y, _w, 1);
    topStripImage.update();
    
    
    // Transfer grab data to the pixel array
  /*  ofPixels pixels = topStripImage.getPixelsRef();
    
    for (int i = 0; i < pixels.size(); i++)
    {
        cout<<"push a color"<<endl;
        colors.push_back(pixels.getColor(i, 0));
    }*/
    
}


void ledWavePanels::draw(int y){
  //  cout<<"ledWavePanels::draw(int " << y << endl;
 //   cout<<"_fbo: "<<_fbo.<< endl;
    _fbo.draw(0,y);
}

void ledWaveStrips::draw(int x, int y){
    topStripImage.draw(x, y);
}

//STRIPS
unsigned char * ledWaveStrips::getTopStripPixels(){
    
    unsigned char * pixels = topStripImage.getPixels();
    return pixels;
}


unsigned char * ledWaveStrips::getBottomStripPixels(){
    return bottomStripImage.getPixels();
}

string ledWaveStrips::getTopStripAddress(){
    return _topStripAddress;
}

string ledWaveStrips::getBottomStripAddress(){
    return _bottomStripAddress;
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