#pragma once


/*
#if(CINDER_VERSION >= 900)
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#else
#include "cinder/app/AppNative.h"
#endif
*/
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

namespace coc
{
    using namespace ci;
    using namespace ci::app;
    using namespace std;

    class InteractiveObject
    {
    public:

        void setBounds( Rectf _bounds ) { bounds = _bounds; }
        Rectf getBounds() { return bounds; }

        void enableAllEvents();
        void disableAllEvents();

        void enableMouseEvents();
        void disableMouseEvents();

        void enableTouchEvents();
        void disableTouchEvents();

        void enableKeyEvents();
        void disableKeyEvents();

        virtual void mouseDown( MouseEvent event ) {};
        virtual void mouseDrag( MouseEvent event ) {};
        virtual void mouseUp( MouseEvent event ) {};
        virtual void mouseMove( MouseEvent event ) {};

        vec2 getMousePos();

        #ifdef CINDER_COCOA_TOUCH

        virtual void touchesBegan( TouchEvent event ) {};
        virtual void touchesMoved( TouchEvent event ) {};
        virtual void touchesEnded( TouchEvent event ) {};

        #endif

        virtual void keyDown( KeyEvent event ) {};
        virtual void keyUp( KeyEvent event ) {};

    private:

        Rectf bounds;

        ci::signals::ScopedConnection  cbTouchesBegan, cbTouchesMoved, cbTouchesEnded;
        ci::signals::ScopedConnection  cbMouseDown, cbMouseDrag, cbMouseUp, cbMouseMove;
        ci::signals::ScopedConnection  cbKeyDown, cbKeyUp;

        void _mouseDown( MouseEvent event );
        void _mouseDrag( MouseEvent event );
        void _mouseUp( MouseEvent event );
        void _mouseMove( MouseEvent event );

        vec2    mousePos;

        #ifdef CINDER_COCOA_TOUCH

        void _touchesBegan( TouchEvent event );
        void _touchesMoved( TouchEvent event );
        void _touchesEnded( TouchEvent event );

        #endif

        void _keyDown( KeyEvent event );
        void _keyUp( KeyEvent event );


    };//class InteractiveObject

}//namespace coc