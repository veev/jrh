//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "displaySystem.h"

const string displaySystem::TEST_MODE = "test_mode";
const string displaySystem::LIVE_MODE = "live_mode";

displaySystem::displaySystem(){
    mode = TEST_MODE;
}

void displaySystem::init(){
    //setup the lumigeek sender class
    lgs.setup(DataManager::getLEDStripHost(), DataManager::getLEDStripPort());
}

//create an instance of the PanelsWave object
void displaySystem::addPanelsWave(int x, int y, int w, int h, int idNum){
    
    ledWavePanels wave = ledWavePanels(x, y, w, h, idNum);
    wavesPanels.push_back(wave);
    
}

//create an instance of the StripWave object
void displaySystem::addStripWave(int x, int y, int w, int h, int idNum, string topAddress, string bottomAddress){
    ledWaveStrips wave = ledWaveStrips(x, y, w, h, idNum, topAddress, bottomAddress);
    wavesStrips.push_back(wave);
}

//update the display with a new image
void displaySystem::updateDisplay(ofFbo * frame){
    _frame = frame;
    
   // _frame->draw(0, 0);
    
    //update the fbo on the wave
    for (int i=0;i<wavesPanels.size();i++){
        ledWavePanels w = wavesPanels.at(i);
        w.updateFbo(frame);
    }
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips w = wavesStrips.at(i);
        //frame->draw(50,50);
        w.updateFbo(frame);
    }
}

void displaySystem::updateDisplayAsImage(ofImage image){
   /*
    cout<<"displaySystem::updateDisplayAsImage"<<endl;
    
    frameImage = image;
    frameImage.update();
    
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips w = wavesStrips.at(i);
        //frame->draw(50,50);
        w.updateImage(frameImage);
    }
    */
}

void displaySystem::draw(){
    //_frame->draw(0,0);
    ofSetColor(255);
    
   // frameImage.draw(50, 50);
    
    
    if(mode == TEST_MODE){
        //render test mode
        ofSetColor(255);
        _frame->draw(0,0);
       
    }
     drawWaves();
}

void displaySystem::drawWaves(){
    //cout<<"drawWaves"<<endl;
    //cout<<"waves.size(): "<<waves.size()<<endl;
    
    //draw outline for the waves
    ofNoFill();
    
    int y=0;
    
    for (int i=0;i<wavesPanels.size();i++)
    {
        ledWavePanels w = wavesPanels.at(i);
        //cout<<"draw wave " << i << endl;
        
        if(mode == TEST_MODE){
            //draw boxes for all the waves
            ofSetColor(255, 100, 100);
            ofRect(w._x, w._y, w._w, w._h);
        }
        else{
            //draw just the panels to the screen
          //  w.image.draw(0, y);
            w.image.draw(200, y);
            w.draw(y);
            y+=w._h;
        }
    }
    
    //STRIPS
    for (int i=0;i<1;i++){
        ledWaveStrips w = wavesStrips.at(i);
        //cout<<"draw wave " << i << endl;
        
        if(mode == TEST_MODE){
            //draw boxes for all the waves
            ofSetColor(100, 100, 255);
            ofRect(w._x, w._y, w._w, w._h);
            
            ofSetColor(255);
            //w.imageToCrop.draw(i*20, i*20);
            //w.topStripImage.draw(10, 620+(i*10));
                     // w.bottomStripImage.draw(10, 620+(i*10)+5);
            
          //  w.imageToCrop.draw(i*10, i*10);
            
            
        }
        
        w.draw(10, 620+(i*10));
        
      
            int numPixels = w._w*3;
            //for the led strips, send the pixel data to the lumigeekSender
            lgs.send(w.getTopStripPixels(), w.getTopStripAddress(), numPixels);
            lgs.send(w.getBottomStripPixels(), w.getBottomStripAddress(), numPixels);
        
       // }
    }
    
}

//Find the wave that is clicked on and make that the draggable one
void displaySystem::mousePressed(int x, int y, int button){
    
     for (int i=0;i<wavesPanels.size();i++){
         ledWavePanels * w = & wavesPanels.at(i);
         if(w->hitTest(x,y)){
             draggableWave = w;
             mousePressedX = x-w->_x;
             mousePressedY = y-w->_y;
             return;
         }
     }
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips * w = & wavesStrips.at(i);
        if(w->hitTest(x,y)){
            draggableWave = w;
            mousePressedX = x-w->_x;
            mousePressedY = y-w->_y;
            return;
        }
    }
    
}

//drag the wave that has been clicked on
void displaySystem::mouseDragged(int x, int y, int button){
    if(draggableWave){
        draggableWave->_x = x - mousePressedX;
        draggableWave->_y = y - mousePressedY;
    }
}

//stop dragging the wave
void displaySystem::mouseReleased(int x, int y, int button){
    draggableWave = NULL;
}


void displaySystem::enterLiveMode(){
    mode = LIVE_MODE;
}

void displaySystem::enterTestMode(){
    mode = TEST_MODE;
}

void displaySystem::saveWaveSetup(){
    DataManager::settings.pushTag("waves");
    
    for (int i=0;i<wavesPanels.size();i++){
        ledWavePanels * w = & wavesPanels.at(i);
        DataManager::settings.setAttribute("wave", "x", w->_x, w->_idNum-1);
        DataManager::settings.setAttribute("wave", "y", w->_y, w->_idNum-1);
    }
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips * w = & wavesStrips.at(i);
        DataManager::settings.setAttribute("wave", "x", w->_x, w->_idNum-1);
        DataManager::settings.setAttribute("wave", "y", w->_y, w->_idNum-1);
    }
    
    /*for(int i=0; i < DataManager::settings.getNumTags("wave"); i++){
        ledWave * w = &wavesPanels.at(i);
        DataManager::settings.setAttribute("wave", "x", w->_x, w->_idNum-1);
        DataManager::settings.setAttribute("wave", "y", w->_y, w->_idNum-1);
    }*/
    
    
    //make sure we pop back to the root after pushing...
    DataManager::settings.popTag();
    
    //save the file
    DataManager::settings.saveFile();
}