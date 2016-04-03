#include "ofAppiOS.h"

//--------------------------------------------------------------
void ofAppiOS::setup(){
    app.setup();
}

//--------------------------------------------------------------
void ofAppiOS::update(){
    app.update();
}

//--------------------------------------------------------------
void ofAppiOS::draw(){
	app.draw();
}

//--------------------------------------------------------------
void ofAppiOS::exit(){
    app.exit();
}

//--------------------------------------------------------------
void ofAppiOS::touchDown(ofTouchEventArgs & touch){
    if(touch.id != 0) {
        return;
    }
    app.mousePressed(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void ofAppiOS::touchMoved(ofTouchEventArgs & touch){
    if(touch.id != 0) {
        return;
    }
    app.mouseDragged(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void ofAppiOS::touchUp(ofTouchEventArgs & touch){
    if(touch.id != 0) {
        return;
    }
    app.mouseReleased(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void ofAppiOS::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofAppiOS::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofAppiOS::lostFocus(){

}

//--------------------------------------------------------------
void ofAppiOS::gotFocus(){

}

//--------------------------------------------------------------
void ofAppiOS::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofAppiOS::deviceOrientationChanged(int newOrientation){

}

