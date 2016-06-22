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

//
//  Ported from ofxBounce2D.h
//  https://github.com/julapy/ofxJulapyUtils/blob/master/src/ofxBounce2D.h
//

#pragma once

#include "cocCore.h"
#include "cocBounce.h"

namespace coc {

class Bounce2D {

public:

    void update();

    void springconst(float value);
    float springconst();

    void inertia(float value);
    float inertia();

    void center(float x, float y);
    void center(const glm::vec2 & value);
    glm::vec2 center();

    void position(float x, float y);
    void position(const glm::vec2 & value);
    glm::vec2 position();

    void velocity(float x, float y);
    void velocity(const glm::vec2 & value);
    glm::vec2 velocity();

    Bounce bounceX;
    Bounce bounceY;
};

}
