//
//  gui.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "DataManager.h"

class gui{
    
public:
    gui();
    void setup();
    void draw();
    
    ofxPanel guiPanel;
    ofxButton saveSetupButton;
    
};