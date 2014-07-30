#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    DataManager::init();
    
    ofSetFrameRate(20);
    
    //setup event listeners
    gui.saveSetupButton.addListener(this, &ofApp::saveWaveSetup);
    gui.modeToggle.addListener(this, &ofApp::onModeToggle);
    
    gui.setup();
    
    int port = DataManager::settings.getValue("ledStrips:port", 4445);
    //create wave objects
    DataManager::settings.pushTag("waves");
    for(int i=0; i < DataManager::settings.getNumTags("wave"); i++){
        string type = DataManager::settings.getAttribute("wave", "type", "", i);
        cout<<"making a wave of type: " << type << endl;
        int x = DataManager::settings.getAttribute("wave", "x", 0, i);
        int y = DataManager::settings.getAttribute("wave", "y", 0, i);
        int w = DataManager::settings.getAttribute("wave", "width", 0, i);
        int h = DataManager::settings.getAttribute("wave", "height", 0, i);
        int id = DataManager::settings.getAttribute("wave", "id", i+1, i);

        if(type == DataManager::PANELS){
            //create an instance of the wave object
            ds.addPanelsWave(x,y,w,h,id);
        }
        else if (type == DataManager::STRIPS){
            int nleds = DataManager::settings.getAttribute("wave", "numLeds", 407, i);
            string host = DataManager::settings.getAttribute("wave", "host", "", i);
            //int port = DataManager::settings.getAttribute("wave", "port", 4445, i);
            DataManager::settings.pushTag("wave",i);
           // string ta = DataManager::settings.getValue("topStrip:address", "");
          // string ba = DataManager::settings.getValue("topStrip:address", "");
            
            //create an instance of the strip object
            ds.addStripWave(x,y,w,h,id,lumigeekSender::ADDRESS_1,lumigeekSender::ADDRESS_2,nleds,host,port);
            DataManager::settings.popTag();
        }
    }
    //make sure we pop back to the root after pushing...
    DataManager::settings.popTag();
    
    //load the test movie
    vs.loadTestMovie(DataManager::getTestVideoPath());
    ds.init();
}

void ofApp::saveWaveSetup(){
    cout<<"ofApp::saveWaveSetup"<<endl;
    ds.saveWaveSetup();
}

void ofApp::onModeToggle(bool & control){
    if(gui.modeToggle)
        ds.enterLiveMode();
    else
        ds.enterTestMode();
}

//--------------------------------------------------------------
void ofApp::update(){
    //pull new frame from visual system
    vs.timeSpeed = gui.flowSpeed;
    vs.timeStep = gui.timeSpeed;
    vs.hForce = gui.horizontalForce;
    vs.vForce = gui.verticalForce;
    vs.fadeAmt = gui.fadeAmt;
    vs.update();
    frame = vs.getFrame();
    
   // ds.updateDisplayAsImage(vs.getFrameAsImage());
    ds.updateDisplay(frame);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   // frame = vs.getFrame();
   // ds.updateDisplay(frame);

    ofBackground(20);
    ds.draw();
    
   // vs.getFrameAsImage().draw(50,50);
    
    if(!gui.isHidden)
        gui.draw();
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
        case ' ':
            gui.isHidden = !gui.isHidden;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ds.mouseDragged(x, y, button);
    vs.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ds.mousePressed(x, y, button);
    vs.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ds.mouseReleased(x, y, button);
    vs.mouseReleased(x, y, button);
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
