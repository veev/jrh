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

//update the display with a new image
void displaySystem::updateDisplay(ofFbo * frame){
    _frame = frame;
}

//create an instance of the PanelsWave object
void displaySystem::addPanelsWave(int x, int y, int w, int h){
    
    ledWave wave = ledWavePanels(x, y, w, h);
    waves.push_back(wave);
    
}

//create an instance of the StripWave object
void displaySystem::addStripWave(int x, int y, int w, int h){
    ledWave wave = ledWaveStrip(x, y, w, h);
    waves.push_back(wave);
}

void displaySystem::draw(){
    if(mode == TEST_MODE){
        //render test mode
        ofSetColor(255);
        _frame->draw(0,0);
        drawWaves();
    }
    else if (mode == LIVE_MODE){
        //render live mode]
        
    }
}

void displaySystem::drawWaves(){
    
    //cout<<"drawWaves"<<endl;
    //cout<<"waves.size(): "<<waves.size()<<endl;
    
    //draw outline for the waves
       ofNoFill();
    
    for (int i=0;i<waves.size();i++){
        ledWave w = waves[i];
        //cout<<"draw wave " << i << endl;
        if(w.type == DataManager::PANELS)
            ofSetColor(255, 100, 100);
        else
            ofSetColor(100, 100, 255);
        
        ofRect(w._x, w._y, w._w, w._h);

    }
    
}

void displaySystem::enterLiveMode(){
    mode = LIVE_MODE;
}

void displaySystem::enterTestMode(){
    mode = TEST_MODE;
}