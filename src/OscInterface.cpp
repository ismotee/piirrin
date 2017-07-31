#include "OscInterface.h"

void OscInterface::setAddress(std::string ipAddress, int sender_port, int receiver_port) {
    sender.setup(ipAddress, sender_port);
    receiver.setup(receiver_port);
}

void OscInterface::sendFloat(std::string address, float value) {
    if (connection) {
        ofxOscMessage msg;
        msg.setAddress(address);
        msg.addFloatArg(value);
        sender.sendMessage(msg,false);
    }
}

void OscInterface::connect() {
    connection = true;
}

void OscInterface::disconnect() {
    connection = false;
}