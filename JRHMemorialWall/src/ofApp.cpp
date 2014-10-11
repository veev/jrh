#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofHideCursor();
    
    isFullScreen = true;
    DataManager::init();
    
    displaySystemYOffset = 300;
    
    ofSetFrameRate(20);
    
    int vsw = DataManager::settings.getAttribute("visualSystem", "width", 600);
    int vsh = DataManager::settings.getAttribute("visualSystem", "height", 400);
    vs.init(vsw, vsh);
    //load the test movie
    vs.loadTestMovie(DataManager::getTestVideoPath());
    

    //setup event listeners
    gui.saveSetupButton.addListener(this, &ofApp::saveWaveSetup);
    gui.modeToggle.addListener(this, &ofApp::onModeToggle);
    gui.showKinect.addListener(this, &ofApp::onKinectToggle);
    
    gui.setup(vsw+20);
    
    int port = DataManager::settings.getValue("ledStrips:port", 4445);
    //create wave objects
    DataManager::settings.pushTag("waves");
    for(int i=0; i < DataManager::settings.getNumTags("wave"); i++){
        string type = DataManager::settings.getAttribute("wave", "type", "", i);
        //cout<<"making a wave of type: " << type << endl;
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
            //calculate # leds based on width
            int nleds = DataManager::settings.getAttribute("wave", "numLeds", 0, i);
            
            if(nleds == 0)
                nleds = round(.74 * w);
            
            string host = DataManager::settings.getAttribute("wave", "host", "", i);
            DataManager::settings.pushTag("wave",i);
            
            //create an instance of the strip object
            ds.addStripWave(x,y,w,h,id,lumigeekSender::ADDRESS_1,lumigeekSender::ADDRESS_2,nleds,host,port);
            DataManager::settings.popTag();
        }
        
    }
    //make sure we pop back to the root after pushing...
    DataManager::settings.popTag();
    
    //update the LEDwave pointer on the textManager to point to the wavesPanels controlled by Display System
    vs.tm.wavesPanels = ds.wavesPanels;
    
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
    
    gui.isHidden = control;
}

void ofApp::onKinectToggle(bool & control){
        vs.showKinect = control;
}

//--------------------------------------------------------------
void ofApp::update(){
    gui.update();
    
    //UPDATE GUI Vars
    //Display System
    ds.mirrorStrips = gui.mirrorLEDStrips;
    ds.ledPanelsColor = gui.ledPanelsColor;
    ds.ledStripsColor = gui.ledStripsColor;
    
    //Visual System
    vs.isOn = !gui.disableSignal;
    vs.timeSpeed = gui.flowSpeed;
    vs.timeStep = gui.timeSpeed;
    vs.hForce = gui.horizontalForce;
    vs.vForce = gui.verticalForce;
    vs.fadeAmt = gui.fadeAmt;
    vs.complexity = gui.flowComplexity;
    vs.particleNeighborhood = gui.particleNeighborhood;
    vs.particleRepulsion = gui.particleRepulsion;
    vs.update();
    vs.blurAmount = gui.blur;
    vs.kinectMix = gui.kinectMix;
    vs.particleBrightnessShift = gui.particleBrightnessShift;
    
    //Computer Vision
    vs.cv.contourFinderThreshold = gui.contourFinderThresh;
    vs.cv.flipVertical = gui.flipVertical;
    vs.cv.flipH = gui.flipH;
    vs.cv.contourFinderOn = gui.contourFinder;
    vs.depthCutoff = gui.depthMapCutoff;
    vs.depthForce = gui.depthMapForce;
    
    frame = vs.getFrame();
    
   // ds.updateDisplayAsImage(vs.getFrameAsImage());
    ds.updateDisplay(frame);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   // frame = vs.getFrame();
   // ds.updateDisplay(frame);

    ofBackground(0);
    ofSetColor(255,255,255,255);
    ds.draw(displaySystemYOffset);
        
    if(!gui.isHidden)
        gui.draw();
    else
        ofDrawBitmapString("LIVE MODE [press spacebar to exit]", 10, ds.height + 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch(key){
        case ' ':
            gui.isHidden = !gui.isHidden;
            if(gui.isHidden)
                ds.enterLiveMode();
            else
                ds.enterTestMode();
            break;
        case 'f':
            isFullScreen = ! isFullScreen;
            ofSetFullscreen(isFullScreen);
            break;
        case OF_KEY_UP:
            vs.angleKinectUp();
            break;
        case OF_KEY_DOWN:
            vs.angleKinectDown();
            break;
        case '0':
            vs.showQuote(0);
            break;
        case '1':
            vs.showQuote(1);
            break;
        case '2':
            vs.showQuote(2);
            break;
        case '3':
            vs.showQuote(3);
            break;
        case '4':
            vs.showQuote(4);
            break;
        case '5':
            vs.showQuote(5);
            break;
        case '6':
            vs.showQuote(6);
            break;
        case '7':
            vs.showQuote(7);
            break;
        case '8':
            vs.showQuote(8);
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    vs.mouseMoved(x, y-displaySystemYOffset);
    
    if(x < ds.width && y < ds.height)
        ofHideCursor();
    else
        ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ds.mouseDragged(x, y-displaySystemYOffset, button);
    vs.mousePressed(x, y-displaySystemYOffset);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ds.mousePressed(x, y-displaySystemYOffset, button);
    //vs.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ds.mouseReleased(x, y-displaySystemYOffset, button);
  //  vs.mouseReleased(x, y, button);
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

void ofApp::exit(){
    //on exit, clear LEDs
    ds.clear();
}
