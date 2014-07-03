//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "visualSystem.h"

visualSystem::visualSystem(){
    
}

//create an instance of the PanelsWave object
void visualSystem::addPanelsWave(int x, int y, int w, int h){
    
    ledWave wave = ledWavePanels(x, y, w, h);
    waves.push_back(wave);
    
}

//create an instance of the StripWave object
void visualSystem::addStripWave(int x, int y, int w){
    
    ledWave wave = ledWaveStrip(x, y, w);
    waves.push_back(wave);
    
}

void visualSystem::drawWaves(){
    
   // cout<<"drawWaves"<<endl;
    //cout<<"waves.size(): "<<waves.size()<<endl;
    
    //draw outline for the waves
    ofSetColor(255, 0, 0);
    
    for (int i=0;i<waves.size();i++){
        //cout<<"draw wave " << i << endl;
        ofRect(waves[i]._x, waves[i]._y, waves[i]._w, waves[i]._h);
    }
    
}