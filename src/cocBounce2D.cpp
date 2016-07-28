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

#include "cocBounce2D.h"

namespace coc {

void Bounce2D::update() {
    bounceX.update();
    bounceY.update();
};

void Bounce2D::springconst(float value) {
    bounceX.springconst(value);
    bounceY.springconst(value);
};

float Bounce2D::springconst() {
    return bounceX.springconst();
};

void Bounce2D::inertia(float value) {
    bounceX.inertia(value);
    bounceY.inertia(value);
};

float Bounce2D::inertia() {
    return bounceX.inertia();
};

void Bounce2D::center(float x, float y) {
    glm::vec2 vec(x, y);
    center(vec);
}

void Bounce2D::center(const glm::vec2 & value) {
    bounceX.center(value.x);
    bounceY.center(value.y);
};

glm::vec2 Bounce2D::center() {
    return glm::vec2(bounceX.center(), bounceY.center());
};

void Bounce2D::position(float x, float y) {
    glm::vec2 vec(x, y);
    position(vec);
}

void Bounce2D::position(const glm::vec2 & value) {
    bounceX.position(value.x);
    bounceY.position(value.y);
};

glm::vec2 Bounce2D::position() {
    return glm::vec2(bounceX.position(), bounceY.position());
};

void Bounce2D::velocity(float x, float y) {
    glm::vec2 vec(x, y);
    velocity(vec);
}

void Bounce2D::velocity(const glm::vec2 & value) {
    bounceX.velocity(value.x);
    bounceY.velocity(value.y);
};

glm::vec2 Bounce2D::velocity() {
    return glm::vec2(bounceX.velocity(), bounceY.velocity());
};

}
