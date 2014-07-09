//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "displaySystem.h"

const string displaySystem::TEST_MODE = "test_mode";
const string displaySystem::LIVE_MODE = "live_mode";

displaySystem::displaySystem(){
    mode = TEST_MODE;
}

//update the display with a new image
void displaySystem::updateDisplay(ofFbo * frame){
    _frame = frame;
    
    //update the fbo on the wave
    for (int i=0;i<waves.size();i++){
        ledWave w = waves.at(i);
        w.updateFbo(frame);
    }
    
}

//create an instance of the PanelsWave object
void displaySystem::addPanelsWave(int x, int y, int w, int h){
    
    ledWave wave = ledWavePanels(x, y, w, h);
    waves.push_back(wave);
    
}

//create an instance of the StripWave object
void displaySystem::addStripWave(int x, int y, int w, int h){
    ledWave wave = ledWaveStrip(x, y, w, h);
    waves.push_back(wave);
}

void displaySystem::draw(){
    if(mode == TEST_MODE){
        //render test mode
        ofSetColor(255);
        _frame->draw(0,0);
       
    }
    else if (mode == LIVE_MODE){
        //render live mode]
        
    }
    
     drawWaves();
}

void displaySystem::drawWaves(){
    
    //cout<<"drawWaves"<<endl;
    //cout<<"waves.size(): "<<waves.size()<<endl;
    
    //draw outline for the waves
       ofNoFill();
    
    int y=0;
    
    for (int i=0;i<waves.size();i++){
        ledWave w = waves.at(i);
        //cout<<"draw wave " << i << endl;
        
        if(mode == TEST_MODE){
            //draw boxes for all the waves
            if(w.type == DataManager::PANELS)
                ofSetColor(255, 100, 100);
            else
                ofSetColor(100, 100, 255);
        
            ofRect(w._x, w._y, w._w, w._h);
        }
        else{
            //draw just the panels to the screen
            if(w.type == DataManager::PANELS){
                w.draw(y);
                y+=w._h;
            }
        }

    }
    
}

//Find the wave that is clicked on and make that the draggable one
void displaySystem::mousePressed(int x, int y, int button){
    
     for (int i=0;i<waves.size();i++){
         ledWave * w = & waves.at(i);
         if(w->hitTest(x,y)){
             draggableWave = w;
             mousePressedX = x-w->_x;
             mousePressedY = y-w->_y;
         }
     }
    
}

//drag the wave that has been clicked on
void displaySystem::mouseDragged(int x, int y, int button){
    if(draggableWave){
        draggableWave->_x = x - mousePressedX;
        draggableWave->_y = y - mousePressedY;
    }
}

//stop dragging the wave
void displaySystem::mouseReleased(int x, int y, int button){
    draggableWave = NULL;
}


void displaySystem::enterLiveMode(){
    mode = LIVE_MODE;
}

void displaySystem::enterTestMode(){
    mode = TEST_MODE;
}

void displaySystem::saveWaveSetup(){
    DataManager::settings.pushTag("waves");
    
    for(int i=0; i < DataManager::settings.getNumTags("wave"); i++){
        ledWave * w = &waves.at(i);
        DataManager::settings.setAttribute("wave", "x", w->_x, i);
        DataManager::settings.setAttribute("wave", "y", w->_y, i);
    }
    
    //make sure we pop back to the root after pushing...
    DataManager::settings.popTag();
    
    //save the file
    DataManager::settings.saveFile();
}