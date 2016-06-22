/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2015-2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

#pragma once

#include "cocCore.h"

namespace coc {

//--------------------------------------------------------------
enum SwipeDirection {
    SwipeDirectionUndefined = 0,
    SwipeDirectionUp,
    SwipeDirectionRight,
    SwipeDirectionDown,
    SwipeDirectionLeft
};

//--------------------------------------------------------------
class SwipePoint {

public:

    enum Type {
        TypeUndefined = 0,
        TypeDown,
        TypeMoved,
        TypeUp
    };

    SwipePoint() {
        type = TypeUndefined;
        velocityScale = 0;
        angleDeg = 0;
        time = 0;
    }

    Type type;
    glm::vec2 position;
    glm::vec2 velocity;
    float velocityScale;
    float angleDeg;
    float time;
};

//--------------------------------------------------------------
class Swipe {

public:

    Swipe();
    ~Swipe();

    void setSwipeArea(const coc::Rect & rect);
    void setSwipeArea(float x, float y, float w, float h);
    void setSwipePixelDistanceThreshold(float value);
    void setSwipePixelVelocityThreshold(float value);

    void update(double optionalTimeElapsedSinceLastUpdateInSeconds=-1);
    void reset();

    void pointDown(float x, float y);
    void pointMoved(float x, float y);
    void pointUp(float x, float y);
    void pointNew(float x, float y, SwipePoint::Type type);

    bool hasFoundSwipeGesture() const;
    SwipeDirection getSwipeGestureDirection() const;

    const std::vector<SwipePoint> & getPoints() const;
    float getSwipeTime() const;

protected:

    SwipeDirection getDirectionFromAngle(float angleDeg) const;

    std::vector<SwipePoint> points;
    std::vector<SwipePoint> pointsNew;
    coc::Rect swipeArea;
    float swipePixelDistanceThreshold;
    float swipePixelVelocityThreshold;
    float swipeTime;

    SwipeDirection gestureDirection;
    int gestureStartIndex;
    bool bGestureFoundNew;

};

}
