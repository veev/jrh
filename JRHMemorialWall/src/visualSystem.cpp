//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/7/14.
//
//

#include "visualSystem.h"

visualSystem::visualSystem(){
    display = new ofFbo();
    display->allocate(800,600,GL_RGB);
   //  image.allocate(800, 600, OF_IMAGE_COLOR);
    
}

void visualSystem::loadTestMovie(string path){
    testMovie.loadMovie(path);
    testMovie.setVolume(0);
	testMovie.play();
}

ofFbo * visualSystem::getFrame(){
    testMovie.update();
    
    display->begin();
    
    ofSetColor(255);
    testMovie.draw(0,0,800,600);
    
    display->end();
    
    return display;
}
/*
ofImage visualSystem::getFrameAsImage(){
    
   
    displayPointer->readToPixels(image.getPixelsRef());
   // image.update();
    return image;
    
}*/




