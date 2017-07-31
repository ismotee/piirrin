#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

struct OscInterface {
    
    bool connection;
    
    ofxOscReceiver receiver;
    ofxOscSender sender;

    void setAddress(std::string ipAddress, int sender_port = 9997, int receiver_port = 9998);
    void sendFloat(std::string address, float value);
    void connect();
    void disconnect();

};
