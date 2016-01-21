#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cocBounce2D.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BounceExampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    coc::Bounce2D bounce;
};

void BounceExampleApp::setup()
{
    int cx = getWindowSize().x * 0.5;
    int cy = getWindowSize().y * 0.5;
    
    bounce.center(cx, cy);
    bounce.position(cx, cy);
}

void BounceExampleApp::mouseDown( MouseEvent event )
{
    bounce.velocity(randFloat(-100, 100), randFloat(-100, 100));
}

void BounceExampleApp::update()
{
    bounce.update();
}

void BounceExampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::drawSolidCircle(bounce.position(), 100);
}

CINDER_APP( BounceExampleApp, RendererGl )
