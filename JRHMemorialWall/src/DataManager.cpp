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