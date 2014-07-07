//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/7/14.
//
//

#include "visualSystem.h"

visualSystem::visualSystem(){
    display.allocate(800,600);
    display.begin();
    ofClear(255,255,255, 0);
    display.end();
}

void visualSystem::loadTestMovie(string path){
    testMovie.loadMovie(path);
	testMovie.play();
    
    
}

ofFbo visualSystem::getFrame(){
    testMovie.update();
    
    display.begin();
    ofSetColor(255);
    testMovie.draw(0,0,800,600);
    display.end();
    
    return display;
}