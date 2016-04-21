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
	void update() override;
	void draw() override;
    
    void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
    
    vector<vec2> poly;
    vector<vec2> polyNormals;
    vector<vec2> polyOuter;
    vector<vec2> polyInner;
    
    float normalLenght = 40;
    bool bClosed = false;
};

void PolyExampleApp::setup() {
    //
}

void PolyExampleApp::update() {

    polyNormals = coc::PolyNormals(poly, bClosed);
}

void PolyExampleApp::draw() {

    gl::clear(Color(0, 0, 0));

    int numOfPoints = poly.size();
    int numOfNormals = coc::min(poly.size(), polyNormals.size());

	for(int i=0; i<numOfPoints; i++) {
        if(bClosed == false) {
            if(i == numOfPoints-1) {
                break;
            }
        }
        int j = (i + 1) % numOfPoints;
        const vec2 & p0 = poly[i];
        const vec2 & p1 = poly[j];
        gl::drawLine(p0, p1);
    }
    
	for(int i=0; i<numOfNormals; i++) {
        const vec2 & p0 = poly[i];
        const vec2 & n0 = polyNormals[i];
        gl::drawLine(p0, p0 + (n0 * vec2(normalLenght)));
    }
    
	for(int i=0; i<numOfPoints; i++) {
        const vec2 & p0 = poly[i];
        gl::drawSolidCircle(p0, 4);
    }
}

void PolyExampleApp::mouseDown( MouseEvent event ) {
    poly.push_back(vec2(event.getX(), event.getY()));
}

void PolyExampleApp::keyDown( KeyEvent event ) {
    if(event.getChar() == 'c' || event.getChar() == 'C') {
        bClosed = !bClosed;
    }
}

CINDER_APP( PolyExampleApp, RendererGl )
