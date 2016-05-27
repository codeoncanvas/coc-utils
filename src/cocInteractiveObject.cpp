#include "cocInteractiveObject.h"

namespace coc
{

    void InteractiveObject::enableAllEvents()
    {
        enableMouseEvents();
        enableKeyEvents();
#ifdef CINDER_COCOA_TOUCH
        enableTouchEvents();
#endif
    }

    void InteractiveObject::disableAllEvents()
    {
        disableMouseEvents();
        disableKeyEvents();
#ifdef CINDER_COCOA_TOUCH
        disableTouchEvents();
#endif

    }

    void InteractiveObject::enableMouseEvents()
    {
        mousePos = vec2(0,0);
        cbMouseDown = getWindow()->getSignalMouseDown().connect( std::bind( &InteractiveObject::_mouseDown, this, std::placeholders::_1 ) );
        cbMouseDrag = getWindow()->getSignalMouseDrag().connect( std::bind( &InteractiveObject::_mouseDrag, this, std::placeholders::_1 ) );
        cbMouseUp = getWindow()->getSignalMouseUp().connect( std::bind( &InteractiveObject::_mouseUp, this, std::placeholders::_1 ) );
        cbMouseMove = getWindow()->getSignalMouseMove().connect( std::bind( &InteractiveObject::_mouseMove, this, std::placeholders::_1 ) );
	}

    void InteractiveObject::disableMouseEvents()
    {
        cbMouseDown.disconnect();
        cbMouseDrag.disconnect();
        cbMouseUp.disconnect();
        cbMouseMove.disconnect();
    }
#ifdef CINDER_COCOA_TOUCH
    void InteractiveObject::enableTouchEvents()
    {
        cbTouchesBegan = getWindow()->getSignalTouchesBegan().connect( std::bind( &InteractiveObject::_touchesBegan, this, std::placeholders::_1 ) );
        cbTouchesMoved = getWindow()->getSignalTouchesMoved().connect( std::bind( &InteractiveObject::_touchesMoved, this, std::placeholders::_1 ) );
        cbTouchesEnded = getWindow()->getSignalTouchesEnded().connect( std::bind( &InteractiveObject::_touchesEnded, this, std::placeholders::_1 ) );

    }

    void InteractiveObject::disableTouchEvents()
    {
        cbTouchesBegan.disconnect();
        cbTouchesMoved.disconnect();
        cbTouchesEnded.disconnect();
    }
#endif

    vec2 InteractiveObject::getMousePos() { return mousePos; }

    void InteractiveObject::enableKeyEvents()
    {
        cbKeyDown = getWindow()->getSignalKeyDown().connect( std::bind( &InteractiveObject::_keyDown, this, std::placeholders::_1 ) );
#ifndef CINDER_COCOA_TOUCH
        cbKeyUp = getWindow()->getSignalKeyUp().connect( std::bind( &InteractiveObject::_keyUp, this, std::placeholders::_1 ) );
#endif
    }

    void InteractiveObject::disableKeyEvents()
    {
        cbKeyDown.disconnect();
#ifndef CINDER_COCOA_TOUCH
        cbKeyUp.disconnect();
#endif
    }

#ifdef CINDER_COCOA_TOUCH

    void InteractiveObject::_touchesBegan( TouchEvent event )
    {
        touchesBegan(event);
    }

    void InteractiveObject::_touchesMoved( TouchEvent event )
    {
        touchesMoved(event);
    }

    void InteractiveObject::_touchesEnded( TouchEvent event )
    {
        touchesEnded(event);
    }

#endif

    void InteractiveObject::_mouseDown( MouseEvent event )
    {
        mouseDown(event);
    }

    void InteractiveObject::_mouseDrag( MouseEvent event )
    {
        mouseDrag(event);
    }

    void InteractiveObject::_mouseUp( MouseEvent event )
    {
        mouseUp(event);
    }

    void InteractiveObject::_mouseMove( MouseEvent event )
    {
        mousePos = event.getPos();
        mouseMove(event);
    }

    void InteractiveObject::_keyDown( KeyEvent event )
    {
        keyDown(event);
    }

    void InteractiveObject::_keyUp( KeyEvent event )
    {
        keyUp(event);
    }

};//namespace coc