#include "ohjain.h"

void Ohjain::setup() {
    hidpen::setup(0);
    gui.setup();
    Sessio::setup(300);
    timedThread::setup(120);

}

void Ohjain::update() {
    Sessio::update();

//    if (Sessio::moodi == piirtaa)
//        vOhjain.lisaaPiste(hiiri.mouseState, 1);

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

void Ohjain::loop() {
    hidpen::update();
    switch (Sessio::moodi) {
        case piirtaa:
            if (hidpen::isOpen)
                vOhjain.lisaaPiste(hiiri.mouseState, (0.25 - hidpen::pressure)*4);
            else
                vOhjain.lisaaPiste(hiiri.mouseState, 1);
            break;
        case viivaValmis:
            vOhjain.tyhjenna();
            break;
    }
}

void Ohjain::draw() {
    gui.draw();
    if (Sessio::moodi == piirtaa) {
        ofDrawBitmapString(vOhjain.viiva.toString(), 20, 30);
    }

}

void Ohjain::keyPressed(int key) {
    gui.handleKey(key);
}

void Ohjain::mousePressed(int x, int y) {
    if (gui.show)
        gui.handleClick(x, y);
    else {
        hiiri.mousePressed(x, y);
    }
}

