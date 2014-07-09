//
//  DataManager.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/26/14.
//
//

#include "DataManager.h"

const string DataManager::PANELS = "panels";
const string DataManager::STRIPS = "strips";

//initialize the static variable
ofxXmlSettings DataManager::settings = ofxXmlSettings();

DataManager::DataManager(){
    
    
}

void DataManager::init(){
    //load settings
    settings.loadFile("settings.xml");
}

string DataManager::getTestVideoPath(){
    return settings.getValue("testVideoPath", "movies/test.mov");
    
}

/*
void DataManager::saveWaveSetup(vector<ledWave> * waves){
    settings.pushTag("waves");
    
    for(int i=0; i < DataManager::settings.getNumTags("wave"); i++){
        ledWave * w = &waves->at(i);
        settings.setAttribute("wave", "x", w->_x, i);
        settings.getAttribute("wave", "y", w->_y, i);
    }
    
    //make sure we pop back to the root after pushing...
    DataManager::settings.popTag();

}*/