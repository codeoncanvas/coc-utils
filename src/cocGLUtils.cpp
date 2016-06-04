//
//  cocGLUtils.cpp
//  WelcomeWall
//
//  Created by Lukasz Karluk on 4/06/2016.
//
//

#include "cocGLUtils.h"

namespace coc {

void enableAlphaBlendingPremult() {
    /**
     *  solution to fbo alpha blending issue.
     *  http://forum.openframeworks.cc/index.php/topic,1643.0.html
     */
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA,
                        GL_ONE_MINUS_SRC_ALPHA,
                        GL_ONE,
                        GL_ONE_MINUS_SRC_ALPHA);
}

};