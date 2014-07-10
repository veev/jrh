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
//#include "displaySystem.h"
#include "ledWave.h"

class DataManager{
    
public:
    DataManager();
    static void init();
    //static void saveWaveSetup(vector<ledWave> & waves);
    
    static string getTestVideoPath();
    static string getLEDStripHost();
    static int getLEDStripPort();
    
    static ofxXmlSettings settings;
    static const string PANELS;
    static const string STRIPS;
    
};