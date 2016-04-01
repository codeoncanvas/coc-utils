//
//  cocTimer.h
//  Created by Lukasz Karluk on 10/10/2015.
//  http://codeoncanvas.cc
//

#include "cocSwipe.h"

namespace coc {

using namespace std;
using namespace glm;

//--------------------------------------------------------------
Swipe::Swipe() {
    swipeTime = 0;
}

Swipe::~Swipe() {
    //
}

void Swipe::setSwipeArea(const coc::Rect & rect) {
    swipeArea = rect;
}

//--------------------------------------------------------------
void Swipe::update(double _optionalTimeElapsedSinceLastUpdateInSeconds) {

    bool bSwipeStarted = true;
    bSwipeStarted = bSwipeStarted && (points.size() > 0);
    
    bool bSwipeStopped = false;
    if(bSwipeStarted == true) {
        bSwipeStopped = bSwipeStopped && (points[points.size()-1].type == SwipePoint::SwipePointTypeUp);
    }
    
    bool bUpdate = false;
    bUpdate = bUpdate || (bSwipeStarted == true);
    bUpdate = bUpdate || (pointsNew.size() > 0);
    bUpdate = bUpdate && (bSwipeStopped == false);
    
    if(bUpdate == false) {
        return;
    }

    double timeElapsedSinceLastUpdateInSeconds = _optionalTimeElapsedSinceLastUpdateInSeconds;
    if(timeElapsedSinceLastUpdateInSeconds < 0.0) {
        timeElapsedSinceLastUpdateInSeconds = coc::getTimeElapsedSinceLastFrame();
    }
    
    swipeTime += timeElapsedSinceLastUpdateInSeconds;
}

//--------------------------------------------------------------
void Swipe::pointDown(float x, float y) {
    pointNew(x, y, SwipePoint::SwipePointTypeDown);
}

void Swipe::pointMoved(float x, float y) {
    pointNew(x, y, SwipePoint::SwipePointTypeMoved);
}

void Swipe::pointUp(float x, float y) {
    pointNew(x, y, SwipePoint::SwipePointTypeUp);
}

void Swipe::pointNew(float x, float y, SwipePoint::SwipePointType type) {
    pointsNew.push_back(SwipePoint());
    SwipePoint & point = pointsNew.back();
    point.position = vec2(x, y);
    point.type = SwipePoint::SwipePointTypeMoved;
}

//--------------------------------------------------------------
const std::vector<SwipePoint> & Swipe::getPoints() const {
    return points;
}

float Swipe::getSwipeTime() {
    return swipeTime;
}

}