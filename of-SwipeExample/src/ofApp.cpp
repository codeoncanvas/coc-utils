/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    swipe.setSwipeArea(0, 0, ofGetWidth(), ofGetHeight());
    swipe.setSwipePixelVelocityThreshold(100.0);

    font.load("verdana.ttf", 40);
    fontStr = "";
    fontAlpha = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){

    swipe.update();

    bool bFoundSwipeGesture = swipe.hasFoundSwipeGesture();
    if(bFoundSwipeGesture == true) {
        coc::SwipeDirection swipeDirection = swipe.getSwipeGestureDirection();

        switch (swipeDirection) {

            case coc::SwipeDirectionUp:
                fontStr = "UP";
                break;

            case coc::SwipeDirectionRight:
                fontStr = "RIGHT";
                break;

            case coc::SwipeDirectionDown:
                fontStr = "DOWN";
                break;

            case coc::SwipeDirectionLeft:
                fontStr = "LEFT";
                break;

            default:
                break;
        }

        fontAlpha = 1.0;
    }

    fontAlpha += (0.0 - fontAlpha) * 0.05;
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

    ofSetColor(0, 255 * fontAlpha);
    font.drawString(fontStr, 20, 50);
    ofSetColor(255);
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
