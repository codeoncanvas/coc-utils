//Cribbed from cinder/Text

/*
 * Usage:
 * vec2 offsetPos(0,0);
 * textTexture = gl::Texture::create( tbox.renderWithLeadingOffset( offsetPos, -3.0f) );
 */

#pragma once

#include "cinder/Cinder.h"
#include "cinder/Surface.h"
#include "cinder/Font.h"
#include "cinder/Vector.h"
#include <vector>
#include <deque>
#include <string>


namespace coc {

class TextBoxExtended : public ci::TextBox
{
public:

	ci::Surface    renderWithLeadingOffset( ci::vec2 offset, float leadingOffset = 0.0f );

private:

	void 			createLinesWithLeadingOffset( float leadingOffset = 0.0f ) const;

};//TextBoxExtended


}//namespace coc