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

#include "cocScaleGesture.h"

namespace coc {

using namespace std;
using namespace ci;
using namespace ci::app;

ScaleGesture::ScaleGesture()
{
    pixelDistanceThreshold = 50;
    gestureType = ScaleGestureNone;
}

ScaleGesture::~ScaleGesture()
{

}

void ScaleGesture::setArea( const coc::Rect &rect )
{
    gestureRect = rect;
}

void ScaleGesture::setArea( float x, float y, float w, float h )
{
    gestureRect = Rectf(x,y,x+w,y+h);
}

void ScaleGesture::setPixelDistanceThreshold( float value )
{
    pixelDistanceThreshold = value;
}

void ScaleGesture::update( double optionalTimeElapsedSinceLastUpdateInSeconds )
{

    if (pointMap.size() == 2) {

        auto points = getPoints();
        float distance = glm::distance( points[0], points[1] );

        if (distance > pixelDistanceThreshold) {

            if (!bCalcGesture) {
                lastDistance = distance;
                bCalcGesture = true;
            }
            else {
                if (distance - lastDistance > 0) {
                    gestureType = ScaleGestureZoom;
                }
                else if (distance - lastDistance < 0) {
                    gestureType = ScaleGesturePinch;
                }
                else {
                    gestureType = ScaleGestureNone;
                }
                lastDistance = distance;
                bCalcGesture = true;
            }
        }

    }
    else {
        gestureType = ScaleGestureNone;
        bCalcGesture = false;
    }


}

void ScaleGesture::reset()
{
    gestureType = ScaleGestureNone;
    pointMap.clear();
}

void ScaleGesture::pointDown( float x, float y, int pointId )
{
    vec2 p(x,y);
    if (!gestureRect.contains(p)) return;
    pointMap[pointId] = p;
}

void ScaleGesture::pointMoved( float x, float y, int pointId )
{
    if (!pointMap.count(pointId)) return;
    vec2 p(x,y);
    pointMap[pointId] = p;
}

void ScaleGesture::pointUp( float x, float y, int pointId )
{
//    if (!pointMap.count(pointId)) return;
//    pointMap.erase(pointId);

    pointMap.clear();
}

bool ScaleGesture::hasFoundGesture() const
{
    return gestureType != ScaleGestureNone;
}

ScaleGestureType ScaleGesture::getGestureType() const
{
    return gestureType;
}

const std::vector<ci::vec2> ScaleGesture::getPoints() const
{
    std::vector<glm::vec2> points;
    for (auto p : pointMap)
    {
        points.push_back(p.second);
    }
    return points;
}

}