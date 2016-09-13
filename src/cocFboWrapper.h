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

#pragma once

#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/Camera.h"


namespace coc {

class FboWrapper {

public:

    FboWrapper();

    void setup( glm::vec2 _size, bool _isOrtho = true, bool _hasAlpha = false );
    void setup( glm::vec2 _size, ci::gl::Fbo::Format _fmt, bool _isOrtho = true );

    void draw() const;
    void draw( glm::vec2 pos ) const;
    void draw( ci::Rectf bounds ) const;

    void bind();
    void unbind();
    void reset();

    ci::gl::FboRef getFboRef();
    ci::gl::TextureRef getTextureRef();
    bool getIsSetup();

private:

    ci::gl::FboRef      fbo;
    glm::vec2           size;
    ci::CameraOrtho     fboCam;
    bool                isSetup;


};//class FboWrapper

};//namespace coc
