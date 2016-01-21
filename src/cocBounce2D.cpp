//
//  Ported from ofxBounce2D.h
//  https://github.com/julapy/ofxJulapyUtils/blob/master/src/ofxBounce2D.h
//
//  Created by Lukasz Karluk on 19/08/2015.
//  http://codeoncanvas.cc
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
