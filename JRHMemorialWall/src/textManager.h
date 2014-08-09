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
    void setup(string dataPath);
    void update();
    void draw();
    void setActiveQuote(int quoteId);
    
    int activeQuoteID, lineSpacing, padding;
    vector <ledWavePanels *> wavesPanels;

    
private:
    ofxFTGLFont font;

    
};