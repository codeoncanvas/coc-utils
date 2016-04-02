#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    swipe.setSwipeArea(0, 0, ofGetWidth(), ofGetHeight());
    swipe.setSwipePixelVelocityThreshold(100.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    swipe.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    const vector<coc::SwipePoint> & swipePoints = swipe.getPoints();
    
    ofPolyline poly;
    
    for(int i=0; i<swipePoints.size(); i++) {
        const coc::SwipePoint & swipePoint = swipePoints[i];
        poly.addVertex(swipePoint.position.x, swipePoint.position.y);
    }
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    ofColor color0 = ofColor::green;
    ofColor color1 = ofColor::red;
    float thick = 2.0;
    
    for(int i=0; i<swipePoints.size(); i++) {
        const coc::SwipePoint & swipePoint = swipePoints[i];
    
        ofVec3f pos = poly[i];
        ofVec3f norm = poly.getNormalAtIndex(i);
        
        mesh.addVertex(pos + norm * thick);
        mesh.addVertex(pos - norm * thick);

        float colorScale = ofMap(swipePoint.velocityScale, 0.0, 1.0, 0.0, 1.0, true);
        ofColor color = color0.getLerped(color1, colorScale);
        
        mesh.addColor(color);
        mesh.addColor(color);
    }
    
    mesh.draw();
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