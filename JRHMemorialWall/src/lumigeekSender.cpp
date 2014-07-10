//
//  lumigeekSender.cpp
//  JRHMemorialWall
//
//  Created by Jack Kalish on 7/9/14.
//
//

#include "lumigeekSender.h"

lumigeekSender::lumigeekSender(){

}

void lumigeekSender::setup(string host, int port){
    //Open Connection to HOST:PORT - what is port for LEDs?
    sender.setup(host, port);
}


void lumigeekSender::send(unsigned char * pixels, string address){
    
    ofBuffer buffer;
    buffer.set(reinterpret_cast<const char*>(pixels), sizeof(pixels)); //casting the unsigned char to const char for buffer
    
    ofxOscMessage m;
    m.setAddress(address); //address to send to Lumigeek driver
    m.addBlobArg(buffer); //I think the oscBlob wants a buffer (const char*) not pixels (unsigned char*)
    sender.sendMessage(m);
    
}

