//
//  computerVision.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#include "computerVision.h"

void computerVision::setup(int width, int height){
    
	kinect.init();
    flipVertical = false;
    flipH = false;
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)
	
	kinect.open();		// opens first available kinect
	//kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
	//kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
	
	// print the intrinsic IR sensor values
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}
    
    kinectAngle = 0;
    
    grayImage.allocate(kinect.width, kinect.height);
    
    //contour finder
    contourFinder.setMinAreaRadius(10);
	contourFinder.setMaxAreaRadius(200);
    
    bgSubTime = 1;
    background.setLearningTime(bgSubTime);
    background.setThresholdValue(10);
    firstFrame = true;

}

void computerVision::update(){
    
    kinect.update();
    background.setLearningTime(bgSubTime);
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
        if(firstFrame){
            firstFrame = false;
            //reset bg upon first frame?
            background.reset();
        }
        
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        //grayImage.mirror(flipVertical, flipH);
        
        //gray image not working? use kinect image for now...
        background.update(kinect, thresholded);
        thresholded.mirror(flipVertical, flipH);
        thresholded.update();
        
        if(contourFinderOn){
            contourFinder.setThreshold(contourFinderThreshold);
            contourFinder.findContours(thresholded);
        }
        
    }
    
}

void computerVision::draw(){
   // grayImage.draw(0,0);
    thresholded.draw(0, 0);
    ofSetLineWidth(2);
    if(contourFinderOn)
        contourFinder.draw();
}

void computerVision::angleKinect(int angle){
    kinectAngle += angle;
    kinect.setCameraTiltAngle(kinectAngle);
    cout<<"angle kinect to: "<<kinectAngle<<endl;
}

