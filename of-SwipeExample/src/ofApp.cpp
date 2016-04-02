#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    //
}

//--------------------------------------------------------------
void ofApp::update(){
    
    swipe.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    const vector<coc::SwipePoint> & swipePoints = swipe.getPoints();
    if(swipePoints.size() >= 2) {
        for(int i=0; i<swipePoints.size()-1; i++) {
            const coc::SwipePoint & swipePoint0 = swipePoints[i];
            const coc::SwipePoint & swipePoint1 = swipePoints[i+1];
            ofDrawLine(swipePoint0.position.x, swipePoint0.position.y,
                       swipePoint1.position.x, swipePoint1.position.y);
        }
    }
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
    swipe.pointMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    swipe.pointDown(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    swipe.pointUp(x, y);
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