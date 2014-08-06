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


class computerVision{

    public:
    void setup(int width, int height);
    void update();
    void draw();
    
    ofxKinect kinect;
    

};