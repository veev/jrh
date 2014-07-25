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
#include "lumigeekSender.h"
#include "DataManager.h"

class displaySystem{
    public:
    
    displaySystem();
    void init();
    void addPanelsWave(int x, int y, int w, int h, int idNum);
    void addStripWave(int x, int y, int w, int h, int idNum, string topAddress, string bottomAddress);
    void draw();
    void drawWaves();
    void updateDisplay(ofFbo * frame);
    void updateDisplayAsImage(ofImage image);
    void enterLiveMode();
    void enterTestMode();
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void saveWaveSetup();
    
    vector<ledWavePanels> wavesPanels;
    vector <ledWaveStrips> wavesStrips;
    
    private:
    ofFbo * _frame;
    static const string TEST_MODE;
    static const string LIVE_MODE;
    string mode;
    ledWave * draggableWave;
    int mousePressedX, mousePressedY;
    lumigeekSender lgs;
    
    ofImage frameImage;

};