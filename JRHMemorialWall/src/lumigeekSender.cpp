//
//  lumigeekSender.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/9/14.
//
//

#include "lumigeekSender.h"

const string lumigeekSender::ADDRESS_1 = "/lumigeek/ethser/frameblob/1";
const string lumigeekSender::ADDRESS_2 = "/lumigeek/ethser/frameblob/2";


lumigeekSender::lumigeekSender(){

}

void lumigeekSender::setup(string host, int port, int numPixels){
  //  cout<<"lumigeek sender setup host: "<<host<<" port: "<<port<< endl;
    
    //Open Connection to HOST:PORT - what is port for LEDs?
    sender = new ofxOscSender();
    sender->setup(host, port);
    totalChannels = numPixels * 3;
    _numPixels = numPixels;
    //_host = host;
   // _port = port;
}


void lumigeekSender::send(unsigned char * pixels, string address){
    
   // cout<<"lumigeekSender::send address: "<<address<<endl;
   // cout<<"host: "<<_host<<endl;
   // cout<<"port: "<<_port<<endl;
    
    
    
    ofBuffer buffer;
    buffer.set(reinterpret_cast<const char*>(pixels), totalChannels); //casting the unsigned char to const char for buffer
    
    ofxOscMessage m;
    m.setAddress(address); //address to send to Lumigeek driver
    m.addBlobArg(buffer); //I think the oscBlob wants a buffer (const char*) not pixels (unsigned char*)
    sender->sendMessage(m);
    
}

void lumigeekSender::clear(){
    //send black pixels to both addresses
    ofPixels *p = new ofPixels();
    p->allocate(_numPixels, 1, OF_IMAGE_COLOR);
    p->setColor(ofColor(0));
    send(p->getPixels(), ADDRESS_1);
    send(p->getPixels(), ADDRESS_2);
}

