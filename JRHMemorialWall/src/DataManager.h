//
//  DataManager.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/26/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"

class DataManager{
    
public:
    DataManager();
    static void init();
    static string getTestVideoPath();
    
    static ofxXmlSettings settings;
    static const string PANELS;
    static const string STRIPS;
    
};