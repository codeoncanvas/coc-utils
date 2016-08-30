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

#include "cocTextBoxExtended.h"
#include "cinder/ip/Fill.h"
#include "cinder/ip/Premultiply.h"
#include "cinder/Utilities.h"
#include "cinder/Noncopyable.h"
#include "cinder/Log.h"

#if defined( CINDER_COCOA )
#include "cinder/cocoa/CinderCocoa.h"
#if defined( CINDER_MAC )
#include <ApplicationServices/ApplicationServices.h>
#elif defined( CINDER_COCOA_TOUCH )
#include <CoreText/CoreText.h>
#endif
#elif defined( CINDER_MSW )
//
#endif

namespace coc {

using namespace ci;
using namespace std;

void TextBoxExtended::generateTexture() {
	texPreLeading = ci::gl::Texture2d::create( render() );
}

void TextBoxExtended::generateLines() {


	if (!texPreLeading) generateTexture();

	//--------------------------------------------------------separate lines

	std::vector<std::pair<uint16_t,ci::vec2> >pairs = measureGlyphs();
	int counter = 0;
	float y = 0;//-99999;

	string text = getText();
	vector<string> lines;
	string line;
	int i = 0;
	for (auto p : pairs ) {

		if ( p.second.y > y) {
			counter++;
			y = p.second.y;
			if (i>0) lines.push_back(line);
			line="";
		}
		line += text[i];
		i++;
	}
	lines.push_back(line);

	//--------------------------------------------------------render lines

	TextBox tbox;
	tbox.setFont( getFont() );
	tbox.setColor( getColor() );
	tbox.setBackgroundColor( getBackgroundColor() );
	tbox.setSize( vec2( getSize().x, 0) );

	float lastLineHeight = 0;
	for ( int i = 0; i<lines.size(); i++ ) {

		tbox.setText(lines[i]);
		gl::TextureRef tex = gl::Texture::create( tbox.render( vec2(0,0) ) );
		linesTex.push_back( tex );

		lineHeight = tex->getHeight();

		if ( i>0 && lineHeight != lastLineHeight) {
			CI_LOG_E("Line texture heights vary!");
			lastLineHeight = lineHeight;
		}
		else {
			lastLineHeight = lineHeight;
		}

	}

}

void TextBoxExtended::applyLeading( float _leadingOffset, bool _roundToInt )
{
	leadingOffset = _leadingOffset;
	roundToInt = _roundToInt;
	linesPos.clear();

	if (!linesTex.size()) generateLines();

	if (linesTex.size() > 1) {

		for (int i=0; i<linesTex.size(); i++) {
			vec2 pos(0,0);
			pos.y = i*lineHeight + i*_leadingOffset;
			if (_roundToInt) pos.y = (int) pos.y;
			linesPos.push_back(pos);
		}
		totalHeight = totalHeight = linesTex.size()*lineHeight + (linesTex.size()-1) * leadingOffset;
	}
	else {
		totalHeight = texPreLeading->getHeight();
	}
}

void TextBoxExtended::drawWithLeading( ci::vec2 _pos )
{
	if (roundToInt) _pos = (ivec2) _pos;
	if (!linesTex.size()) {
		CI_LOG_E("Must call applyLeading()!");
		return;
	}

	if ( leadingOffset == 0 || linesTex.size() < 2 ) {
		gl::draw( texPreLeading, _pos);
	}
	else {
		for (int i=0; i<linesTex.size(); i++) {
			gl::draw( linesTex[i], linesPos[i] + _pos);
		}
	}

}

void TextBoxExtended::drawWithLeading( ci::vec2 _pos, float _leadingOffset, bool _roundToInt ) {

	if (_roundToInt) _pos = (ivec2) _pos;
	if (!linesTex.size()) generateLines();

	if ( linesTex.size() > 1 ) {

		for (int i=0; i<linesTex.size(); i++) {

			vec2 pos(0,0);
			pos.y = i*lineHeight + i*_leadingOffset;
			if (_roundToInt) pos.y = (int) pos.y;
			gl::draw(linesTex[i], pos + _pos);

		}

		totalHeight = linesTex.size()*lineHeight + (linesTex.size()-1) * _leadingOffset;
	}
	else {
		gl::draw( texPreLeading, _pos);
		totalHeight = texPreLeading->getHeight();
	}

}

// CRIBBED FROM cinder/Text.cpp :

#if defined( CINDER_COCOA )

Surface TextBoxExtended::renderWithLeadingOffset( vec2 offset, float leadingOffset )
{
	createLinesWithLeadingOffset( leadingOffset );

	float sizeX = ( mSize.x <= 0 ) ? mCalculatedSize.x : mSize.x;
	float sizeY = ( mSize.y <= 0 ) ? mCalculatedSize.y : mSize.y;
	sizeX = math<float>::ceil( sizeX );
	sizeY = math<float>::ceil( sizeY );

	Surface result( (int)sizeX, (int)sizeY, true );
	ip::fill( &result, mBackgroundColor );
	::CGContextRef cgContext = cocoa::createCgBitmapContext( result );
	if( ! cgContext )
		return result;

	::CGContextSetTextMatrix( cgContext, CGAffineTransformIdentity );

	for( vector<pair<shared_ptr<const __CTLine>,vec2> >::const_iterator lineIt = mLines.begin(); lineIt != mLines.end(); ++lineIt ) {
		::CGContextSetTextPosition( cgContext, lineIt->second.x + offset.x, sizeY - lineIt->second.y + offset.y );
		::CTLineDraw( lineIt->first.get(), cgContext );
	}
	CGContextFlush( cgContext );
	CGContextRelease( cgContext );

	if( ! mPremultiplied )
		ip::unpremultiply( &result );
	else
		result.setPremultiplied( true );

	return result;
}

void TextBoxExtended::createLinesWithLeadingOffset( float leadingOffset ) const
{
	if( ! mInvalid )
		return;

	CFRange range = CFRangeMake( 0, 0 );
	CFAttributedStringRef attrStr = cocoa::createCfAttributedString( mText, mFont, mColor, mLigate );
	if( ! attrStr )
		return;
	CTTypesetterRef typeSetter = ::CTTypesetterCreateWithAttributedString( attrStr );

	CFIndex strLength = ::CFAttributedStringGetLength( attrStr );

	double maxWidth = ( mSize.x <= 0 ) ? CGFLOAT_MAX : mSize.x;

	float flush = 0;
	if( mAlign == TextBox::CENTER ) flush = 0.5f;
	else if( mAlign == TextBox::RIGHT ) flush = 1;

	mCalculatedSize = vec2();
	mLines.clear();
	vec2 lineOffset = vec2();
	while( range.location < strLength ) {
		CGFloat ascent, descent, leading;
		range.length = ::CTTypesetterSuggestLineBreak( typeSetter, range.location, maxWidth );
		CTLineRef line = ::CTTypesetterCreateLine( typeSetter, range );
		double lineWidth = ::CTLineGetTypographicBounds( line, &ascent, &descent, &leading );

		leading += leadingOffset;

		lineOffset.x = ::CTLineGetPenOffsetForFlush( line, flush, maxWidth );
		lineOffset.y += ascent;
		mLines.push_back( make_pair( shared_ptr<__CTLine>( (__CTLine*)line, ::CFRelease ), lineOffset ) );
		lineOffset.y += descent + leading;
		mCalculatedSize.x = std::max( mCalculatedSize.x, (float)lineWidth );
		mCalculatedSize.y += ascent + descent + leading;
		range.location += range.length;
	}

	::CFRelease( attrStr );
	::CFRelease( typeSetter );

	mInvalid = false;
}

#elif defined( CINDER_MSW )

Surface TextBoxExtended::renderWithLeadingOffset( vec2 offset, float leadingOffset )
{
	CI_LOG_E( "Does not work on windows" );
	return render();
}

#endif



}//namespace coc
