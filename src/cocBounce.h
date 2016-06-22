/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2010-2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

 //
 //  Ported from ofxBounce.h
 //  https://github.com/julapy/ofxJulapyUtils/blob/master/src/ofxBounce.h
 //

#pragma once

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
