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
    
}

void gui::setup(){
    
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

    
    //create the gui
    guiPanel.setup("GUI","gui_settings.xml",810,10);
    //guiPanel.setup(visualSystemParams);
    guiPanel.add(saveSetupButton.setup("SAVE SETUP"));
    guiPanel.add(modeToggle.setup("TOGGLE LIVE MODE", true));
    guiPanel.add(hideGuiButton.setup("HIDE GUI"));
    guiPanel.add(visualSystemParams);
    guiPanel.loadFromFile("gui_settings.xml");

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