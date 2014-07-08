//
//  visualSystem.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 6/25/14.
//
//

#pragma once
#include "ofMain.h"
#include "ledWave.h"

class displaySystem{
    public:
    
    displaySystem();
    void addPanelsWave(int x, int y, int w, int h);
    void addStripWave(int x, int y, int w, int h);
    void draw();
    void drawWaves();
    void updateDisplay(ofFbo * frame);
    void enterLiveMode();
    void enterTestMode();
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    vector<ledWave> waves;  // create an empty vector of floats
    
    
    private:
    ofFbo * _frame;
    static const string TEST_MODE;
    static const string LIVE_MODE;
    string mode;
    ledWave * draggableWave;
    int mousePressedX, mousePressedY;

};