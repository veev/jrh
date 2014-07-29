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

    //particle system
    // this number describes how many bins are used
	// on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
	// if this number is too high, binning is not effective
	// because the screen is not subdivided enough. if
	// it's too low, the bins take up so much memory as to
	// become inefficient.
	int binPower = 3;
    
	particleSystem.setup(ofGetWidth(), ofGetHeight(), binPower);
    
	kParticles = 32;
	float padding = 0;
	float maxVelocity = .5;
	for(int i = 0; i < kParticles * 1024; i++) {
		float x = ofRandom(padding, ofGetWidth() - padding);
		float y = ofRandom(padding, ofGetHeight() - padding);
		float xv = ofRandom(-maxVelocity, maxVelocity);
		float yv = ofRandom(-maxVelocity, maxVelocity);
		Particle particle(x, y, xv, yv);
		particleSystem.add(particle);
	}
    
	ofBackground(0, 0, 0);
    
	timeStep = 1;
	lineOpacity = 128;
	pointOpacity = 255;
	isMousePressed = false;
	slowMotion = false;
	particleNeighborhood = 4;
	particleRepulsion = 1;
	centerAttraction = .01;
}

void visualSystem::loadTestMovie(string path){
    testMovie.loadMovie(path);
    testMovie.setVolume(0);
	testMovie.play();
}

void visualSystem::update(){
    particleSystem.setTimeStep(timeStep);
    
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, lineOpacity);
	particleSystem.setupForces();
	// apply per-particle forces
	glBegin(GL_LINES);
	for(int i = 0; i < particleSystem.size(); i++) {
		Particle& cur = particleSystem[i];
		// global force on other particles
		particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
		// forces on this particle
		cur.bounceOffWalls(0, 0, ofGetWidth(), ofGetHeight());
		cur.addDampingForce();
	}
	glEnd();
	// single global forces
	particleSystem.addAttractionForce(ofGetWidth() / 2, ofGetHeight() / 2, ofGetWidth(), centerAttraction);
	//if(isMousePressed)
	//	particleSystem.addRepulsionForce(mouseX, mouseY, 100, 10);
	particleSystem.update();
	
    
    
	
	ofDisableAlphaBlending();
    
	//ofSetColor(255, 255, 255);
	//ofDrawBitmapString(ofToString(kParticles) + "k particles", 32, 32);
	//ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
    
    
    //draw to FBO
    display->begin();
    ofBackground(0);
    ofSetColor(255, 255, 255, pointOpacity);
    particleSystem.draw();
    // ofSetColor(255);
    //testMovie.draw(0,0,800,600);
    display->end();

}

ofFbo * visualSystem::getFrame(){
   // testMovie.update();
    
    
    return display;
}
/*
ofImage visualSystem::getFrameAsImage(){
    
   
    displayPointer->readToPixels(image.getPixelsRef());
   // image.update();
    return image;
    
}*/




