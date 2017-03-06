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
enum ScaleGestureType {
    ScaleGestureNone = 0,
	ScaleGesturePinch,
	ScaleGestureZoom
};

//--------------------------------------------------------------
class ScaleGesture {

public:

    ScaleGesture();
    ~ScaleGesture();

    void setArea( const coc::Rect &rect );
    void setArea( float x, float y, float w, float h );
    void setPixelDistanceThreshold( float value );

    void update(double optionalTimeElapsedSinceLastUpdateInSeconds=-1);
    void reset();

    void pointDown(float x, float y, int pointId );
    void pointMoved(float x, float y, int pointId);
    void pointUp(float x, float y, int pointId);

    bool hasFoundGesture() const;
    ScaleGestureType getGestureType() const;

    const std::vector<ci::vec2> getPoints() const;
	int getNumPoints() { return pointMap.size(); }

	int getDistance() { return lastDistance; }

protected:

	std::map< int, ci::vec2 > pointMap;
	float lastDistance;
	bool bCalcGesture = false;

    coc::Rect gestureRect;
    float pixelDistanceThreshold;

    ScaleGestureType gestureType;
    bool bGestureFound = false;

};

}
