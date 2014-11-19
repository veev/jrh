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
    debugYOffset = 300;
    mirrorStrips = false;
    
    width = height = 0;
}

void displaySystem::init(){
    
}

//create an instance of the PanelsWave object
void displaySystem::addPanelsWave(int x, int y, int w, int h, int idNum){
    
    ledWavePanels * wave = new ledWavePanels(x, y, w, h, idNum);
    wavesPanels.push_back(wave);
    
    //update overall ds width and height values
    if(w>width)
        width = w;
    height += h;
}

//create an instance of the StripWave object
void displaySystem::addStripWave(int x, int y, int w, int h, int idNum, string topAddress, string bottomAddress, int numLeds, string host, int port){
    ledWaveStrips * wave = new ledWaveStrips(x, y, w, h, idNum, topAddress, bottomAddress, numLeds, host, port);
    wavesStrips.push_back(wave);
}

//update the display with a new image
void displaySystem::updateDisplay(ofFbo * frame){
    _frame = frame;
    
    //update the fbo on the wave
    for (int i=0;i<wavesPanels.size();i++){
        ledWavePanels * w = wavesPanels.at(i);
        w->updateFbo(frame);
    }
    
    //make a copy of the FBO and color it...
    ofFbo *colorCopy = new ofFbo();
    colorCopy->allocate(frame->getWidth(), frame->getHeight(), GL_RGB);
    //draw into the copy
    colorCopy->begin();
    ofSetColor(ledStripsColor);
    frame->draw(0,0);
    colorCopy->end();
    
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips * w = wavesStrips.at(i);
        w->updateFbo(colorCopy, mirrorStrips);
    }
    
    delete colorCopy;
}


void displaySystem::draw(int offSetY){
    ofSetColor(255);
    
    if(mode == TEST_MODE){
        //render test mode
        ofSetColor(255);
        _frame->draw(0,offSetY);
    }
     drawWaves();
}

void displaySystem::drawWaves(){
    //cout<<"drawWaves"<<endl;
    //cout<<"waves.size(): "<<waves.size()<<endl;
    
    //draw outline for the waves
    ofNoFill();
    ofSetLineWidth(1);
    
    int y=0;
    
    //PANELS
    for (int i=0;i<wavesPanels.size();i++)
    {
        ledWavePanels * w = wavesPanels.at(i);
        //cout<<"draw wave " << i << endl;
        
        if(mode == TEST_MODE){
            //draw red boxes for all the panels waves
            ofSetColor(255, 0, 0, 255);
            ofRect(w->_x, w->_y+debugYOffset, w->_w, w->_h);
            ofDrawBitmapString(ofToString(w->_idNum), w->_x+2, w->_y+12+debugYOffset);
        }
        
        //draw the panels to the screen
        ofSetColor(ledPanelsColor);
        w->draw(y);
        y+=w->_h;
    }
    
    //STRIPS
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips * w = wavesStrips.at(i);
        //cout<<"draw wave " << i << endl;
        
        if(mode == TEST_MODE){
            //draw blue boxes for all the strips waves
            ofSetColor(0, 0, 255, 255);
            ofRect(w->_x, w->_y+debugYOffset, w->_w, w->_h);
            ofDrawBitmapString(ofToString(w->_idNum), w->_x+2, w->_y+12+debugYOffset);
            
            //draw strips below
            int yOffset = 200;
            ofSetColor(255);
            ofDrawBitmapString(ofToString(w->_idNum), 10, yOffset+(i*20)+7);
            w->draw(30, yOffset+(i*20));
            w->drawToStrips();
        }
    }
    
}

//Find the wave that is clicked on and make that the draggable one
void displaySystem::mousePressed(int x, int y, int button){
    
     for (int i=0;i<wavesPanels.size();i++){
         ledWavePanels * w = wavesPanels.at(i);
         if(w->hitTest(x,y)){
             draggableWave = w;
             mousePressedX = x-w->_x;
             mousePressedY = y-w->_y;
             return;
         }
     }
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips * w = wavesStrips.at(i);
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
    cout<<"displaySystem::saveWaveSetup(){"<<endl;
    
    DataManager::settings.pushTag("waves");
    
    for (int i=0;i<wavesPanels.size();i++){
        ledWavePanels * w = wavesPanels.at(i);
        DataManager::settings.setAttribute("wave", "x", w->_x, w->_idNum-1);
        DataManager::settings.setAttribute("wave", "y", w->_y, w->_idNum-1);
    }
    for (int i=0;i<wavesStrips.size();i++){
        ledWaveStrips * w = wavesStrips.at(i);
        DataManager::settings.setAttribute("wave", "x", w->_x, w->_idNum-1);
        DataManager::settings.setAttribute("wave", "y", w->_y, w->_idNum-1);
    }
    
    //make sure we pop back to the root after pushing...
    DataManager::settings.popTag();
    
    //save the file
    DataManager::settings.saveFile();
}

void displaySystem::clear(){
    //send clear signal to LED strips
    for (int i=0;i<wavesStrips.size();i++){
        wavesStrips.at(i)->clear();
    }
}