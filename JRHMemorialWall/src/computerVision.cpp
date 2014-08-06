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

}

void computerVision::update(){
    
    kinect.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		contourFinder.setThreshold(contourFinderThreshold);
		contourFinder.findContours(grayImage);
    }
}

void computerVision::draw(){
    grayImage.draw(0, 0);
    ofSetLineWidth(2);
	contourFinder.draw();
    
    //contourFinder.getContours();
}



void computerVision::angleKinect(int angle){
    kinectAngle += angle;
    kinect.setCameraTiltAngle(kinectAngle);
    cout<<"angle kinect to: "<<kinectAngle<<endl;
    
}

