#include "GUI.h"
#include <iostream>


// *************** GUI_element ******************* //

GUI_element::GUI_element(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}


bool GUI_element::pointIsInside(int p_x, int p_y) { //true jos annettu piste on elementin sisällä
    if (p_x >= x &&
            p_x <= x + w &&
            p_y >= y &&
            p_y <= y + h)
        return true;
    else return false;
}


// *************** clickable : public GUI_element ********************** //

clickable::clickable(int x_, int y_, int w_, int h_) : GUI_element(x_,y_,w_,h_) {}


bool clickable::getState() { //true if clicked. also resets state
    if (clicked) {
        clicked = false;
        return true;
    } else return false;
}


bool clickable::peek() { //true if clicked, doesn't reset state
    return clicked;
}


void clickable::resetState() { //reset clicked state to false
    clicked = false;
}


void clickable::handleClick(int mouse_x, int mouse_y) {
    if (disabled) return;
    if (pointIsInside(mouse_x, mouse_y)) clicked = true;
}


// *********************** button : public clickable *************** //

button::button(int x_, int y_, int w_, int h_, std::string text) : clickable(x_, y_, w_, h_), label(text) {}


void button::draw(int x0, int y0) {
    if(disabled)        ofSetColor(170,170,170);
    else if(clicked)    ofSetColor(255,0,255);
    else                ofSetColor(100, 100, 100);
    
    ofDrawRectangle(x+x0, y+y0, w, h);
    
    if(disabled) ofSetColor(100,100,100);
    else ofSetColor(0, 255, 255);
    ofDrawBitmapString(label, x+x0 + 10, y+y0 + 14);    
}


// ************** textField : public clickable ************** //

textField::textField(int x_, int y_, int w_, int h_, string text, int max_length) 
        : clickable(x_,y_,w_,h_), label(text), max_l(max_length), mode(TEXTFIELD_DEFAULT) {}


void textField::draw(int x0, int y0) {
    ofSetColor(100, 100, 100);
    ofDrawRectangle(x + x0, y + y0, w, h);

    if (mode == TEXTFIELD_TYPING) ofSetColor(255, 0, 0);
    else ofSetColor(0, 255, 0);

    string displayString = label + ": " + content;
    if (mode == TEXTFIELD_TYPING) displayString += '_';
  
    ofDrawBitmapString(displayString, x + x0 + 10, y + y0 + 14);

}


void textField::handleKey(int key) {
    if(mode == TEXTFIELD_TYPING) {    
        if(key == OF_KEY_RETURN) {
            mode = TEXTFIELD_DEFAULT;
        }
        else {
            content += (char)key;
            if(max_l!=0 && content.length() >= max_l)
                mode = TEXTFIELD_DEFAULT;
        }
    }
}


void textField::handleClick(int m_x, int m_y) {
    if(mode == TEXTFIELD_DEFAULT && pointIsInside(m_x, m_y) ) {
        mode = TEXTFIELD_TYPING;
        content = "";
    }
}


// ************** console : public GUI_element *************** //

console::console(int x_, int y_, int max_length_, int rows_) 
                : GUI_element(x_, y_, 0, 0), max_length(max_length_), rows(rows_) {
    w = max_length * 8 + 10; //10 px per merkki plus 5px marginaalit
    h = rows * 12 + 10; // 12px per rivi plus 5px marginaalit
}


void console::draw(int x0, int y0) {
    
    ofSetColor(210,210,210);
    ofDrawRectangle(x + x0, y + y0, w, h);
    
    ofSetColor(0,0,0);
    
    for(int i=0; i< contents.size(); i++) {
        std::string str = contents[i];
        if(str.length() > max_length) str.resize(max_length);
        
        ofDrawBitmapString(str, x + x0 + 5, y + y0 + i*12 + 15);
    }
}


void console::add(const std::string& str) {
    contents.push_back(str);
    while(contents.size() > rows)
        contents.erase(contents.begin());
}


// ****************** GUI : public GUI_element ********************* //

GUI::GUI(int x_, int y_, int w_, int h_) : GUI_element(x_,y_,w_,h_) {    
}


void GUI::setup() { 
    
    IP_Field = textField(10, 20, 240, 20,"IP Address", 15);
    IP_Field.content = "127.0.0.1";
    
    sendPortField = textField(10, 50, 160, 20,  "Send Port", 5);
    sendPortField.content = "9997";
    
    listenPortField = textField(10, 80, 160, 20,"Listen Port", 5);
    listenPortField.content = "9998";
    
    connectButton = button(320, 20, 100, 20, "connect");    // 410 - 100 = 310
    disconnectButton = button(320, 45, 100, 20, "disconnect");
    
    outputConsole = console(10, 120, 50, 15); //width is length * 8 + 10 px; 50*8+10 = 410
    
}


void GUI::draw() {
    if(show) {
        IP_Field.draw(x, y);
        sendPortField.draw(x,y);
        listenPortField.draw(x,y);
        connectButton.draw(x,y);
        disconnectButton.draw(x,y);
        outputConsole.draw(x,y);
        ofSetColor(200,200,200);
        ofDrawBitmapString(showText, x+5, y+12);
    }
    else{
        ofSetColor(200,200,200);
        ofDrawBitmapString(hideText, x+5, y+12);
    }
}


void GUI::update() {
}


void GUI::handleKey(int key) {
    //for elements
    IP_Field.handleKey(key);
    sendPortField.handleKey(key);
    listenPortField.handleKey(key);
    
    //for the gui
    if(key == hideKey)
        show = !show;
}


void GUI::handleClick(int mouse_x, int mouse_y) {
    IP_Field.handleClick(mouse_x - x, mouse_y - y);
    sendPortField.handleClick(mouse_x - x, mouse_y - y);
    listenPortField.handleClick(mouse_x - x, mouse_y - y);
    connectButton.handleClick(mouse_x - x, mouse_y - y);
    disconnectButton.handleClick(mouse_x - x, mouse_y - y);
}


GUI_info_T GUI::getInfo() {
    //this resets button states
    GUI_info_T info;
    info.ip = IP_Field.content;
    info.senderPort = ofFromString<int>(sendPortField.content);
    info.receiverPort = ofFromString<int>(listenPortField.content);
    info.connecting = connectButton.getState();
    info.disconnecting = disconnectButton.getState();
    return info;    
}


void GUI::print(std::string line) {
    outputConsole.add(line);
}