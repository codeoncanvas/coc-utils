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
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"


namespace coc {

class TextBoxExtended : public ci::TextBox
{
public:

	~TextBoxExtended() { reset(); }
	void reset() {  texPreLeading.reset(); }

	void generateTexture();
	void generateLines();
	void drawWithLeading( ci::vec2 _pos, float _leadingOffset );

	int getNumLines() { return numLines; }
	float getLineHeight() { return lineHeight; }
	int getTotalHeight() { return totalHeight; }
	ci::gl::TextureRef getTextureRef() { return texPreLeading; }

	ci::Surface    renderWithLeadingOffset( ci::vec2 offset, float leadingOffset );

private:

	int 					totalHeight;
	int                     numLines 		= 0;
	float                   lineHeight 		= 0;
	ci::gl::TextureRef      texPreLeading 	= nullptr;

#if defined( CINDER_COCOA )
	void 			createLinesWithLeadingOffset( float leadingOffset = 0.0f ) const;
#endif

};//TextBoxExtended


}//namespace coc
