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
    void setup(int x=0);
    void update();
    void draw();
    void hide(bool control = true);
    void toggleIsHidden();
    void onHideGuiButton();
    void onModeToggle();
    
    ofxPanel guiPanel;
    ofxButton saveSetupButton, hideGuiButton;
    ofxToggle modeToggle;
    ofParameterGroup visualSystemParams, cvParams, dsParams;
    ofParameter<float> flowSpeed, timeSpeed, flowComplexity, horizontalForce, verticalForce, particleNeighborhood, particleRepulsion, contourFinderThresh, depthMapCutoff, depthMapForce;
    ofParameter<int> fadeAmt, blur, kinectMix, ledPanelHue, ledStripHue, ledPanelBrightness, ledStripBrightness, ledPanelSaturation, ledStripSaturation, particleBrightnessShift;
    ofParameter<bool> showKinect, flipVertical, flipH, mirrorLEDStrips, disableSignal, contourFinder;
    ofParameter<ofColor> ledPanelsColor, ledStripsColor;
    
    bool isHidden;
    
};