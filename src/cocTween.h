//
//  cocTween.h
//  Rutherford
//
//  Created by Lukasz Karluk on 21/03/2016.
//
//

#pragma once

#include "cocCore.h"

namespace coc {

//-----------------------------------------------------------------------
enum EaseFunction {
    EASE_BACK_IN = 0,
    EASE_BACK_OUT,
    EASE_BACK_INOUT,
    EASE_BOUNCE_IN,
    EASE_BOUNCE_OUT,
    EASE_BOUNCE_INOUT,
    EASE_CIRC_IN,
    EASE_CIRC_OUT,
    EASE_CIRC_INOUT,
    EASE_CUBIC_IN,
    EASE_CUBIC_OUT,
    EASE_CUBIC_INOUT,
    EASE_ELASTIC_IN,
    EASE_ELASTIC_OUT,
    EASE_ELASTIC_INOUT,
    EASE_EXPO_IN,
    EASE_EXPO_OUT,
    EASE_EXPO_INOUT,
    EASE_LINEAR_IN,
    EASE_LINEAR_OUT,
    EASE_LINEAR_INOUT,
    EASE_QUAD_IN,
    EASE_QUAD_OUT,
    EASE_QUAD_INOUT,
    EASE_QUART_IN,
    EASE_QUART_OUT,
    EASE_QUART_INOUT,
    EASE_QUINT_IN,
    EASE_QUINT_OUT,
    EASE_QUINT_INOUT,
    EASE_SINE_IN,
    EASE_SINE_OUT,
    EASE_SINE_INOUT
};

//----------------------------------------------------------------------- Easing
class Easing {
public:
    virtual float easeIn(float t, float b, float c, float d) const;
    virtual float easeOut(float t, float b, float c, float d) const;
    virtual float easeInOut(float t, float b, float c, float d) const;
};

//----------------------------------------------------------------------- EasingBack
class EasingBack: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        float s = 1.70158f;
        float postFix = t/=d;
        return c*(postFix)*t*((s+1)*t - s) + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        float s = 1.70158f;
        return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        float s = 1.70158f;
        if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
        float postFix = t-=2;
        return c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
    }
};

//----------------------------------------------------------------------- EasingBounce
class EasingBounce: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return c - easeOut (d-t, 0, c, d) + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        if ((t/=d) < (1/2.75f)) {
            return c*(7.5625f*t*t) + b;
        } else if (t < (2/2.75f)) {
            float postFix = t-=(1.5f/2.75f);
            return c*(7.5625f*(postFix)*t + .75f) + b;
        } else if (t < (2.5/2.75)) {
			float postFix = t-=(2.25f/2.75f);
            return c*(7.5625f*(postFix)*t + .9375f) + b;
        } else {
            float postFix = t-=(2.625f/2.75f);
            return c*(7.5625f*(postFix)*t + .984375f) + b;
        }
    }
    float easeInOut(float t,float b , float c, float d) const {
        if (t < d/2) return easeIn (t*2, 0, c, d) * .5f + b;
        else return easeOut (t*2-d, 0, c, d) * .5f + c*.5f + b;
    }
};

//----------------------------------------------------------------------- EasingCirc
class EasingCirc: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return c * sqrt(1 - (t=t/d-1)*t) + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
        return c/2 * (sqrt(1 - t*(t-=2)) + 1) + b;
    }
};

//----------------------------------------------------------------------- EasingCubic
class EasingCubic: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return c*(t/=d)*t*t + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return c*((t=t/d-1)*t*t + 1) + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        if ((t/=d/2) < 1) return c/2*t*t*t + b;
        return c/2*((t-=2)*t*t + 2) + b;
    }
};

//----------------------------------------------------------------------- EasingElastic
class EasingElastic: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        if (t==0) return b;  if ((t/=d)==1) return b+c;
        float p=d*.3f;
        float a=c;
        float s=p/4;
        float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
        return -(postFix * sin((t*d-s)*(2*M_PI)/p )) + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        if (t==0) return b;  if ((t/=d)==1) return b+c;
        float p=d*.3f;
        float a=c;
        float s=p/4;
        return (a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b);
    }
    float easeInOut(float t,float b , float c, float d) const {
        if (t==0) return b;  if ((t/=d/2)==2) return b+c;
        float p=d*(.3f*1.5f);
        float a=c;
        float s=p/4;
        if (t < 1) {
            float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
            return -.5f*(postFix* sin( (t*d-s)*(2*M_PI)/p )) + b;
        }
        float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
        return postFix * sin( (t*d-s)*(2*M_PI)/p )*.5f + c + b;
    }
};

//----------------------------------------------------------------------- EasingExpo
class EasingExpo: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        if (t==0) return b;
        if (t==d) return b+c;
        if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
        return c/2 * (-pow(2, -10 * --t) + 2) + b;
    }
};

//----------------------------------------------------------------------- EasingLinear
class EasingLinear: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return c*t/d + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return c*t/d + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        return c*t/d + b;
    }
};

//----------------------------------------------------------------------- EasingQuad
class EasingQuad: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return c*(t/=d)*t + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return -c *(t/=d)*(t-2) + b;
    }
    
    float easeInOut(float t,float b , float c, float d) const {
        if ((t/=d/2) < 1) return c/2*t*t + b;
        return -c/2 * ((--t)*(t-2) - 1) + b;
    }
};

