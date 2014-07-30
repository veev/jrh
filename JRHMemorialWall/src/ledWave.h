//
//  ledWave.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#pragma once
#include "ofMain.h"
#include "DataManager.h"
#include "lumigeekSender.h"

class ledWave{
    
    public:
    ledWave(int x, int y, int w, int h, int idNum);
    //void draw(int y);

    bool hitTest(int x, int y);
    
    int _x, _y, _w, _h, _idNum;
    string type;
    
};

class ledWavePanels: public ledWave{
    
    public:
        ledWavePanels(int x, int y, int w, int h, int idNum);
        void draw(int y);
        void updateFbo(ofFbo * fbo);
        ofFbo _fbo;
        ofImage image;
};

class ledWaveStrips: public ledWave{
    
    public:
    void draw(int x, int y);
    void drawToStrips();
    ledWaveStrips(int x, int y, int w, int h, int idNum, string topAddress, string bottomAddress, int numLeds, string host, int port);
    void updateFbo(ofFbo * fbo);
   // void updateImage(ofImage image);
    void clear();
    
    ofPixels topStripPixels, bottomStripPixels;
    ofImage topStripImage, bottomStripImage;
    
    unsigned char * getTopStripPixels();
    unsigned char * getBottomStripPixels();
    unsigned char topStripPixelsChar;
    string getTopStripAddress();
    string getBottomStripAddress();
    ofFbo topStripFBO, bottomStripFBO;
    
    // Hold the Captured Colors
    vector <ofColor> colors;
    int _numLeds;
    lumigeekSender * lgs;
    
    private:
    string _topStripAddress, _bottomStripAddress;

    
    
};