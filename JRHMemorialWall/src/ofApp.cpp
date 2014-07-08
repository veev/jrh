#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    DataManager::init();
    
    //create wave objects
    DataManager::settings.pushTag("waves");
    for(int i=0; i < DataManager::settings.getNumTags("wave"); i++){
        string type = DataManager::settings.getAttribute("wave", "type", "", i);
        cout<<"making a wave of type: " << type << endl;
        int x = DataManager::settings.getAttribute("wave", "x", 0, i);
        int y = DataManager::settings.getAttribute("wave", "y", 0, i);
        int w = DataManager::settings.getAttribute("wave", "width", 0, i);
        int h = DataManager::settings.getAttribute("wave", "height", 0, i);

        if(type == DataManager::PANELS){
            //create an instance of the wave object
            ds.addPanelsWave(x,y,w,h);
        }
        else if (type == DataManager::STRIPS){
            //create an instance of the strip object
            ds.addStripWave(x,y,w,h);
        }
    }
    //make sure we pop back to the root after pushing...
    DataManager::settings.popTag();
    
    
    //load the test movie
    vs.loadTestMovie(DataManager::getTestVideoPath());
}

//--------------------------------------------------------------
void ofApp::update(){
    //pull new frame from visual system
    frame = vs.getFrame();
    ds.updateDisplay(frame);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ds.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch(key){
        case 't':
            ds.enterTestMode();
            break;
        case 'l':
            ds.enterLiveMode();
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ds.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ds.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ds.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
