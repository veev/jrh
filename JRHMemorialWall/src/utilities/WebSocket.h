//
//  WebSocketReceiver.h
//  JRHMemorialWall
//
//  Created by Jack Kalish on 11/2/14.
//
//

#pragma once
#include "ofxLibwebsockets.h"

class WebSocket{
 
public:
    WebSocket();
    void setup();
    void broadcastMessage(string m);
    
    ofxLibwebsockets::Server server;
    
    bool bSetup;
    
    //queue of rec'd messages
    vector<string> messages;
    
    //string to send to clients
    string toSend;
    
    // websocket methods
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
    
    ofEvent<string> onGotMessage;
    ofEvent<ofxLibwebsockets::Event> onNewConnection;
    
};
