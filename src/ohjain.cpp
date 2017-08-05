#include "ohjain.h"

void Ohjain::setup() {
    gui.setup();
    ViivanOhjain::setup(300);
    VariOhjain::setup();
    ViivanOhjain::moodi = viivaValmis;
    Monitori::setup();
    OscInterface::setAddress("127.0.0.1", 9997, 9998);
}

void Ohjain::update() {

    //kun halutaan lopettaa viiva:
    //Monitori::tyhjenna();
    //minkä jälkeen uusi viiva alkaa taas, kun kutsutaan piirraViiva())
    if (Nauhuri::uusiViiva || (moodi == viivaValmis && tila != soittaa)) {
        Monitori::tyhjenna();
        VariOhjain::asetaVari(ViivanOhjain::viiva.alkuVari);
    }
    if (moodi == piirtaa && ViivanOhjain::viivaOnUusi)
        ViivanOhjain::viiva.alkuVari = haeVari();

    ViivanOhjain::loop();

    //haetaan viiva ja lasketaan väri
    uusinViiva = ViivanOhjain::haeViiva();
    VariOhjain::laskeVari(uusinViiva);
    uusinVari = haeVari();

    //asetetaan monitoriin viiva ja väri. Tämä ei vielä piirrä ruudulle; ks. Monitori::draw()
    //TODO: milloin lopetetaan piirtäminen ja aloitetaan uusi?
    Monitori::piirraVari(uusinVari);
    Monitori::piirraViiva(uusinViiva);

    if (connection && !uusinViiva.pisteet.empty())
        teeOscPakettiJaLaheta(uusinViiva);


    GUI_info_T info = gui.getInfo();
    if (info.connecting) {
        gui.print("connecting to " + info.ip + " @ " + ofToString(info.senderPort) + "," + ofToString(info.receiverPort) + "...");
        OscInterface::setAddress(info.ip, info.senderPort, info.receiverPort);
        if (!OscInterface::connection)
            OscInterface::connect();
        if (OscInterface::connection)
            gui.print("connected");
    }

    if (info.disconnecting) {
        if (OscInterface::connection) {
            gui.print("disconnecting");
            OscInterface::disconnect();
        } else
            gui.print("not connected");
    }



}

void Ohjain::draw() {
    //ofSetColor(uusinVari.getInverted());
    //ofDrawBitmapString(moodi, 20, 20);
    //ofDrawBitmapString(ofToString(updateCount), 20, 40);

    //Piirretään ruudulle väri ja viiva:
    ofSetColor(ofColor::white);
    Monitori::draw();



    if (showDebug) {
        ofDrawBitmapString("tila: " + kerroTila(), 20, 20);

        ofDrawBitmapString("moodi: " + kerroMoodi(), 20, 40);
        ofDrawBitmapString("viivaId: " + std::to_string(viivaId), 20, 60);
        ofDrawBitmapString("lukupaa: " + to_string(lukuPaa), 20, 80);
    }
    gui.draw();

}

void Ohjain::keyPressed(int key) {

    gui.handleKey(key);

    if (key == OF_KEY_TAB) {
        if (Monitori::showing)
            Monitori::piilota();
        else
            Monitori::paljasta();
    }
    if (key == OF_KEY_F1) {
        tila = vapaa;
    }
    if (key == OF_KEY_F2) {
        tila = tallentaa;
    }
    if (key == OF_KEY_F3) {
        tila = soittaa;
    }

    if (key == OF_KEY_F12)
        showDebug = !showDebug;

    if (key == OF_KEY_LEFT && tila == soittaa)
        edellinen();

    if (key == OF_KEY_RIGHT && tila == soittaa)
        seuraava();
}

void Ohjain::mousePressed(int x, int y) {
    if (gui.show) {
        gui.handleClick(x, y);
    } else {
        ViivanOhjain::mousePressed(x, y);
    }
}

void Ohjain::teeOscPakettiJaLaheta(Viiva& viiva) {
    ViivanPiste vp = viiva.haeUusinPiste();

    ofxOscMessage tulkinnatMsg;
    tulkinnatMsg.setAddress("/viiva/tulkinnat");
    tulkinnatMsg.addFloatArg(vp.tulkinnat.kiihtyvyys);
    tulkinnatMsg.addFloatArg(vp.tulkinnat.kohoavuus);
    tulkinnatMsg.addFloatArg(vp.tulkinnat.vahvuus);
    tulkinnatMsg.addFloatArg(vp.tulkinnat.paino.x);
    tulkinnatMsg.addFloatArg(vp.tulkinnat.paino.y);
    tulkinnatMsg.addFloatArg(vp.tulkinnat.paino.z);
    OscInterface::sendMessage(tulkinnatMsg);

    ofxOscMessage yleisetMsg;
    yleisetMsg.setAddress("/viiva/yleiset");
    yleisetMsg.addFloatArg(vp.yleisetOminaisuudet.nopeus);
    yleisetMsg.addFloatArg(vp.yleisetOminaisuudet.paine);
    yleisetMsg.addFloatArg(vp.yleisetOminaisuudet.suunta.x);
    yleisetMsg.addFloatArg(vp.yleisetOminaisuudet.suunta.y);
    yleisetMsg.addFloatArg(vp.yleisetOminaisuudet.suunta.z);
    OscInterface::sendMessage(yleisetMsg);

    ofxOscMessage hetkellisetMsg;
    hetkellisetMsg.setAddress("/viiva/hetkelliset");
    hetkellisetMsg.addFloatArg(vp.hetkellisetOminaisuudet.nopeus);
    hetkellisetMsg.addFloatArg(vp.hetkellisetOminaisuudet.paine);
    hetkellisetMsg.addFloatArg(vp.hetkellisetOminaisuudet.suunta.x);
    hetkellisetMsg.addFloatArg(vp.hetkellisetOminaisuudet.suunta.y);
    hetkellisetMsg.addFloatArg(vp.hetkellisetOminaisuudet.suunta.z);
    OscInterface::sendMessage(hetkellisetMsg);

}
