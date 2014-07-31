//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/7/14.
//
//



#include "visualSystem.h"



visualSystem::visualSystem(){
    width=600;
    height=400;
    
    display = new ofFbo();
    display->allocate(width,height,GL_RGB);

    //particle system
    // this number describes how many bins are used
	// on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
	// if this number is too high, binning is not effective
	// because the screen is not subdivided enough. if
	// it's too low, the bins take up so much memory as to
	// become inefficient.
	int binPower = 3;
    
	particleSystem.setup(width, height, binPower);
    
	kParticles = 20;
	float padding = 0;
	float maxVelocity = 5;
	for(int i = 0; i < kParticles * 1024; i++) {
		float x = ofRandom(padding, width - padding);
		float y = ofRandom(padding, height - padding);
		//float xv = ofRandom(-maxVelocity, 0);
		//float yv = ofRandom(-maxVelocity, maxVelocity);
        
		Particle particle(x, y);
		particleSystem.add(particle);
	}
    
	ofBackground(0, 0, 0);
    
	timeStep = .3;
	lineOpacity = 100;
	pointOpacity = 255;
	isMousePressed = false;
	slowMotion = false;
	particleNeighborhood = 4;
	particleRepulsion = 1;
	centerAttraction = .01;
    
    /*
     All these settings control the behavior of the app. In general it's a better
     idea to keep variables in the .h file, but this makes it easy to set them at
     the same time you declare them.
     */
    complexity = 2; // wind complexity
    pollenMass = .8; // pollen mass
    timeSpeed = .002; // wind variation speed
    phase = TWO_PI; // separate u-noise from v-noise
    hForce = .2;
    vForce = .2;
}

void visualSystem::loadTestMovie(string path){
    testMovie.loadMovie(path);
    testMovie.setVolume(0);
	testMovie.play();
}

void visualSystem::update(){
    particleSystem.setTimeStep(timeStep);
    t = ofGetFrameNum() * timeSpeed;
	   
    
    //draw to FBO
    display->begin();

    ofEnableAlphaBlending();
    //ofBackground(0,0,0,100);
   
    ofFill();
    ofSetColor(0, 0, 0, fadeAmt);
    ofRect(0,0,width,height);

    

    
	ofSetColor(lineOpacity, lineOpacity, lineOpacity, 255);
	particleSystem.setupForces();
	// apply per-particle forces
	glBegin(GL_LINES);
    ofVec2f pos;
	for(int i = 0; i < particleSystem.size(); i++) {
		Particle& cur = particleSystem[i];
		// global force on other particles
		particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
		// forces on this particle
		//cur.bounceOffWalls(0, 0, width, height);
        cur.loopAround(0,0,width,height);
		cur.addDampingForce();
        //apply force to particle
        pos.set(cur.x,cur.y);
        cur.applyForce(getField(pos));
	}
	glEnd();
	
    // single global forces
	particleSystem.addAttractionForce(width / 2, height / 2, width, centerAttraction);
	
    if(isMousePressed)
		particleSystem.addRepulsionForce(mouseX, mouseY, 100, 10);
	particleSystem.update();
    
	
    
	//ofSetColor(255, 255, 255);
	//ofDrawBitmapString(ofToString(kParticles) + "k particles", 32, 32);
	//ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);

    
    ofSetColor(pointOpacity, pointOpacity, pointOpacity, 255);
    particleSystem.draw();
    
    
    ofDisableAlphaBlending();
    // ofSetColor(255);
    //testMovie.draw(0,0,800,600);
    display->end();

}

ofFbo * visualSystem::getFrame(){
   // testMovie.update();
    
    
    return display;
}

void visualSystem::mousePressed(int x, int y){
    isMousePressed = true;
    mouseX = x;
    mouseY = y;
}

void visualSystem::mouseReleased(int x, int y, int button){
    isMousePressed = false;
}

/*
 This is the magic method that samples a 2d slice of the 3d noise field. When
 you call this method with a position, it returns a direction (a 2d vector). The
 trick behind this method is that the u,v values for the field are taken from
 out-of-phase slices in the first dimension: t + phase for the u, and t - phase
 for the v.
 */
//--------------------------------------------------------------
ofVec2f visualSystem::getField(ofVec2f position) {
	float normx = ofNormalize(position.x, 0, width);
	float normy = ofNormalize(position.y, 0, height);
    
	float u = -ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
	float v = .5-ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
    u*=hForce;
    v*=vForce;
    
	return ofVec2f(u, v);
}



