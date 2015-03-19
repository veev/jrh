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
    void setup(string host, int port, int numPixels);
    void send(unsigned char * pixels, string address);
        static const string ADDRESS_1, ADDRESS_2;
    void clear();
    
private:
    ofxOscSender * sender;
    int totalChannels, _numPixels;
    bool setupSuccessful;

};
