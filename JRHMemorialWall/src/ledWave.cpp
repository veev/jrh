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
    topStripPixels.allocate(w, 1, OF_IMAGE_COLOR);

    
    bottomStripImage.allocate(w, 1, OF_IMAGE_COLOR);
    
   // topStripPixels.clear();
   // topStripImage.clear();
    bottomStripPixels.allocate(w, 1, OF_IMAGE_COLOR);
    
    imageToCrop.allocate(800,600, OF_IMAGE_COLOR);

    
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
    
   // topStripImage.cropFrom(fbo->readToPixels(<#ofPixels &pixels#>), <#int x#>, <#int y#>, <#int w#>, <#int h#>)
    
     //fbo->draw(50,50);
    
   // ofImage ts;
  //  ofImage bs;
 //  topStripImage.allocate(800, 600, OF_IMAGE_COLOR);
   // bottomStripImage.allocate(800, 600, OF_IMAGE_COLOR);
    
    //get the right portion of the fbo and place it into the wave object
    //ofPixels pixelsToCrop;
  //  pixelsToCrop.allocate(800, 600, OF_IMAGE_COLOR);
    
//    fbo->readToPixels(pixelsToCrop);
    //ofTexture texture;
   // texture.allocate(_w,_h,GL_RGB);
    
    
    
 //   newFbo.readToPixels(topStripPixels);
    ofPixels pixels;
    newFbo.readToPixels(pixels);
    topStripImage.setFromPixels(pixels);

    topStripImage.update();
    
   // topStripPixels.crop(_x, _y, _w, 1);
    topStripImage.crop(_x, _y, _w, 1);
    
  //  texture.loadData(topStripPixels.getPixelsRef(), _w, 1, GL_RGB);
    
   // texture.readToPixels(topStripImage);
    
   // topStripImage.update();
    
    topStripFBO.begin();
    topStripImage.draw(0, 0);
    topStripFBO.end();
    
  //  topStripImage.update();
    
//    ofSetColor(255);
//    
   
    
   // fbo->readToPixels(topStripImage);

   // fbo->readToPixels(bottomStripImage);
    
   // topStripImage.crop(_x,_y,_w,1);
   // bottomStripImage.crop(_x,_y+_h-1,_w,1);

   // imageToCrop.setFromPixels(pixelsToCrop);
    
    //fbo->readToPixels(bottomStripImage);
    
    //**from OF docs:**
    //This crops the pixels to a new width and height.
    //As a word of caution this reallocates memory and can be a bit expensive if done a lot.
    
//    pixelsToCrop.crop(_x,_y,_w,1);
//    pixelsToCrop.setNumChannels(3);
    
   // pixelsToCrop.cropTo(topStripPixels, _x,_y,_w,1);
   // pixelsToCrop.cropTo(bottomStripPixels, _x,_y+_h-1,_w,1);
    
//    ofPixels debug;
//    debug.setImageType(OF_IMAGE_COLOR);
//    debug.allocate(_w, 1, OF_IMAGE_COLOR);
    
//    for(int i = 0; i < _w; ++i)
//    {
//        debug.setColor(i, ofColor(255, 0, 0));
//    }
    
//    topStripImage.setFromPixels(pixelsToCrop);
//    topStripImage.setFromPixels(debug);
//    topStripImage.update();
    
    
   /* for(int i = 0; i < topStripImage.getWidth(); ++i)
    {
        cout << topStripImage.getColor(i, 0) << endl;
    }*/
    
   // topStripImage.setFromPixels(topStripPixels);
   // bottomStripImage.setFromPixels(bottomStripPixels);
    
    //crop the top line of pixels
  // topStripImage.cropFrom(imageToCrop, _x,_y,_w,1);
    
    //crop the bottom line of pixels
   // bottomStripImage.cropFrom(imageToCrop, _x,_y+_h-1,_w,1);
  /*
    topStripFBO.begin();
    topStripImage.draw(0, 0);
    topStripFBO.end();
    
    bottomStripFBO.begin();
    bottomStripImage.draw(0, 0);
    bottomStripFBO.end();*/
    
   // topStripImage.setFromPixels(topStrip);
   // bottomStripImage.setFromPixels(bottomStrip);
}


void ledWavePanels::draw(int y){
  //  cout<<"ledWavePanels::draw(int " << y << endl;
 //   cout<<"_fbo: "<<_fbo.<< endl;
    _fbo.draw(0,y);
}

void ledWaveStrips::draw(int x, int y){
    topStripImage.draw(x, y);
    topStripFBO.draw(x, y+5);
    //imageToCrop.draw(50,50);
}

//STRIPS
unsigned char * ledWaveStrips::getTopStripPixels(){
    //return topStripPixels.getPixels();
    return topStripImage.getPixels();
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