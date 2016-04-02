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
    swipePixelVelocityThreshold = 100;
}

Swipe::~Swipe() {
    //
}

void Swipe::setSwipeArea(const coc::Rect & rect) {
    swipeArea = rect;
}

void Swipe::setSwipePixelVelocityThreshold(float value) {
    swipePixelVelocityThreshold = value;
}

//--------------------------------------------------------------
void Swipe::update(double _optionalTimeElapsedSinceLastUpdateInSeconds) {

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
                points.clear();
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
    
    SwipePoint * pointNew = NULL;
    
    if(bSwipeStartedNow == true) {

        // look for touch down.

        for(int i=0; i<pointsNew.size(); i++) {
            if(pointsNew[i].type == SwipePoint::TypeDown) {
                pointNew = &pointsNew[i];
                break;
            }
        }
    
    } else {
    
        // look for touch up first.
        
        for(int i=pointsNew.size()-1; i>=0; i--) {
            if(pointsNew[i].type == SwipePoint::TypeUp) {
                pointNew = &pointsNew[i];
                break;
            }
        }
        
        // look for touch moved first.
        
        if(pointNew == NULL) {
            for(int i=pointsNew.size()-1; i>=0; i--) {
                if(pointsNew[i].type == SwipePoint::TypeMoved) {
                    pointNew = &pointsNew[i];
                    break;
                }
            }
        }
    }
    
    if(pointNew == NULL) {
        return;
    }
    
    points.push_back(SwipePoint());
    SwipePoint & point = points.back();
    point.position = pointNew->position;
    point.type = pointNew->type;
    point.time = swipeTime;
    
    cout << point.type << " " << point.time << endl;
    
    pointsNew.clear();
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
const std::vector<SwipePoint> & Swipe::getPoints() const {
    return points;
}

float Swipe::getSwipeTime() const {
    return swipeTime;
}

}