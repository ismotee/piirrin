#include "ohjain.h"

void Ohjain::setup() {
    gui.setup();
    ViivanOhjain::setup(300);
    VariOhjain::setup();
    ViivanOhjain::moodi = viivaValmis;
}

void Ohjain::update() {
    ViivanOhjain::loop();

    uusinViiva = ViivanOhjain::haeViiva();
    laskeVari(uusinViiva);
    uusinVari = haeVari();

    
    //Guin updaten vois pakata natimminkin.
    GUI_info_T info = gui.getInfo();
    if (info.connecting) {
        gui.print("connecting to " + info.ip + " @ " + ofToString(info.senderPort) + "," + ofToString(info.receiverPort) + "...");
        setAddress(info.ip, info.senderPort, info.receiverPort);
        if (!connection)
            connect();
        if (connection)
            gui.print("connected");
    }

    if (info.disconnecting) {
        if (connection) {
            gui.print("disconnecting");
            disconnect();
        } else
            gui.print("not connected");
    }
    
}

void Ohjain::draw() {
    gui.draw();
    ofBackground(uusinVari);
    if (ViivanOhjain::moodi == piirtaa) {
        ofSetColor(uusinVari.getInverted());
        ofDrawBitmapString(uusinViiva.toString(), 20, 30);
    }
}

void Ohjain::keyPressed(int key) {
   // gui.handleKey(key);
}

void Ohjain::mousePressed(int x, int y) {
  //  if (gui.show)
  //      gui.handleClick(x, y);
  //  else {
        ViivanOhjain::mousePressed(x, y);
  //  }
}

