//
//  lumigeekSender.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/9/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

class lumigeekSender{
    
public:
    lumigeekSender();
    void setup(string host, int port);
    void send(unsigned char * pixels, string address);
    
private:
    ofxOscSender sender;
    
};
