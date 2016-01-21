#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    int cx = ofGetWidth() * 0.5;
    int cy = ofGetHeight() * 0.5;

    bounce.center(cx, cy);
    bounce.position(cx, cy);
}

//--------------------------------------------------------------
void ofApp::update(){

    bounce.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    ofTranslate(coc::toOf(bounce.position()));
    ofDrawCircle(0, 0, 100);
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bounce.velocity(ofRandom(-100, 100), ofRandom(-100, 100));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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