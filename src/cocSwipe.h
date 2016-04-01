//
//  cocTimer.h
//  Created by Lukasz Karluk on 10/10/2015.
//  http://codeoncanvas.cc
//

#pragma once

#include "cocCore.h"

namespace coc {

//--------------------------------------------------------------
enum SwipeGesture {
    SwipeGestureUndefined = 0,
    SwipeGestureUp,
    SwipeGestureRight,
    SwipeGestureDown,
    SwipeGestureLeft
};

//--------------------------------------------------------------
class SwipePoint {

public:

    enum SwipePointType {
        SwipePointTypeUndefined = 0,
        SwipePointTypeDown,
        SwipePointTypeMoved,
        SwipePointTypeUp
    };

    SwipePoint() {
        type = SwipePointTypeUndefined;
        timeSec = 0;
    }
    
    glm::vec2 position;
    glm::vec2 velocity;
    SwipePointType type;
    float timeSec;
};

//--------------------------------------------------------------
class Swipe {
    
public:
    
    Swipe();
    ~Swipe();
    
    void setSwipeArea(const coc::Rect & rect);
    
    void update(double optionalTimeElapsedSinceLastUpdateInSeconds=-1);
    
    void pointDown(float x, float y);
    void pointMoved(float x, float y);
    void pointUp(float x, float y);
    void pointNew(float x, float y, SwipePoint::SwipePointType type);
    
    const std::vector<SwipePoint> & getPoints() const;
    float getSwipeTime();
    
protected:
    
    std::vector<SwipePoint> points;
    std::vector<SwipePoint> pointsNew;
    coc::Rect swipeArea;
    float swipeTime;
    
};

}