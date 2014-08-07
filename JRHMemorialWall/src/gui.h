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
    void hide(bool control = true);
    void toggleIsHidden();
    void onHideGuiButton();
    void onModeToggle();
    
    ofxPanel guiPanel;
    ofxButton saveSetupButton, hideGuiButton;
    ofxToggle modeToggle;
    ofParameterGroup visualSystemParams, cvParams;
    ofParameter<float> flowSpeed, timeSpeed, flowComplexity, horizontalForce, verticalForce, particleNeighborhood, particleRepulsion, contourFinderThresh;
    ofParameter<int> fadeAmt, blur, kinectMix;
    ofParameter<bool> showKinect, flipVertical;
    
    bool isHidden;
    
};