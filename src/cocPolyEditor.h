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
 *
 * Simple class to edit and load/save single poly to xml file
 * based on Cinder bezierPath sample
 */

#pragma once

#include "cinder/app/App.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include "cinder/Xml.h"

namespace coc {

class PolyEditor {
public:

    void setup( std::string _filename = "config_poly.xml" );
    void draw( bool _solid = false);
    void save();

    void toggleEditMode();
    bool getIsEditable() { return mIsEditable; };
    void setIsEditable( bool _b ) { mIsEditable = _b; }

    void close() { mPath.close(); };
    void clear() { mPath.clear(); };
    void clearLast() {
        if (mPath.getNumSegments()>0) mPath.removeSegment( mPath.getNumSegments()-1 );
    }
    void cleanup();

    ci::Rectf   getBounds() { return mPath.calcBoundingBox(); }
    ci::Path2d  getPath() { return mPath; }

    void registerEvents();
    void unregisterEvents();

    void mouseDown( ci::app::MouseEvent event );
    void mouseDrag( ci::app::MouseEvent event );
    void mouseUp( ci::app::MouseEvent event );
    void keyDown( ci::app::KeyEvent event );

private:
    bool areEventsRegistered = false;

    ci::signals::ScopedConnection	mCbMouseDown, mCbMouseDrag, mCbMouseUp, mCbKeyDown;

    std::string         mFilename;
    ci::Path2d  	    mPath;
    int		            mTrackedPoint;
    bool                mIsEditable;
    ci::XmlTree         xml;

    ci::app::MouseEvent	lastMouseDown;//for key events


};//class PolyEditor

}//namespace coc