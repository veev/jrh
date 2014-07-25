//
//  strip.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/10/14.
//
//

#pragma once
#include "ofMain.h"

class strip{
public:
    strip();
    void setup(string address);
    
    
private:
    unsigned char * pixels;
};