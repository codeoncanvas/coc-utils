/*
 *  Ported from ofxBounce.h
 *  https://github.com/julapy/ofxJulapyUtils/blob/master/src/ofxBounce.h
 *
 *  Created by lukasz karluk on 5/01/10.
 *  http://codeoncanvas.cc
 */

#pragma once

#include "cocCore.h"

namespace coc {

class Bounce {
    
public:
    
    Bounce();
    
    void update();
    
    void springconst(float value);
    float springconst() const;
    
    void inertia(float value);
    float inertia() const;
    
    void center(float value);
    float center() const;
    
    void position(float value);
    float position() const;
    
    void  velocity(float value);
    float velocity() const;
    
private:
    
    float k;  // spring constant.
    float i;  // inertia.
    float c;  // center.
    float p;  // position.
    float d;  // difference = center - position.
    float v;  // velocity.
    
};

}