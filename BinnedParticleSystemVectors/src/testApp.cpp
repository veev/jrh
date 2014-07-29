#include "testApp.h"

void testApp::setup(){
    // this number describes how many bins are used
    // on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
    // if this number is too high, binning is not effective
    // because the screen is not subdivided enough. if
    // it's too low, the bins take up so much memory as to
    // become inefficient.
    
    pixelFbo.allocate(ofGetWidth(), ofGetHeight());
    
    int binPower = 3;
    
    //load images in file
    string path = "images";
    ofDirectory dir(path);
    dir.allowExt("jpg");
    dir.listDir();
    
    for(int i = 0; i < dir.numFiles(); i++ ) {
        images.push_back(dir.getPath(i));
        ofLogNotice(dir.getPath(i));
    }

    //Image FBO to get pixel colors for particles
    
    imgWidth = 400;
    imgHeight = 267;
    sclWidth = imgWidth/3;
    sclHeight = imgHeight/3;
    mx = ofGetWidth()/sclWidth;
    my = ofGetHeight()/sclHeight;
    
    pixelFbo.begin();
    
    int i = 0;
    for( int y = 0; y < ofGetHeight(); y += sclHeight ) {
        for (int x = 0; x < ofGetWidth(); x += sclWidth) {
            
            images[i].draw(x , y, sclWidth, sclHeight);
            
            if (i == images.size() - 1) {
                i = 0;
            }
            i++;
        }
    }
    
    pixelFbo.end();
    ofTexture tex = pixelFbo.getTextureReference();
    tex.readToPixels(pixels);
    
    //set up particle system
    particleSystem.setup(ofGetWidth(), ofGetHeight(), binPower);
    
    //populate with particles in a grid
    kParticles = 32;
    float padding = 0;
    //float maxVelocity = .5;
    ofVec2f velocity = ofVec2f(0, 0);
    int res = 10;
    //int xRes = (int)(ofGetWidth()/res);
    //int yRes = (int)(ofGetHeight()/res);
    for(int y = 0; y < ofGetHeight(); y+=res) {
        for(int x = 0; x < ofGetWidth(); x+=res) {
            ofVec2f location = ofVec2f(x, y);
            Particle particle(pixels, location, velocity);
            particleSystem.add(particle);
        }
    }
    
    //clear pixels object to free up memory
    pixels.clear();
    
    //for(int i = 0; i < kParticles * 1024; i++) {
        //float x = ofRandom(padding, ofGetWidth() - padding);
        //float y = ofRandom(padding, ofGetHeight() - padding);
        //float xv = ofRandom(-maxVelocity, maxVelocity);
        //float yv = ofRandom(-maxVelocity, maxVelocity);
        //ofVec2f location = ofVec2f(x, y);
        //Particle particle(location, velocity);
        //particleSystem.add(particle);
    //}
    
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    //default variable values
    timeStep = 0.5;
    lineOpacity = 128;
    pointOpacity = 255;
    isMousePressed = false;
    slowMotion = false;
    applyPerlin = false;
    returnToOrigin = false;
    drawParticles = false;
    drawImage = true;
    saveFrames = false;
    tweenOpacity = false;
    pauseParticles = false;
    particleNeighborhood = 4;
    particleRepulsion = 1;
    centerAttraction = .01;
    center = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    
    perlinNoise = Perlin();
    perlinScalar = 0.25;
    springFactor = 1.0;
    
    //GUI STUFF
    float dim = 16;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
    gui = new ofxUICanvas(0,0,length+xInit*2.0,ofGetHeight());
    
	gui->addWidgetDown(new ofxUILabel("ACTIVATE STATES", OFX_UI_FONT_MEDIUM));
    gui->addToggle("Display Images", false);
    gui->addToggle("Image Tween", false);
    gui->addToggle("Display Particles", false);
    //gui->addToggle("Toggle Images Particles", false);
    gui->addToggle("Perlin Noise", false);
    //gui->addToggle("Central Gravity", false);
    gui->addToggle("Return to Origin", false);
    gui->addToggle("Pause Particles", false);
    gui->addToggle("Save Frames", false);
    
    gui->addSpacer(length, 2);
    
    //gui->addSpacer(length, 2);
    gui->addWidgetDown(new ofxUILabel("FORCE TUNING", OFX_UI_FONT_MEDIUM));
    gui->addSlider("Perlin Force", 0.0, 1.5, perlinScalar, length, dim);
    //gui->addSlider("Central Gravity Force", 0.0, 0.1, maxForce);
    gui->addSlider("Origin Spring Factor", 0.0, 2.0, springFactor);
    
    gui->addSpacer(length, 2);
    gui->addWidgetDown(new ofxUILabel("HIDE & SHOW GUI BY PRESSING 'g'", OFX_UI_FONT_MEDIUM));
    
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui->loadSettings("GUI/guiSettings.xml");
    
    //TWEENZOR STUFF
    // must call this before adding any tweens //
    Tweenzor::init();
    
    _x1 = 200.f;
    _x2 = ofRandom(11,200);
    _x3 = ofRandom(11, 200);
    
    // save some params //
	params.setup( &_x2, _x2, ofRandom(11, 200), 0.f, 3.f, EASE_IN_OUT_SINE );
	
	Tweenzor::add(params);
	//Tweenzor::getTween( params.property )->setRepeat( 1, true );
	Tweenzor::addCompleteListener( Tweenzor::getTween( params.property ), this, &testApp::onComplete);
    
    Tweenzor::add(&_x1, 0.0f, 255.0f, 0.f, 3.0f);
    Tweenzor::getTween(&_x1)->setRepeat( -1, true);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&_x1), this, &testApp::onComplete);
    
    Tweenzor::add(&_x3, _x3, ofRandom(11, 200), 0.f, 2.f, EASE_IN_OUT_SINE);
    Tweenzor::getTween(&_x3)->setRepeat( -1, true);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&_x3), this, &testApp::onComplete);


}

