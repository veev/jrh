//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/7/14.
//
//

#include "visualSystem.h"

visualSystem::visualSystem(){
    displayPointer = &display;
    displayPointer->allocate(800,600,GL_RGB);
     image.allocate(800, 600, OF_IMAGE_COLOR);
    
    /*displayPointer->begin();
    ofClear(255,255,255, 0);
    displayPointer->end();*/
}

void visualSystem::loadTestMovie(string path){
    testMovie.loadMovie(path);
	testMovie.play();
}

ofFbo * visualSystem::getFrame(){
    testMovie.update();
    
    displayPointer->begin();
    
    ofSetColor(255);
    testMovie.draw(0,0,800,600);
    
    displayPointer->end();
    
    return displayPointer;
}

ofImage visualSystem::getFrameAsImage(){
    
   
    displayPointer->readToPixels(image.getPixelsRef());
    image.update();
    return image;
    
}




