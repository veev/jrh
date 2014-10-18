//
//  gui.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "gui.h"

gui::gui(){
    //setup listeners
   hideGuiButton.addListener(this, &gui::onHideGuiButton);
   // modeToggle.addListener(this, &gui::onModeToggle);
    isHidden = false;
    
}

void gui::setup(int x){
    
    //display system
    dsParams.setName("Display System");
    dsParams.add(mirrorLEDStrips.set("mirror strips", false));
    
    dsParams.add(ledPanelsColor.set("Panel Color",ofColor(255),ofColor(0, 0),ofColor(255)));
    dsParams.add(ledPanelHue.set("Panel Hue",0,0,255));
    dsParams.add(ledPanelBrightness.set("Panel Brightness",0,0,255));
    dsParams.add(ledPanelSaturation.set("Panel Saturation",0,0,255));

    dsParams.add(ledStripsColor.set("Strip Color",ofColor(255),ofColor(0, 0),ofColor(255)));
    dsParams.add(ledStripHue.set("Strip Hue",0,0,255));
    dsParams.add(ledStripBrightness.set("Strip Brightness",0,0,255));
    dsParams.add(ledStripSaturation.set("Strip Saturation",0,0,255));

    //add event listeners here to update color when hue changes, and vice-versus
    
    //visualSystem
    visualSystemParams.setName("Visual System");
	visualSystemParams.add(flowSpeed.set("turbulence",.002,0,.1));
    visualSystemParams.add(timeSpeed.set("particle speed",.2,-1,1));
    visualSystemParams.add(flowComplexity.set("density",2,0,20));
    visualSystemParams.add(horizontalForce.set("H force",.2,-1,1));
    visualSystemParams.add(verticalForce.set("V force",.2,0,1));
    visualSystemParams.add(fadeAmt.set("fade amount",100,0,255));
    visualSystemParams.add(particleNeighborhood.set("p neighborhood",4,0,10));
    visualSystemParams.add(particleRepulsion.set("p repulsion",1,-1,1));
    visualSystemParams.add(blur.set("blur",1,0,10));
    visualSystemParams.add(particleBrightnessShift.set("Particle Brightness",10,0,100));
    visualSystemParams.add(depthMapCutoff.set("Depth Cutoff",200,0,255));
    visualSystemParams.add(depthMapForce.set("Depth Force",2.2,0,10));
    visualSystemParams.add(textFadeTo.set("Text Fade Amt",200,0,255));



    //computer vision params
    cvParams.setName("Computer Vision");
    cvParams.add(contourFinder.set("Contour Finder", false));
    cvParams.add(contourFinderThresh.set("Contour Threshold",0,0,255));
    cvParams.add(showKinect.set("SHOW KINECT", false));
    cvParams.add(kinectMix.set("Kinect Mix", 50, 0, 255));
    cvParams.add(flipVertical.set("Flip V", false));
    cvParams.add(flipH.set("Flip H", false));
    

    
    //create the gui
    guiPanel.setup("GUI","gui_settings.xml", x,10);
    guiPanel.setWidthElements(200);
    
    //guiPanel.setup(visualSystemParams);
    guiPanel.add(disableSignal.set("LEDs ON", false));
    guiPanel.add(saveSetupButton.setup("SAVE SETUP"));
    guiPanel.add(modeToggle.setup("TOGGLE LIVE MODE", true));
    guiPanel.add(dsParams);
    guiPanel.add(visualSystemParams);
    guiPanel.add(cvParams);
    guiPanel.loadFromFile("gui_settings.xml");
}

void gui::update(){
    //update led panel color
    ofColor c = ledPanelsColor;
    c.setHue(ledPanelHue);
    c.setSaturation(ledPanelSaturation);
    c.setBrightness(ledPanelBrightness);
    ledPanelsColor.set(c);
    
    //update led strip color
    c = ledStripsColor;
    c.setHue(ledStripHue);
    c.setSaturation(ledStripSaturation);
    c.setBrightness(ledStripBrightness);
    ledStripsColor.set(c);
}

void gui::draw(){
    guiPanel.draw();
}

void gui::hide(bool control){
    isHidden = control;
}

void gui::onHideGuiButton(){
    isHidden = true;
}