#include "ohjain.h"

void Ohjain::setup() {
    GUI::setup();
    ViivanOhjain::setup(300);
    VariOhjain::setup();
    ViivanOhjain::moodi = viivaValmis;
    Monitori::setup();
}


void Ohjain::update() {
    
    ViivanOhjain::loop();

    //haetaan viiva ja lasketaan väri
    uusinViiva = ViivanOhjain::haeViiva();
    VariOhjain::laskeVari(uusinViiva);
    uusinVari = haeVari();
    
    //asetetaan monitoriin viiva ja väri. Tämä ei vielä piirrä ruudulle; ks. Monitori::draw()
    //TODO: milloin lopetetaan piirtäminen ja aloitetaan uusi?
    Monitori::piirraVari(uusinVari);
    Monitori::piirraViiva(uusinViiva);
    
    //kun halutaan lopettaa viiva:
    //Monitori::tyhjenna();
    //minkä jälkeen uusi viiva alkaa taas, kun kutsutaan piirraViiva())

    
    GUI_info_T info = GUI::getInfo();
    if (info.connecting) {
        GUI::print("connecting to " + info.ip + " @ " + ofToString(info.senderPort) + "," + ofToString(info.receiverPort) + "...");
       OscInterface::setAddress(info.ip, info.senderPort, info.receiverPort);
        if (!OscInterface::connection)
            OscInterface::connect();
        if (OscInterface::connection)
            GUI::print("connected");
    }

    if (info.disconnecting) {
        if (OscInterface::connection) {
            GUI::print("disconnecting");
            OscInterface::disconnect();
        } else
            GUI::print("not connected");
    }
}


void Ohjain::draw() {
    GUI::draw();
    ofSetColor(uusinVari.getInverted());
    ofDrawBitmapString(moodi, 20, 20);
    ofDrawBitmapString(ofToString(updateCount), 20, 40);
    
    //Piirretään ruudulle väri ja viiva:
    ofSetColor(ofColor::white);
    Monitori::draw();
}


void Ohjain::keyPressed(int key) {
    // gui.handleKey(key);
    if(key == OF_KEY_TAB)
        Monitori::show = !Monitori::show;
}


void Ohjain::mousePressed(int x, int y) {
    //  if (gui.show)
    //      gui.handleClick(x, y);
    //  else {
    ViivanOhjain::mousePressed(x, y);
    //  }
}

