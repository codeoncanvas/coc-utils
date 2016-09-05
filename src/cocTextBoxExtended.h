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

	//! Pre-calculates leading
	void applyLeading( float _leadingOffset, bool _roundToInt = false );

	void generateTexture();
	void generateLines();

	//! Calculates leading in draw if you want to adjust in realtime
	void drawWithLeading( ci::vec2 _pos, float _leadingOffset, bool _roundToInt = false );

	//! Draws based on pre-calculated leading
	void drawWithLeading( ci::vec2 _pos );


	int getNumLines() { return linesTex.size(); }
	float getLineHeight() { return lineHeight; }
	int getTotalHeight() { return totalHeight; }
	ci::gl::TextureRef getTextureRef() const { return texPreLeading; }

	ci::Surface    renderWithLeadingOffset( ci::vec2 offset, float leadingOffset );

#if defined(CINDER_MSW)
	std::vector< std::pair< uint16_t, ci::vec2 > > TextBoxExtended::measureGlyphs() const;
#endif

private:

	std::vector<ci::gl::TextureRef>	linesTex;
	std::vector<ci::vec2>	linesPos;
	float 					leadingOffset = 0;
	bool 					roundToInt = false;

	int 					totalHeight		= 0;
	float                   lineHeight 		= 0;
	ci::gl::TextureRef      texPreLeading 	= nullptr;

#if defined( CINDER_COCOA )
	void 			createLinesWithLeadingOffset( float leadingOffset = 0.0f ) const;
#endif

};//TextBoxExtended


}//namespace coc
