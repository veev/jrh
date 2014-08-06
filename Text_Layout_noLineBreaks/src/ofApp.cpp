#include "ofApp.h"

int margin, quoteMargin, quoteHeight, issueState;
string alignment, type, name;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    // Layout will wrap your text depending on the line length you set,
    // or when you insert line breaks into the text manually (\n).
    
    margin = 20;
    quoteMargin = 25;
    quoteHeight = 125;
    alignment = "LEFT";
    
    layoutInfo.loadFont("Futura.ttf", 8);
    layoutInfo.setLineLength(ofGetWidth() - margin * 2);
    
    layoutText.loadFont("FuturaBold.ttf", 6);
    layoutText.setLineLength(ofGetWidth() - margin * 2);
    
    settings.loadFile("quotes.xml");
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(settings.loadFile("quotes.xml") ) {
        
        settings.pushTag("quotes");
        
        int numIssues = settings.getNumTags("issue");
        
        for(int i=0; i < numIssues; i++){
            
            type = settings.getAttribute("issue", "id", "", issueState);
            //cout<<"issue: " << type << endl;
            
            name = settings.getAttribute("issue", "name", "", issueState);
            //cout<<"name: " << name << endl;
            
            //quote = settings.getAttribute("issue", "quote", "", issueState);
            //cout<<"quote: " << quote << endl;
            //upperQuote = ofToUpper(quote);
        }
        
        settings.popTag();
        
        layoutText.setLineLength(MAX(margin * 2, ofGetMouseX() - margin));
        layoutText.setLineSpacing(ofMap(ofGetMouseY(), 0, ofGetHeight(), 0.0f, 2.0f, true));
    
    } else {
       
        ofLogError("Settings file did not load!");
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
	
    ofSetColor(128);
    layoutInfo.drawString("FPS: " + ofToString(ofGetFrameRate(), 2) + "\n" +
                          "Line Length (Mouse X): " + ofToString(layoutText.getLineLength()) + "\n" +
                          "Line Spacing (Mouse Y): " + ofToString(layoutText.getLineSpacing()) + "\n" +
                          "Alignment (1-4): " + alignment + "\n" +
                          "Issue: " + name,
                          margin, 20);
    
    ofSetColor(255, 0, 0);
    
    int height = 120;
    int canvasWidth = 512;
    int canvasHeight = 144;
    ofPushStyle();
    ofNoFill();
    ofRect(margin, height, canvasWidth, canvasHeight);
    ofPopStyle();
    
    ofFill();
    ofSetColor(255,0,0,50);
   // ofStroke(255,0,0,255);
    ofRect(margin + canvasWidth - 352, height, 352, 16);
    ofRect(margin + canvasWidth - 480, height + 16, 480, 32);
    ofRect(margin, height + 16 + 32, 480, 48);
    ofRect(margin + 40, height + 16 + 32 + 48, 320, 48);
    
    ofNoFill();
    ofSetColor(255, 0, 0, 255);
    ofRect(margin + canvasWidth - 352, height, 352, 16);
    ofRect(margin + canvasWidth - 480, height + 16, 480, 32);
    ofRect(margin, height + 16 + 32, 480, 48);
    ofRect(margin + 40, height + 16 + 32 + 48, 320, 48);
    
    ofSetColor(0);
	layoutText.drawString(upperQuote, quoteMargin, quoteHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 97) {
        quoteMargin--;
        cout << "quoteMargin: " << quoteMargin << endl;
    }
    else if (key == 100) {
        quoteMargin++;
        cout << "quoteMargin: " << quoteMargin << endl;
    }
    else if (key == 115) {
        quoteHeight--;
        cout << "quoteHeight: " << quoteHeight << endl;
    }
    else if( key == 119) {
        quoteHeight++;
        cout << "quoteHeight: " << quoteHeight << endl;

    }

    
    
    switch (key) {
        case '1':
            issueState = 0;
            break;
        case '2':
            issueState = 1;
            break;
        case '3':
            issueState = 2;
            break;
        case '4':
            issueState = 3;
            break;
        case '5':
            issueState = 4;
            break;
        case '6':
            issueState = 5;
            break;
            
        case '7':
            layoutText.setAlignment(FTGL_ALIGN_LEFT);
            alignment = "LEFT";
            break;
        case '8':
            layoutText.setAlignment(FTGL_ALIGN_CENTER);
            alignment = "CENTER";
            break;
        case '9':
            layoutText.setAlignment(FTGL_ALIGN_RIGHT);
            alignment = "RIGHT";
            break;
        case '0':
            layoutText.setAlignment(FTGL_ALIGN_JUSTIFY);
            alignment = "JUSTIFY";
            break;
            
        default:
            break;
    }
    

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
