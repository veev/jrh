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
    
    //preload all the images
    //quote.loadImage("quotes/1.png");
    
    }

void textManager::setup(int width, int height){
    textFbo.allocate(width, height);
}

void textManager::update(){
   /*  ofSetColor(255, 0, 0, 100);
    if(quote.isAllocated()){
        quote.draw(0, 0);
    }*/
    
    
        ofSetColor(255);
        //parse XML to get the text
        /* DataManager::settings.pushTag("quotes");
         DataManager::settings.pushTag("issue", activeQuoteID-1);
         DataManager::settings.pushTag("quote");
         int y = 48+font.getSize()+padding;
         for(int i=0; i<DataManager::settings.getNumTags("line");i++){
         string str = DataManager::settings.getAttribute("line", "text", "", i);
         str = ofToUpper(str);
         int waveNum = DataManager::settings.getAttribute("line", "wave", 4, i);
         int lineNum = DataManager::settings.getAttribute("line", "line", 0, i);*/
        
        //find the wave by id
        textFbo.begin();
        //ofClearAlpha();
    ofClear(0,0,0,0);
    if(activeQuoteID != 0){
        ledWavePanels * w;
        int cropY = 0;
        for(int wcnt = 0; wcnt<wavesPanels.size(); wcnt++){
            w = wavesPanels.at(wcnt);
            //draw the text to the correct location in the text fbo layer
            
            quote.drawSubsection(w->_x, w->_y, w->_w, w->_h, 0, cropY);
            cropY+=w->_h;
            
            //if(w->_idNum == waveNum)
            //  break;
        }
        
    }
        textFbo.end();
        
        /*  ofRectangle textBox = font.getStringBoundingBox(str, 0, 0);
         int x = w->_x + padding;
         int y = w->_y + padding + textBox.height + (textBox.height+lineSpacing)*(lineNum-1);
         
         //TODO: use ledWavePanel pointer vector to determine positioning
         font.drawString(str, x, y);
         
         //go to next line
         //y += textBox.height + lineSpacing;
         }
         DataManager::settings.popTag();
         DataManager::settings.popTag();
         DataManager::settings.popTag();*/
    

}

void textManager::draw(){
    textFbo.draw(0,0);
}

void textManager::setActiveQuote(int quoteId){
    activeQuoteID = quoteId;
    
    if(quoteId == 0){
        quote.clear();
    }
    else{
        quote.loadImage("quotes/"+ofToString(quoteId)+".png");
    }
    
    //load the image for that quote
}