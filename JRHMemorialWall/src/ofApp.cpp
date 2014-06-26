#include "ofApp.h"

const string ofApp::PANELS = "panels";
const string ofApp::STRIPS = "strips";

//--------------------------------------------------------------
void ofApp::setup(){
    //load settings
    settings.loadFile("settings.xml");
    
    //create wave objects
    settings.pushTag("waves");
    for(int i=0; i < settings.getNumTags("wave"); i++){
        string type = settings.getAttribute("wave", "type", "", i);
        if(type == PANELS){
            //create an instance of the wave object
            int w = settings.getAttribute("wave", "width", 0, i);
            //vs.addPanelsWave();
        }
        else if (type == STRIPS){
            //create an instance of the strip object
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
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
