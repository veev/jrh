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
   // saveSetupButton.addListener(this, &DataManager::saveSettings);
   
    
}

void gui::setup(){
    //create the gui
    guiPanel.setup("GUI","gui_settings.xml",810,10);
    guiPanel.add(saveSetupButton.setup("SAVE SETUP"));
   // guiPanel.setPosition(810,10);
}

void gui::draw(){
    guiPanel.draw();
}