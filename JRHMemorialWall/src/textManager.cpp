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
    font.loadFont("fonts/Futur", 10);
    lineSpacing = 5;
    padding = 5;
    activeQuoteID = 0;
}

void textManager::setup(string dataPath){
    
}

void textManager::update(){
    
}

void textManager::draw(){
    
    if(activeQuoteID != 0){
        ofSetColor(255);
        //parse XML to get the text
        DataManager::settings.pushTag("quotes");
        DataManager::settings.pushTag("issue", activeQuoteID-1);
        DataManager::settings.pushTag("quote");
        int y = 48+font.getSize()+padding;
        for(int i=0; i<DataManager::settings.getNumTags("line");i++){
            string str = DataManager::settings.getAttribute("line", "text", "", i);
            str = ofToUpper(str);
            int waveNum = DataManager::settings.getAttribute("line", "wave", 4, i);
            
            //find the wave by id
            ledWavePanels * w;
            for(int wcnt = 0; wcnt<wavesPanels.size(); wcnt++){
                w = wavesPanels.at(wcnt);
                if(w->_idNum == waveNum)
                    break;
            }
            ofRectangle textBox = font.getStringBoundingBox(str, 0, 0);
            int x = w->_x + padding;
            int y = w->_y + padding + textBox.height + (textBox.height+lineSpacing)*i;
        
            //TODO: use ledWavePanel pointer vector to determine positioning
            font.drawString(str, x, y);
        
            //go to next line
            //y += textBox.height + lineSpacing;
        }
        DataManager::settings.popTag();
        DataManager::settings.popTag();
        DataManager::settings.popTag();
    }
    
}

void textManager::setActiveQuote(int quoteId){
    activeQuoteID = quoteId;
}