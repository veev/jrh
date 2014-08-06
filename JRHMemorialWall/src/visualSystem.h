//
//  visualSystem.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/7/14.
//
//

#pragma once
#include "ofMain.h"
#include "ParticleSystem.h"
#include "computerVision.h"
//#include "ofxFX.h"
//#include "ofxBloom.h"
//#include "ofxMultiTexture.h"

class visualSystem{
    
    public:
    visualSystem();
    ofFbo * getFrame();
    void loadTestMovie(string path);
    void update();
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y, int button);
    void mouseMoved(int x, int y);
    ofVec2f getField(ofVec2f position);
    

    
    ofVideoPlayer 		testMovie;
    ofFbo *             display;
    
    int width, height, mouseX, mouseY;
    
    //noise field
    float t;
    
    //particle system
    float timeStep;
	int lineOpacity, pointOpacity;
	float particleNeighborhood, particleRepulsion;
	float centerAttraction;
    
	int kParticles, fadeAmt;
	ParticleSystem particleSystem;
	bool isMousePressed, slowMotion;
    
    float complexity;
    float pollenMass;
    float timeSpeed;
    float phase, hForce, vForce;
    
    computerVision cv;
    
    //fx
   // ofxBloom bloom;
   // ofxMultiTexture mult;

};