#pragma once

#include "ofMain.h"
#include "displaySystem.h"
#include "DataManager.h"
#include "visualSystem.h"
#include "gui.h"
#include "lumigeekSender.h"
#include "WebSocket.h"

class ofApp : public ofBaseApp{

	public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void onModeToggle(bool & control);
    void onKinectToggle(bool & control);
    void onLEDsToggle(bool & control);
    void onSoundToggle(bool & control);
    void fullscreenToggle(bool & control);
    void onMessage(string & m);
    void onNewConnection(ofxLibwebsockets::Event& args);

    void saveWaveSetup();
    
    void exit();
    
    displaySystem ds;
    visualSystem  vs;
    WebSocket webSocket;
    
    
    ofFbo * frame;
    
    gui gui;
    
    bool isFullScreen;
	int displaySystemYOffset;
    
    
};
