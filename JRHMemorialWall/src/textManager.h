//
//  textManager.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 8/8/14.
//
//

#pragma once
#include "ofMain.h"
#include "DataManager.h"
#include "ofxFTGLFont.h"
#include "ledWave.h"

class textManager{
    
public:
    textManager();
    void setup(int width, int height);
    void update();
    void draw();
    void setActiveQuote(int quoteId);
    void fadeTo(int a, int speed);
    
    int activeQuoteID, lineSpacing, padding, alpha, fadeToValue;
    vector <ledWavePanels *> wavesPanels;
    ofPixels pixels;

    
private:
    ofxFTGLFont font;
    ofImage quote, croppedQuote;
    ofFbo textFbo;
    int targetAlpha, fadeSpeed;
    
    
};