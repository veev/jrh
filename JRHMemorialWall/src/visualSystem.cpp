//
//  visualSystem.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/7/14.
//
//



#include "visualSystem.h"



void visualSystem::init(int w, int h){
    width=w;
    height=h;
    particleBrightnessShift = 10;
    
    displayPixels.allocate(w, h, OF_IMAGE_COLOR);
   // textPixels.allocate(w, h, OF_IMAGE_COLOR);
    
    mouseX = -100;
    mouseY = -100;
    
 //   bloom.allocate(width, height);
  //  glow.allocate(width, height);
    blur.allocate(width, height);
    
    cv.setup(width, height);
    
    display = new ofFbo();
    display->allocate(width,height,GL_RGB);
    
    tm.setup(w, h);

    //particle system
    // this number describes how many bins are used
	// on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
	// if this number is too high, binning is not effective
	// because the screen is not subdivided enough. if
	// it's too low, the bins take up so much memory as to
	// become inefficient.
	int binPower = 2;
    
	particleSystem.setup(width, height, binPower);
    
	kParticles = 15;
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
	isMousePressed = true;
	slowMotion = false;
	particleNeighborhood = 4;
	particleRepulsion = 0;
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
    cv.update();
    tm.update();
    
    particleSystem.setTimeStep(timeStep);
    t = ofGetFrameNum() * timeSpeed;
    
    display->readToPixels(displayPixels);
    
    
    //draw to FBO
    display->begin();

    //ofEnableAlphaBlending();
    //ofBackground(0,0,0,100);
   
    ofFill();
    //fade out BG by drawing a rectangle
    ofSetColor(0, 0, 0, fadeAmt);
    ofRect(0,0,width,height);

    //PARTICLE SYSTEM DRAWING STARTS HERE
    if(isOn){
	ofSetColor(lineOpacity, lineOpacity, lineOpacity, 255);
	particleSystem.setupForces();
    
	// apply per-particle forces
	glBegin(GL_LINES);
    ofVec2f pos;
    
    //get depth pixels from kinect image
    ofPixels depthPixels;
    depthPixels.setFromPixels(cv.grayImage.getPixels(), cv.grayImage.getWidth(), cv.grayImage.getHeight(), OF_IMAGE_GRAYSCALE);
        
	for(int i = 0; i < particleSystem.size(); i++) {
		Particle& cur = particleSystem[i];
		// global force on other particles
		particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
		// forces on this particle
        cur.loopAround(0,0,width,height);
		cur.addDampingForce(); //slows the particle down
        
        //apply noise field force to the particle
        pos.set(cur.x,cur.y);
        cur.applyForce(getField(pos));
        cur.updateColor(particleBrightnessShift);
        
        //SHOW TEXT
        //stop the particle if it is over an empty area with text
        if(displayPixels.getColor(cur.x, cur.y).getBrightness() < 230){
            if(tm.pixels.getColor(cur.x, cur.y).getBrightness() > 20){
                cur.stop();
            }
        }
        
        //effect particle speed based on kinect camera depth map
        //cv.grayImage.getPixels()
        
        float depthValue = depthPixels.getColor(cur.x, cur.y).getBrightness();
        //cout<< "depthValue: "<<depthValue<<endl;
        //cout<<"depthValue: "<<depthValue<<endl;
        
        
        //particles sticking to bottom of screen for some reason
       /* if(depthValue > depthCutoff){
            cur.repel((depthValue/255)*depthForce);
        }
        else{
            cur.wasRepeled = false;
        }
*/
        
	}
	glEnd();
	
    
    //add forces for blobs from kinect
        if(contourFinderOn){
            for(int i=0;i<cv.contourFinder.size();i++){
                cv::Point2f center = cv.contourFinder.getCenter(i);
                cv::Rect rect = cv.contourFinder.getBoundingRect(i);
                particleSystem.addRepulsionForce(center.x, center.y, rect.width, repForce);
            }
        }
        
        cv.contourFinderOn = contourFinderOn;
	
    //mouse interaction
    particleSystem.addRepulsionForce(mouseX, mouseY, 50, repForce);
	particleSystem.update();
    
    ofSetColor(pointOpacity, pointOpacity, pointOpacity, 255);
    particleSystem.draw();
    
    
   // ofDisableAlphaBlending();
        
    }
    display->end();


    
    if(isOn){
        //apply the blur
    blur.setTexture(display->getTextureReference());
    blur.setRadius(blurAmount);
    blur.update();

    //Apply blur FX
    display->begin();
        
        //need to enable these special blame functions in order to properly blend apha PNGs
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
        
        //Draw stuff here
        // ...
        
        
        ofClearAlpha();
       // ofEnableAlphaBlending();
        ofSetColor(255,255,255,255);
        //draw text layer
       // tm.draw();
        
    //draw the blurred particle system
    blur.draw(0,0);
        
        //draw the kinect image (for debugging)
    if(showKinect){
        ofSetColor(255, 255, 255, kinectMix);
        cv.draw();
    }
    
    tm.draw();
        
       // ofDisableAlphaBlending();
        glDisable(GL_BLEND);
        glPopAttrib();
    display->end();
    }
}

ofFbo * visualSystem::getFrame(){
   // testMovie.update();
    
    //glow.draw(0,0, ofGetWidth(), ofGetHeight());
    
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

void visualSystem::mouseMoved(int x, int y){
   // isMouseMoved = true;
    mouseX = x;
    mouseY = y;
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

void visualSystem::angleKinectUp(){
    cout<<"angleKinectUp"<<endl;
    cv.angleKinect(-1);
}

void visualSystem::angleKinectDown(){
    cout<<"angleKinectDown"<<endl;
    cv.angleKinect(1);
}

void visualSystem::showQuote(int quoteId){
    tm.setActiveQuote(quoteId);
}

