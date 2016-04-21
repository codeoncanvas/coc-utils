#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cocPoly.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PolyExampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    coc::Poly poly;
};

void PolyExampleApp::setup()
{
    //
}

void PolyExampleApp::mouseDown( MouseEvent event )
{
    //
}

void PolyExampleApp::update()
{
    //
}

void PolyExampleApp::draw()
{
	//
}

CINDER_APP( PolyExampleApp, RendererGl )
