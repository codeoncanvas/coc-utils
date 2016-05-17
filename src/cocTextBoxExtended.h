//Cribbed from cinder/Text

/*
 * Usage:
 * vec2 offsetPos(0,0);
 * textTexture = gl::Texture::create( tbox.renderWithLeadingOffset( offsetPos, -3.0f) );
 */

#pragma once

#include "cinder/Text.h"


namespace coc {

class TextBoxExtended : public ci::TextBox
{
public:

	~TextBoxExtended() { texPreLeading.reset(); }

	void generateTexture();
	void generateLines();
	void drawWithLeading( float _leadingOffset );

	int getNumLines() { return numLines; }
	float getLineHeight() { return lineHeight; }

	ci::Surface    renderWithLeadingOffset( ci::vec2 offset, float leadingOffset = 0.0f );

private:

	int                     numLines 		= 0;
	float                   lineHeight 		= 0;
	ci::gl::TextureRef      texPreLeading 	= nullptr;

#if defined( CINDER_COCOA )
	void 			createLinesWithLeadingOffset( float leadingOffset = 0.0f ) const;
#endif

};//TextBoxExtended


}//namespace coc