void testApp::update(){
    
    Tweenzor::update(ofGetElapsedTimeMillis());
    
    particleSystem.setTimeStep(timeStep);
    
    // apply per-particle forces
    particleSystem.setupForces();
    
    for(int i = 0; i < particleSystem.size(); i++) {
        Particle& cur = particleSystem[i];
        // global force on other particles
        //particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
        // forces on this particle
        if (applyPerlin) {
            cur.applyPerlinForce(perlinNoise, perlinScalar);
        }
        
        if (returnToOrigin) {
            cur.returnToOrigin(springFactor);
            //particleSystem.returnToOrigin(cur, 1000, 10);
        }
        
        if(pauseParticles) {
            cur.pause();
        }
        //cur.bounceOffWalls(0, 0, ofGetWidth(), ofGetHeight());
        cur.addDampingForce();
    }
    
    // single global forces
    ofVec2f mouseLoc = ofVec2f(mouseX, mouseY);
    //particleSystem.addAttractionForce(center, ofGetWidth(), centerAttraction);
    if(isMousePressed)
        particleSystem.addRepulsionForce(mouseLoc, 100, 10);
    particleSystem.update();
}

void testApp::draw(){
    
    //ofEnableAlphaBlending();
    //ofSetColor(255, 255, 255, lineOpacity);
    //glBegin(GL_LINES);
    
    //glEnd();

    //ofSetColor(255, 255, 255, pointOpacity);
    if(drawParticles) {
        particleSystem.draw();
        drawImage = false;
    }
    
    if(drawImage) {
        drawParticles = false;
        int i = 0;
        
        for( int y = 0; y < ofGetHeight(); y += sclHeight ) {
            for (int x = 0; x < ofGetWidth(); x += sclWidth) {
                
                if (tweenOpacity) {
                    if(i % 4 == 0) {
                        ofSetColor(255, 255, 255, _x2);
                    } else if ( i % 4 == 1) {
                        ofSetColor(255, 255, 255, _x1);
                    } else if (i % 4 == 2){
                        ofSetColor(255, 255, 255, _x3);
                    } else {
                        ofSetColor(255, 255, 255, _x2);
                    }
                }
                
                images[i].draw(x , y, sclWidth, sclHeight);
                
                if (i == images.size() - 1) {
                    i = 0;
                }
                i++;
            }
        }

        
    }
    //ofDisableAlphaBlending();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(kParticles) + "k particles", 32, 32);
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
    
    if (saveFrames) {
        ofSaveScreen(ofToString(ofGetMinutes()) + "_" + ofToString(ofGetFrameNum()) + ".png");
    }
}

