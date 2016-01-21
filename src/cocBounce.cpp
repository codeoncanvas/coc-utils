/*
 *  Ported from ofxBounce.h
 *  https://github.com/julapy/ofxJulapyUtils/blob/master/src/ofxBounce.h
 *
 *  Created by lukasz karluk on 5/01/10.
 *  http://codeoncanvas.cc
 */

#include "cocBounce.h"

namespace coc {

Bounce::Bounce() {
    k = 0.1;    // spring constant.
    i = 0.9;    // inertia.
    c = 0;      // center.
    p = 0;      // position.
    d = 0;      // difference = center - position.
    v = 0;      // velocity.
};
    
void Bounce::update() {
    d = c - p;
    v = v * i + d * k;
    p += v;
};

void Bounce::springconst(float value) {
    k = value;
};

float Bounce::springconst() const {
    return k;
};

void Bounce::inertia(float value) {
    i = value;
};

float Bounce::inertia() const {
    return i;
};

void Bounce::center(float value) {
    c = value;
};

float Bounce::center() const {
    return c;
};

void Bounce::position(float value) {
    p = value;
};

float Bounce::position() const {
    return p;
};

void Bounce::velocity(float value) {
    v = value;
};

float Bounce::velocity() const {
    return v;
};

}

