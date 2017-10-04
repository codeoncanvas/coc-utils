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
 * */

#include "cocPolyEditor.h"
#include "cinder/Utilities.h"
#include "cinder/Log.h"
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;


namespace coc {


void PolyEditor::setup( string _filename ) {

    mFilename = _filename;

    fs::path settings = getAssetPath("") / mFilename;
    if( fs::exists( settings ) )
    {
        try {

            xml = XmlTree( loadAsset( mFilename ) ).getChild("polys/poly");
            string val = xml.getValue();

            if ( val !="") {
                CI_LOG_V("Loading poly: " << val);

                boost::trim(val);
                vector<string> pieces = split(val, " ", true);
                vector<string> types;
                vector<vec2> points;

                for (int i = 0; i < pieces.size();) {
                    if (
                            pieces[i] == "M" ||
                                    pieces[i] == "L" ||
                                    pieces[i] == "Q" ||
                                    pieces[i] == "C" ||
                                    pieces[i] == "Z"
                            ) {
                        types.push_back(pieces[i]);
                        i++;
                    }
                    else {
                        vec2 p;
                        p.x = fromString<int>(pieces[i]);
                        p.y = fromString<int>(pieces[i + 1]);
                        points.push_back(p);
                        i += 2;
                    }
                }

                int pointIndex = 0;
                for (int i = 0; i < types.size(); i++) {

                    if (types[i] == "M") { //MOVETO, 1 point
                        mPath.moveTo(points[pointIndex]);
                        pointIndex++;
                    }
                    else if (types[i] == "L") { //LINETO, 1 point
                        mPath.lineTo(points[pointIndex]);
                        pointIndex++;
                    }
                    else if (types[i] == "Q") { //QUADTO, 2 points
                        mPath.quadTo(points[pointIndex], points[pointIndex + 1]);
                        pointIndex += 2;
                    }
                    else if (types[i] == "C") { //CUBICTO, 3 points
                        mPath.curveTo(points[pointIndex], points[pointIndex + 1], points[pointIndex + 2]);
                        pointIndex += 3;
                    }
                    else if (types[i] == "Z") { //close, 0 points
                        mPath.close();
                    }
                }

            }

        }
        catch( const std::exception &e ) {
            CI_LOG_EXCEPTION( "Exception Loading Poly: ", e );
        }

        //WHEN CINDER PATCHED:
//            vector<string> pieces = split(val," ");
//
//            for (int i=0; i<pieces.size(); ) {
//
//                if (pieces[i] == "M") { //MOVETO, 1 point
//                    vec2 p;
//                    p.x = fromString<int>(pieces[i+1]);
//                    p.y = fromString<int>(pieces[i+2]);
//                    mPath.moveTo(p);
//                    i+=3;
//                }
//                else if (pieces[i] == "L") { //LINETO, 1 point
//                    vec2 p;
//                    p.x = fromString<int>(pieces[i+1]);
//                    p.y = fromString<int>(pieces[i+2]);
//                    mPath.lineTo(p);
//                    i+=3;
//                }
//                else if (pieces[i] == "Q") { //QUADTO, 2 points
//                    vec2 p1;
//                    p1.x = fromString<int>(pieces[i+1]);
//                    p1.y = fromString<int>(pieces[i+2]);
//                    vec2 p2;
//                    p2.x = fromString<int>(pieces[i+3]);
//                    p2.y = fromString<int>(pieces[i+4]);
//                    mPath.quadTo(p1,p2);
//                    i+=5;
//                }
//                else if (pieces[i] == "C") { //CUBICTO, 3 points
//                    vec2 p1;
//                    p1.x = fromString<int>(pieces[i+1]);
//                    p1.y = fromString<int>(pieces[i+2]);
//                    vec2 p2;
//                    p2.x = fromString<int>(pieces[i+3]);
//                    p2.y = fromString<int>(pieces[i+4]);
//                    vec2 p3;
//                    p3.x = fromString<int>(pieces[i+5]);
//                    p3.y = fromString<int>(pieces[i+6]);
//                    mPath.curveTo(p1,p2,p3);
//                    i+=7;
//                }
//                else if (pieces[i] == "Z") { //close, 0 points
//                    mPath.close();
//                    i++;
//                }
//                else {
//                    cerr<<"Poly parsing error."<<pieces[i]<<endl;
//                    i++;
//                }
//            }

    }
    else
    {
        CI_LOG_E("Create: " << mFilename);
    }


    mIsEditable = false;

}

void PolyEditor::registerEvents()
{
    mCbMouseDown = getWindow()->getSignalMouseDown().connect( std::bind( &PolyEditor::mouseDown, this, std::placeholders::_1 ) );
    mCbMouseUp   = getWindow()->getSignalMouseUp().connect(   std::bind( &PolyEditor::mouseUp,   this, std::placeholders::_1 ) );
    mCbMouseDrag = getWindow()->getSignalMouseDrag().connect( std::bind( &PolyEditor::mouseDrag, this, std::placeholders::_1 ) );
    mCbKeyDown   = getWindow()->getSignalKeyDown().connect( std::bind( &PolyEditor::keyDown, this, std::placeholders::_1 ) );
    //todo: register cleanup event
    areEventsRegistered = true;

}

void PolyEditor::unregisterEvents()
{
    if (areEventsRegistered) {
        mCbMouseDown.disconnect();
        mCbMouseUp.disconnect();
        mCbMouseDrag.disconnect();
        mCbKeyDown.disconnect();
        areEventsRegistered = false;
    }

}

void PolyEditor::draw( bool _solid )
{

    if (mIsEditable) {
        // draw the control points
        gl::color( Color( 1, 1, 0 ) );
        for( size_t p = 0; p < mPath.getNumPoints(); ++p )
            gl::drawSolidCircle( mPath.getPoint( p ), 2.5f );

        // draw the curve itself
        gl::color( Color( 1.0f, 0.5f, 0.25f ) );
        gl::draw( mPath );
    }
    else {

        // draw the curve itself
        _solid ? gl::drawSolid( mPath) : gl::draw( mPath );

    }

}


void PolyEditor::toggleEditMode()
{
    mIsEditable = !mIsEditable;
}

void PolyEditor::save()
{

//        mPath.close();
    vec2 lastPt = mPath.getPoint( mPath.getNumPoints()-1);

    stringstream ss;
    //hack for bug in Path2d:
    //ss << "M " << mPath << (int)lastPt.x << " " << (int) lastPt.y;
    //when cinder patched:
    ss << mPath;
    CI_LOG_V("Saving poly: "<<ss.str());

    xml = XmlTree("polys","");
    XmlTree polyXml = XmlTree("poly",ss.str());

    xml.push_back(polyXml);

    xml.write( writeFile( getAssetPath( mFilename ) ) );

}

void PolyEditor::mouseDown( MouseEvent event )
{
    if (!mIsEditable) return;

    lastMouseDown = event;

    if( event.isLeftDown() ) { // line
        if( mPath.empty() ) {
            mPath.moveTo( event.getPos() );
            mTrackedPoint = 0;
        }
        else
            mPath.lineTo( event.getPos() );
    }
}

void PolyEditor::mouseDrag( MouseEvent event )
{
    if (!mIsEditable) return;

    if( mTrackedPoint >= 0 ) {
        mPath.setPoint( mTrackedPoint, event.getPos() );
    }
    else { // first bit of dragging, so switch our line to a cubic or a quad if Shift is down
        // we want to preserve the end of our current line, because it will still be the end of our curve
        vec2 endPt = mPath.getPoint( mPath.getNumPoints() - 1 );
        // and now we'll delete that line and replace it with a curve
        mPath.removeSegment( mPath.getNumSegments() - 1 );

        Path2d::SegmentType prevType = ( mPath.getNumSegments() == 0 ) ? Path2d::MOVETO : mPath.getSegmentType( mPath.getNumSegments() - 1 );

        if( event.isShiftDown() || prevType == Path2d::MOVETO ) { // add a quadratic curve segment
            mPath.quadTo( event.getPos(), endPt );
        }
        else { // add a cubic curve segment
            vec2 tan1;
            if( prevType == Path2d::CUBICTO ) { 		// if the segment before was cubic, let's replicate and reverse its tangent
                vec2 prevDelta = mPath.getPoint( mPath.getNumPoints() - 2 ) - mPath.getPoint( mPath.getNumPoints() - 1 );
                tan1 = mPath.getPoint( mPath.getNumPoints() - 1 ) - prevDelta;
            }
            else if( prevType == Path2d::QUADTO ) {
                // we can figure out what the equivalent cubic tangent would be using a little math
                vec2 quadTangent = mPath.getPoint( mPath.getNumPoints() - 2 );
                vec2 quadEnd = mPath.getPoint( mPath.getNumPoints() - 1 );
                vec2 prevDelta = ( quadTangent + ( quadEnd - quadTangent ) / 3.0f ) - quadEnd;
                tan1 = quadEnd - prevDelta;
            }
            else
                tan1 = mPath.getPoint( mPath.getNumPoints() - 1 );

            mPath.curveTo( tan1, event.getPos(), endPt );
        }

        // our second-to-last point is the tangent next to the end, and we'll track that
        mTrackedPoint = mPath.getNumPoints() - 2;
    }
}

void PolyEditor::mouseUp( MouseEvent event )
{

    if (!mIsEditable) return;

    mTrackedPoint = -1;
}

//todo: update so works for non-straight lines too
void PolyEditor::keyDown( KeyEvent event )
{
    if (!mIsEditable || mPath.empty()) return;

    MouseEvent fakeEvent = lastMouseDown;
    ivec2 lastPos = lastMouseDown.getPos();


    switch( event.getCode() ) {
        case KeyEvent::KEY_UP:
            clearLast();
            lastPos.y--;
            fakeEvent.setPos(lastPos);
            mouseDown( fakeEvent );
            mouseUp( fakeEvent );
            break;
        case KeyEvent::KEY_DOWN:
            clearLast();
            lastPos.y++;
            fakeEvent.setPos(lastPos);
            mouseDown( fakeEvent );
            mouseUp( fakeEvent );
            break;
        case KeyEvent::KEY_LEFT:
            clearLast();
            lastPos.x--;
            fakeEvent.setPos(lastPos);
            mouseDown( fakeEvent );
            mouseUp( fakeEvent );
            break;
        case KeyEvent::KEY_RIGHT:
            clearLast();
            lastPos.x++;
            fakeEvent.setPos(lastPos);
            mouseDown( fakeEvent );
            mouseUp( fakeEvent );
            break;
    }
}

void PolyEditor::cleanup()
{
    if (areEventsRegistered) unregisterEvents();
}



}//namespace coc