//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "displaySystem.h"

displaySystem::displaySystem(){
    
}

//update the display with a new image
void displaySystem::updateDisplay(ofFbo frame){
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
    ofSetColor(255);
    _frame.draw(0,0);
    drawWaves();
}

void displaySystem::drawWaves(){
    
   // cout<<"drawWaves"<<endl;
    //cout<<"waves.size(): "<<waves.size()<<endl;
    
    //draw outline for the waves
    ofSetColor(255, 0, 0);
    ofNoFill();
    
    for (int i=0;i<waves.size();i++){
        //cout<<"draw wave " << i << endl;
        ofRect(waves[i]._x, waves[i]._y, waves[i]._w, waves[i]._h);
    }
    
}