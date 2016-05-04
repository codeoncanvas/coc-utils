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

    swipePixelDistanceThreshold = 50;
    swipePixelVelocityThreshold = 100;
    
    reset();
}

Swipe::~Swipe() {
    //
}

void Swipe::setSwipeArea(const coc::Rect & rect) {
    swipeArea = rect;
}

void Swipe::setSwipeArea(float x, float y, float w, float h) {
    swipeArea.setX(x);
    swipeArea.setY(y);
    swipeArea.setW(w);
    swipeArea.setH(h);
}

void Swipe::setSwipePixelDistanceThreshold(float value) {
    swipePixelDistanceThreshold = value;
}

void Swipe::setSwipePixelVelocityThreshold(float value) {
    swipePixelVelocityThreshold = value;
}

//--------------------------------------------------------------
void Swipe::update(double _optionalTimeElapsedSinceLastUpdateInSeconds) {

    bGestureFoundNew = false; // clear on every new frame.

    //----------------------------------------------------------
    bool bSwipeStopped = false;
    if(points.size() > 0) {
        const SwipePoint & pointLast = points[points.size()-1];
        bSwipeStopped = (pointLast.type == SwipePoint::TypeUp);
        if(bSwipeStopped == true) {
            bool bDownNew = false;
            for(int i=0; i<pointsNew.size(); i++) {
                const SwipePoint & pointNew = pointsNew[i];
                if(pointNew.type == SwipePoint::TypeDown) {
                    bDownNew = true;
                    break;
                }
            }
            if(bDownNew == true) {
                bSwipeStopped = false;
                reset();
            }
        }
    }
    
    if(bSwipeStopped == true) {
        return;
    }

    bool bSwipeStarted = true;
    bSwipeStarted = bSwipeStarted && (points.size() > 0);
    
    bool bSwipeStartedNow = true;
    bSwipeStartedNow = bSwipeStartedNow && (bSwipeStarted == false);
    bSwipeStartedNow = bSwipeStartedNow && (pointsNew.size() > 0);
    if(bSwipeStartedNow == true) {
        bSwipeStartedNow = bSwipeStartedNow && (pointsNew[0].type == SwipePoint::TypeDown);
    }
    
    bool bUpdate = false;
    bUpdate = bUpdate || (bSwipeStarted == true);
    bUpdate = bUpdate || (bSwipeStartedNow == true);
    if(bUpdate == false) {
        return;
    }
    
    double timeElapsedSinceLastUpdateInSeconds = _optionalTimeElapsedSinceLastUpdateInSeconds;
    if(timeElapsedSinceLastUpdateInSeconds < 0.0) {
        timeElapsedSinceLastUpdateInSeconds = coc::getTimeElapsedSinceLastFrame();
    }
    
    if(bSwipeStartedNow == true) {
        swipeTime = 0;
    } else {
        swipeTime += timeElapsedSinceLastUpdateInSeconds;
    }
    
    if(pointsNew.size() == 0) {
        return;
    }
    
    //----------------------------------------------------------
    bool bFound = false;
    SwipePoint pointNew;
    
    if(bSwipeStartedNow == true) {

        // look for touch down.

        for(int i=0; i<pointsNew.size(); i++) {
            if(pointsNew[i].type == SwipePoint::TypeDown) {
                pointNew = pointsNew[i];
                bFound = true;
                break;
            }
        }
    
    } else {
    
        // look for touch up first.
        
        for(int i=pointsNew.size()-1; i>=0; i--) {
            if(pointsNew[i].type == SwipePoint::TypeUp) {
            
                bool bSame = false;
                if(points.size() > 0) {
                    const SwipePoint & pointLast = points[points.size()-1];
                    bSame = true;
                    bSame = bSame && ((int)pointsNew[i].position.x == (int)pointLast.position.x);
                    bSame = bSame && ((int)pointsNew[i].position.y == (int)pointLast.position.y);
                }
                if(bSame == true) {
                    // remove last move point and replace with up point.
                    points.erase(points.begin() + points.size()-1);
                }
            
                pointNew = pointsNew[i];
                bFound = true;
                break;
            }
        }
        
        // look for touch moved first.
        
        if(bFound == false) {
            for(int i=pointsNew.size()-1; i>=0; i--) {
                if(pointsNew[i].type == SwipePoint::TypeMoved) {
                    
                    bool bSame = false;
                    if(points.size() > 0) {
                        const SwipePoint & pointLast = points[points.size()-1];
                        bSame = true;
                        bSame = bSame && ((int)pointsNew[i].position.x == (int)pointLast.position.x);
                        bSame = bSame && ((int)pointsNew[i].position.y == (int)pointLast.position.y);
                    }
                    if(bSame == true) {
                        continue;
                    }
                
                    pointNew = pointsNew[i];
                    bFound = true;
                    break;
                }
            }
        }
    }
    
    pointsNew.clear();
    
    if(bFound == false) {
        return;
    }
    
    points.push_back(pointNew);
    SwipePoint & point = points.back();
    point.time = swipeTime;
    
    if(points.size() > 1) {
    
        const SwipePoint & pointLast = points[points.size()-2];
        point.velocity = (point.position - pointLast.position) / (point.time - pointLast.time);
        point.velocityScale = length(point.velocity) / swipePixelVelocityThreshold;
        
        point.angleDeg = coc::angleClockwise(point.velocity);
        point.angleDeg = (point.angleDeg / (float)M_PI) * 180.0;
    }
    
    //----------------------------------------------------------
    if(gestureStartIndex == -1) {
        gestureStartIndex = points.size() - 1;
    }
    
    SwipePoint gesturePointStart;
    SwipeDirection gestureDirectionStart;
    
    for(int i=gestureStartIndex; i<points.size(); i++) {
        if(i == gestureStartIndex) {
            gesturePointStart = points[i];
            gestureDirectionStart = getDirectionFromAngle(gesturePointStart.angleDeg);
        }
        
        const SwipePoint & gesturePoint = points[i];
        if(gesturePoint.velocityScale < 1.0) {
            gestureDirection = SwipeDirectionUndefined;
            gestureStartIndex = -1;
            break;
        }
        
        SwipeDirection gestureDirectionNew = getDirectionFromAngle(gesturePoint.angleDeg);
        if(gestureDirectionNew != gestureDirectionStart) {
            gestureDirection = SwipeDirectionUndefined;
            gestureStartIndex = -1;
            break;
        }
        
        float dist = distance(gesturePoint.position, gesturePointStart.position);
        if(dist >= swipePixelDistanceThreshold) {
            bGestureFoundNew = gestureDirection != gestureDirectionNew;
            gestureDirection = gestureDirectionNew;
        }
    }
}