//----------------------------------------------------------------------- EasingQuart
class EasingQuart: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return c*(t/=d)*t*t*t + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return -c * ((t=t/d-1)*t*t*t - 1) + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
        return -c/2 * ((t-=2)*t*t*t - 2) + b;
    }
};

//----------------------------------------------------------------------- EasingQuint
class EasingQuint: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return c*(t/=d)*t*t*t*t + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return c*((t=t/d-1)*t*t*t*t + 1) + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
        return c/2*((t-=2)*t*t*t*t + 2) + b;
    }
};

//----------------------------------------------------------------------- EasingSine
class EasingSine: public Easing {
public:
    float easeIn (float t,float b , float c, float d) const {
        return -c * cos(t/d * (M_PI/2)) + c + b;
    }
    float easeOut(float t,float b , float c, float d) const {
        return c * sin(t/d * (M_PI/2)) + b;
    }
    float easeInOut(float t,float b , float c, float d) const {
        return -c/2 * (cos(M_PI*t/d) - 1) + b;
    }
};

//----------------------------------------------------------------------- Tween
class Tween {

public:
    
    //-------------------------------------------------------------------
    float tween(float value, float inputMin, float inputMax, float outputMin, float outputMax, EaseFunction easingFunc, bool bClamp = false) {

        float t = coc::map(value, inputMin, inputMax, 0.0, 1.0, bClamp);
        float b = outputMin;
        float c = outputMax - outputMin;
        float d = 1.0;
        
        const Easing & easing = getEasing(easingFunc);
        unsigned int easeType = (int)easingFunc % 3;
        
        if(easeType == 0) {
            
            return easing.easeIn(t, b, c, d);
            
        } else if(easeType == 1) {
            
            return easing.easeOut(t, b, c, d);
            
        } else if(easeType == 2) {
        
            return easing.easeInOut(t, b, c, d);
        }
        
        return 0;
    }
    
    //-----------------------------------------------------------------------
    const Easing & getEasing(EaseFunction easeFunc) {

        if((easeFunc == EASE_BACK_IN)  ||
           (easeFunc == EASE_BACK_OUT) ||
           (easeFunc == EASE_BACK_INOUT)) {
        
            return easingBack;
            
        } else if((easeFunc == EASE_BOUNCE_IN)  ||
                  (easeFunc == EASE_BOUNCE_OUT) ||
                  (easeFunc == EASE_BOUNCE_INOUT)) {
        
            return easingBounce;
            
        } else if((easeFunc == EASE_CIRC_IN)  ||
                  (easeFunc == EASE_CIRC_OUT) ||
                  (easeFunc == EASE_CIRC_INOUT)) {
        
            return easingCirc;
            
        } else if((easeFunc == EASE_CUBIC_IN)  ||
                  (easeFunc == EASE_CUBIC_OUT) ||
                  (easeFunc == EASE_CUBIC_INOUT)) {
         
            return easingCubic;
            
        } else if((easeFunc == EASE_ELASTIC_IN)  ||
                  (easeFunc == EASE_ELASTIC_OUT) ||
                  (easeFunc == EASE_ELASTIC_INOUT)) {

            return easingElastic;
            
        } else if((easeFunc == EASE_EXPO_IN)  ||
                  (easeFunc == EASE_EXPO_OUT) ||
                  (easeFunc == EASE_EXPO_INOUT)) {

            return easingExpo;
            
        } else if((easeFunc == EASE_QUAD_IN)  ||
                  (easeFunc == EASE_QUAD_OUT) ||
                  (easeFunc == EASE_QUAD_INOUT)) {
        
            return easingQuad;
            
        } else if((easeFunc == EASE_QUART_IN)  ||
                  (easeFunc == EASE_QUART_OUT) ||
                  (easeFunc == EASE_QUART_INOUT)) {

            return easingQuart;
            
        } else if((easeFunc == EASE_QUINT_IN)  ||
                  (easeFunc == EASE_QUINT_OUT) ||
                  (easeFunc == EASE_QUINT_INOUT)) {

            return easingQuint;
            
        } else if((easeFunc == EASE_SINE_IN)  ||
                  (easeFunc == EASE_SINE_OUT) ||
                  (easeFunc == EASE_SINE_INOUT)) {

            return easingSine;
        }
        
        return easingLinear; // default.
    }
    
protected:
    
    EasingBack easingBack;
    EasingBounce easingBounce;
    EasingCirc easingCirc;
    EasingCubic easingCubic;
    EasingElastic easingElastic;
    EasingExpo easingExpo;
    EasingLinear easingLinear;
    EasingQuad easingQuad;
    EasingQuart easingQuart;
    EasingQuint easingQuint;
    EasingSine easingSine;
};

//-----------------------------------------------------------------------
static float tween(float value, float inputMin, float inputMax, float outputMin, float outputMax, EaseFunction easingFunc, bool bClamp = false) {
    static Tween tweenObj;
    return tweenObj.tween(value, inputMin, inputMax, outputMin, outputMax, easingFunc, bClamp);
}

};