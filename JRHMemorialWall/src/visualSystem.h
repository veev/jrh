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

class visualSystem{
    
    public:
    visualSystem();
    ofFbo * getFrame();
    void loadTestMovie(string path);
    void update();
    
    ofVideoPlayer 		testMovie;
   // ofFbo               display;
    ofFbo *             display;
   // ofImage             image;
    
    //particle system
    float timeStep;
	int lineOpacity, pointOpacity;
	float particleNeighborhood, particleRepulsion;
	float centerAttraction;
    
	int kParticles;
	ParticleSystem particleSystem;
	bool isMousePressed, slowMotion;
};