void Swipe::reset() {
    
    points.clear();
    swipeTime = 0;
    
    gestureDirection = SwipeDirectionUndefined;
    gestureStartIndex = -1;
}

//--------------------------------------------------------------
void Swipe::pointDown(float x, float y) {
    pointNew(x, y, SwipePoint::TypeDown);
}

void Swipe::pointMoved(float x, float y) {
    pointNew(x, y, SwipePoint::TypeMoved);
}

void Swipe::pointUp(float x, float y) {
    pointNew(x, y, SwipePoint::TypeUp);
}

void Swipe::pointNew(float x, float y, SwipePoint::Type type) {
    pointsNew.push_back(SwipePoint());
    SwipePoint & point = pointsNew.back();
    point.position = vec2(x, y);
    point.type = type;
}

//--------------------------------------------------------------
bool Swipe::hasFoundSwipeGesture() const {
    return bGestureFoundNew;
}

SwipeDirection Swipe::getSwipeGestureDirection() const {
    return gestureDirection;
}

const std::vector<SwipePoint> & Swipe::getPoints() const {
    return points;
}

float Swipe::getSwipeTime() const {
    return swipeTime;
}

//--------------------------------------------------------------
SwipeDirection Swipe::getDirectionFromAngle(float angleDeg) const {
    SwipeDirection dir;
    if((angleDeg > 315 && angleDeg <= 360) || (angleDeg >= 0 && angleDeg <= 45)) {
        dir = SwipeDirectionUp;
    } else if(angleDeg > 45 && angleDeg <= 135) {
        dir = SwipeDirectionRight;
    } else if(angleDeg > 135 && angleDeg <= 225) {
        dir = SwipeDirectionDown;
    } else if(angleDeg > 225 && angleDeg <= 315) {
        dir = SwipeDirectionLeft;
    }
    return dir;
}

}