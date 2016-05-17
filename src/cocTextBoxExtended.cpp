//Cribbed from cinder/Text

#include "cocTextBoxExtended.h"
#include "cinder/Text.h"
#include "cinder/ip/Fill.h"
#include "cinder/ip/Premultiply.h"
#include "cinder/Utilities.h"
#include "cinder/Noncopyable.h"


#if defined( CINDER_COCOA )
#include "cinder/cocoa/CinderCocoa.h"
#if defined( CINDER_MAC )
#include <ApplicationServices/ApplicationServices.h>
#elif defined( CINDER_COCOA_TOUCH )
#include <CoreText/CoreText.h>
#endif
#elif defined( CINDER_MSW )
#include <Windows.h>
	#define max(a, b) (((a) > (b)) ? (a) : (b))
	#define min(a, b) (((a) < (b)) ? (a) : (b))
	#include <gdiplus.h>
	#undef min
	#undef max
	#include "cinder/msw/CinderMsw.h"
	#include "cinder/msw/CinderMswGdiPlus.h"
	#pragma comment(lib, "gdiplus")
	#include "cinder/Unicode.h"

static const float MAX_SIZE = 1000000.0f;

#endif

namespace coc {

using namespace ci;
using namespace ci::app;
using namespace std;



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

Surface    TextBoxExtended::renderWithLeadingOffset( vec2 offset, float leadingOffset = 0.0f )
{
	//
}

void TextBoxExtended::createLinesWithLeadingOffset( float leadingOffset = 0.0f ) const
{
	//
}

#endif



}//namespace coc