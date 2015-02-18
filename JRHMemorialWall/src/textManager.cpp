//
//  textManager.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 8/8/14.
//
//

#include "textManager.h"

textManager::textManager(){
    //load fonts
    font.loadFont("/Library/Fonts/Futura.ttc", 10);
    lineSpacing = 5;
    padding = 5;
    activeQuoteID = 0;
    alpha = 0;
    targetAlpha = 0;
    fadeSpeed = 1;
    fadeToValue = 255;
    
}

void textManager::setup(int width, int height){
    textFbo.allocate(width, height, GL_RGBA);
    pixels.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    quote.allocate(480, 144, OF_IMAGE_COLOR_ALPHA);
    
}

void textManager::update(){
    
    if(loadNewQuote){
        //load the image for that quote
        quote.loadImage("quotes/"+ofToString(activeQuoteID)+".png");
        fadeTo(fadeToValue, 100);
        loadNewQuote = false;
    }
    
    
    
    //find the wave by id
    textFbo.begin();
    //set alpha
    alpha += (targetAlpha - alpha)/fadeSpeed;
   // alpha = round(alpha);
    
    cout<<"targetAlpha: "<<targetAlpha<<endl;
    cout<<"alpha: "<<alpha<<endl;

    
    ofSetColor(255, 255, 255, alpha);
    
    //ofClearAlpha();
    ofClear(0,0,0,0);
    
    //need to enable these special blame functions in order to properly blend apha PNGs
    //glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glEnable(GL_BLEND);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);

    ledWavePanels * w;
    int cropY = 0;
    for(int wcnt = 0; wcnt<wavesPanels.size(); wcnt++){
        w = wavesPanels.at(wcnt);

        //draw the text to the correct location in the text fbo layer
        quote.drawSubsection(w->_x, w->_y, w->_w, w->_h, 0, cropY);
        cropY+=w->_h;
    }
    
    textFbo.end();
    
    textFbo.readToPixels(pixels);
    
}

void textManager::draw(){
    ofSetColor(255, 255, 255, 255);
    textFbo.draw(0,0);
}

void textManager::setActiveQuote(int quoteId){
    activeQuoteID = quoteId;
    
    if(quoteId == 0){
        fadeTo(0, 50);
    }
    else{
        loadNewQuote = true;
    }
}

void textManager::fadeTo(int a, int speed){
    targetAlpha = a;
    fadeSpeed = speed;
}