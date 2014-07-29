#pragma once

#include "ParticleSystem.h"
#include "ofMain.h"
#include "Perlin.h"
#include "ofxUI.h"
#include "ofxTweenzor.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    float timeStep;
    int lineOpacity, pointOpacity;
    float particleNeighborhood, particleRepulsion;
    float centerAttraction;
    
    int kParticles;
    ParticleSystem particleSystem;
    bool isMousePressed, slowMotion, applyPerlin, returnToOrigin, drawParticles, drawImage, tweenOpacity, pauseParticles, saveFrames;
    ofVec2f center;
    
    Perlin perlinNoise;
    
    float perlinScalar, springFactor;
    
    ofFbo pixelFbo;
    ofImage img;
    ofPixels pixels;
    vector<ofImage> images;
    
    int imgWidth, imgHeight;
    float sclWidth, sclHeight;
    int mx, my;
    
    //GUI stuff
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    
    //Tweenzor stuff
    TweenParams params;
    void onComplete(float* arg);
    float _x1, _x2, _x3;
    
};