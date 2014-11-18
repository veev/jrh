//
//  computerVision.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"


class computerVision{

    public:
    void setup(int width, int height);
    void update();
    void draw();
    void angleKinect(int angle);
    void getBlobs();
    
    ofxKinect kinect;
    int kinectAngle, bgSubTime;
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    
    ofxCv::ContourFinder contourFinder;
    float contourFinderThreshold;
    
    bool flipVertical, flipH, contourFinderOn;
    
    ofxCv::RunningBackground background;
    ofImage thresholded;



};