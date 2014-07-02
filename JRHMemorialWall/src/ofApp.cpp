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
        

        if(type == DataManager::PANELS){
            //create an instance of the wave object
            int h = DataManager::settings.getAttribute("wave", "height", 0, i);
            vs.addPanelsWave(x,y,w,h);
        }
        else if (type == DataManager::STRIPS){
            //create an instance of the strip object
            vs.addStripWave(x,y,w);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    //for debugging
    vs.drawWaves();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
