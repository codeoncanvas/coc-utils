/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

/*

code adapted from:
http://www.videotutorialsrock.com/opengl_tutorial/reflections/video.php

*/

#pragma once

#ifdef COC_CI
#include "cinder/gl/gl.h"
#endif

#ifdef COC_OF
#include "ofMain.h"
#endif

namespace coc {

//! \brief Static functions for using stencil buffer

/*!
Example usage:
```
coc::stencil::beginDrawingStencil();
//Draw your mask here.
coc::stencil::beginUsingStencil();
//Draw your scene to be masked here.
coc::stencil::endUsingStencil();
```
*/

namespace stencil {

    //! Set up to draw stencil
    static void beginDrawingStencil() {
        glClear(GL_STENCIL_BUFFER_BIT);
        glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
        glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
        glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
        //Make pixels in the stencil buffer be set to 1 when the stencil test passes
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        //Set all of the pixels below to be 1 in the stencil buffer...
    }

    //! Switch from drawing stencil to scene to be masked
    //! \param _invert If true masks area not drawn.
    static void beginUsingStencil(bool _invert = false) {
        glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
        //Make the stencil test pass only when the pixel is 1 in the stencil buffer unless inverted
        _invert ? glStencilFunc(GL_NOTEQUAL, 1, 1) : glStencilFunc(GL_EQUAL, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
        //Draw all pixels where the stencil buffer is 1...
    }

    //! Switch back to normal unmasked drawing
    static void endUsingStencil() {
        glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
    }

}//namespace stencil

}//namespace coc
