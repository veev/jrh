#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Open Connection to HOST:PORT - what is port for LEDs?
    sender.setup(HOST, PORT); 
    
    //Load Movie for Testing
    jrhMovie.loadMovie("jh_projection_640x480.mov");
    jrhMovie.play();
    
    ofSetFrameRate(20); //keep framerate to 20fps to begin

}

//--------------------------------------------------------------
void ofApp::update(){
    
    jrhMovie.update();
    
    int width =  350; // LEDs want 350 pixels for now  //jrhMovie.getWidth();
    int height =  1; //LEDs are only 1 pixel high //jrhMovie.getHeight();
    
    //unsigned char * pixels = jrhMovie.getPixels();
    int nChannels = jrhMovie.getPixelsRef().getNumChannels(); //RGB = 3 Channels
    
    ofFbo fboSrc;
    
    ofFbo * fbo;
    
    fbo = &fboSrc;
    
    
    fbo->allocate(640, 360, GL_RGB);
    
    fbo->begin();
    jrhMovie.draw(0, 0);
    fbo->end();
    
   // ofPixels p;
    ofImage image;
    image.allocate(width, height, OF_IMAGE_COLOR);
   // image.setNumChannels(3);
    fbo->readToPixels(image);
    image.update();
    
    
    unsigned char * pixels = image.getPixels();
    
    int totalPixels = width * height;
    int totalChannels = totalPixels * nChannels;
    
   for (int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            
            //pixelColor = jrhMovie.getPixelsRef().getColor(x, y);
            
            //In case we want pixel data
            int r = pixels[ (y * width + x) * nChannels + 0 ];
            int g = pixels[ (y * width + x) * nChannels + 1 ];
            int b = pixels[ (y * width + x) * nChannels + 2 ];
            
            cout<<"R: "<<r<<" G: "<<g<<" B: "<<b<<endl;

        }
    }
    
    ofBuffer buffer;
    buffer.set(reinterpret_cast<const char*>(pixels), totalChannels); //casting the unsigned char to const char for buffer
    
    ofxOscMessage m;
    m.setAddress( "/lumigeek/ethser/frameblob/1"); //address to send to Lumigeek driver
    m.addBlobArg(buffer); //I think the oscBlob wants a buffer (const char*) not pixels (unsigned char*)
    sender.sendMessage(m);
    //cout << "ofApp:: sending pixel buffer with size: " << buffer.size() << endl;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    jrhMovie.draw(0,0);
    
    image.draw(0, 380);
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
