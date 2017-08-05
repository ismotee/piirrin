#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    Ohjain::setup();
    ofBackground(ofColor::black);
   // glEnable(GL_FRAMEBUFFER_SRGB);    
    ofSetFrameRate(60);
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    Ohjain::update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    Ohjain::draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    Ohjain::keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    Ohjain::mouseMoved(x,y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    Ohjain::mouseDragged(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    Ohjain::mousePressed(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    Ohjain::mouseReleased(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}