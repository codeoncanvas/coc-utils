#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

#include "cocTextBoxExtended.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TextBoxExtendedSampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	params::InterfaceGlRef	params;
	coc::TextBoxExtended	tbox;
	bool 					roundToInt = true;
	int 					leading = 5;
	int 					numLines = 0;
	bool 					enableDepth = false;
	bool 					drawBounds = false;
};

void TextBoxExtendedSampleApp::setup()
{

	params = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( ivec2( 200, 300 ) ) );
	params->addParam( "roundToInt", &roundToInt );
	params->addParam( "leading", &leading ).min( -20 ).max( 20 );
	params->addParam( "numLines", &numLines );
	params->addParam( "enableDepth", &enableDepth );
	params->addParam( "drawBounds", &drawBounds );

	tbox.setFont( Font("Arial", 13) );
	string txt =  "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc ut nisl bibendum, aliquam arcu scelerisque, ornare arcu. Donec pulvinar mattis nunc, porta efficitur nisi blandit et.";
	tbox.setText( txt + txt + txt );
	tbox.setSize( ivec2( 300, 0) );
	tbox.setColor( Color(1,1,1) );
	tbox.setBackgroundColor( ColorA(0,0,0,0) );

//	tbox.applyLeading(leading,roundToInt); //if not applying in draw
}

void TextBoxExtendedSampleApp::mouseDown( MouseEvent event )
{
}

void TextBoxExtendedSampleApp::update()
{
	numLines = tbox.getNumLines();
}

void TextBoxExtendedSampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	gl::color( Color( 1, 1, 1 ) );
	gl::ScopedBlendAlpha tmp;
	gl::enableDepth(enableDepth);

	tbox.drawWithLeading( vec2(0,0), leading, roundToInt );
//	tbox.drawWithLeading( vec2(0,0) );//if applying in setup
	if (drawBounds) tbox.drawBounds();

	gl::draw( gl::Texture::create( tbox.render(vec2(0,0))), vec2(320,0) );

	params->draw();
}

CINDER_APP( TextBoxExtendedSampleApp, RendererGl )
