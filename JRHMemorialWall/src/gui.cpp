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
    
    //create the gui
    guiPanel.setup("GUI","gui_settings.xml",810,10);
    guiPanel.add(saveSetupButton.setup("SAVE SETUP"));
    guiPanel.add(modeToggle.setup("TOGGLE LIVE MODE", true));
    guiPanel.add(hideGuiButton.setup("HIDE GUI"));
    
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

void gui::onModeToggle(){
    
}