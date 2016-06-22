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

/*
 * Thanks to Paul Houx: https://forum.libcinder.org/topic/hex-color
 * And @nselikoff :https://github.com/cinder/Cinder/pull/374/files
 */

#pragma once

#ifdef COC_CI

#include "cinder/Color.h"
#include <sstream>

namespace coc {

namespace Color {


static ci::Color hex( const std::string &hexValueString )
{
	std::stringstream converter( hexValueString );
	uint32_t hexValue;
	converter >> std::hex >> hexValue;

	return ci::Color::hex( hexValue );
}


}//namespace Color

}//namespace coc

#endif