void testApp::keyPressed(int key){
    if(key == 's')
        saveFrames = !saveFrames;
        
    if(key == 't') {
        slowMotion = !slowMotion;
        if(slowMotion)
            timeStep = .05;
        else
            timeStep = 1;
    }
    
    if(key == 'p') {
        applyPerlin = !applyPerlin;
    }
    
    if(key == 'o') {
        returnToOrigin = !returnToOrigin;
    }
    
    switch (key) {
        case 'g': {
            gui->toggleVisible();
        }
            break;
        default:
            break;
    }
}

void testApp::mousePressed(int x, int y, int button){
    isMousePressed = true;
}

void testApp::mouseReleased(int x, int y, int button){
    isMousePressed = false;
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    if (name == "Display Images")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        drawImage = toggle->getValue();
    }
    else if (name == "Image Tween")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        tweenOpacity = toggle->getValue();
    }
    if (name == "Display Particles")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        drawParticles = toggle->getValue();
    }
//    else if (name == "Toggle Images Particles")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        toggleImageParticle = toggle->getValue();
//    }
    
    else if (name == "Perlin Noise")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        applyPerlin = toggle->getValue();
    }
//    else if (name == "Central Gravity")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        centralGravity = toggle->getValue();
//    }
    else if (name == "Return to Origin")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        returnToOrigin = toggle->getValue();
    }
    else if (name == "Pause Particles")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        pauseParticles = toggle->getValue();
    }
    else if (name == "Save Frames")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        saveFrames = toggle->getValue();
    }
    
    else if (name == "Perlin Force")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        perlinScalar = slider->getScaledValue();
    }
//    else if (name == "Central Gravity Force")
//    {
//        ofxUISlider *slider = (ofxUISlider *) e.widget;
//        maxForce = slider->getScaledValue();
//    }
    else if (name == "Origin Spring Factor")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        springFactor = slider->getScaledValue();
    }
}

//--------------------------------------------------------------
// this function is called on when the tween is complete //
void testApp::onComplete(float* arg) {
	cout << "testApp :: onComplete : arg = " << *arg << endl;
	float _tarX = 0.f;
	float _begin = 0.f;
	
	// the arg argument is a pointer to the variable passed in when calling Tweenzor::add();
	// if you want to check its value, you must de-reference it by calling *arg
	if (*arg > 300) {
		_tarX = 200.0f;
		_begin = 900.0f;
	} else {
		_tarX = 900.f;
		_begin = 200.f;
	}
	
	if (arg == &_x2) {
		// update the params //
		params.begin	= *params.property;
		params.end		= ofRandom(11, 200);
		params.duration = ofRandom(.3, 1.1);
		Tweenzor::add( params );
		Tweenzor::addCompleteListener( Tweenzor::getTween(&_x2), this, &testApp::onComplete);
	}
    
	//Tweenzor::add( &_x1, _begin, _tarX, 0.f, 2.f );
	
	// add the complete listener again so that it will fire again, creating a loop //
	//Tweenzor::addCompleteListener( Tweenzor::getTween(&_x1), this, &testApp::onComplete);
	
	//Tweenzor::add(&_x2, _x2, _tarX, 0.f, 2.f, EASE_IN_OUT_SINE);
    //	Tweenzor::add(&_x3, _x3, _tarX, 0.f, 2.f, EASE_IN_OUT_QUAD);
    //
    //	Tweenzor::add( &_x4, _x4, _tarX, 0.f, 2.f, EASE_IN_OUT_QUART );
    //	Tweenzor::add( &_x5, _x5, _tarX, 0.f, 2.f, EASE_IN_OUT_CUBIC );
    //	Tweenzor::add( &_x6, _x6, _tarX, 0.f, 2.f, EASE_IN_OUT_QUINT );
    //	Tweenzor::add( &_x7, _x7, _tarX, 0.f, 2.f, EASE_IN_OUT_CIRC );
    //	Tweenzor::add( &_x8, _x8, _tarX, 0.f, 2.f, EASE_IN_OUT_ELASTIC );
    //	Tweenzor::add( &_x9, _x9, _tarX, 0.f, 2.f, EASE_IN_OUT_BACK );
    //	Tweenzor::add( &_x10, _x10, _tarX, 0.f, 2.f, EASE_IN_OUT_BOUNCE );
	
	
}

