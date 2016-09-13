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
 *
 * 	USAGE:
 *
 * 	coc::parameters()->registerParam("variableName",&variable);
 * 	coc::parameters()->load();
 * 	...
 * 	coc::parameters()->save();
 *
 */

#pragma once

#include "cinder/app/App.h"
#include "cinder/Xml.h"
#include "cinder/Log.h"
#include <fstream>

namespace coc {

enum parameterType {
	PARAM_FLOAT = 0,
	PARAM_INT = 1,
	PARAM_BOOL = 2,
	PARAM_STR = 3,
	PARAM_VEC2 = 10,
    PARAM_COL3 = 20,
    PARAM_COL4 = 21,
	PARAM_RECT = 30
};

struct Parameter {

	std::string 	name;
	parameterType 	type;
	void*			val;

};

class Parameters {
public:

    Parameters();

	template<typename T>
	void registerParam( std::string _name, T *_val )
	{
		params.push_back(Parameter());
		params.back().name = _name;
		params.back().val = _val;
		if (std::is_same<T, float>::value) params.back().type = PARAM_FLOAT;
		else if (std::is_same<T, int>::value) params.back().type = PARAM_INT;
		else if (std::is_same<T, bool>::value) params.back().type = PARAM_BOOL;
		else if (std::is_same<T, std::string>::value) params.back().type = PARAM_STR;
		else if (std::is_same<T, glm::vec2>::value) params.back().type = PARAM_VEC2;
        else if (std::is_same<T, ci::Color>::value) params.back().type = PARAM_COL3;
        else if (std::is_same<T, ci::ColorA>::value) params.back().type = PARAM_COL4;
		else if (std::is_same<T, ci::Rectf>::value) params.back().type = PARAM_RECT;
	}

	void save( std::string _filename = "config_params.xml" );
	void load( std::string _filename = "config_params.xml" );

    void setVerbose(bool value) { bVerbose = value; }

	static Parameters* instance();

private:

	static Parameters* pInst;

	std::vector<coc::Parameter> params;
    
    bool bVerbose;
};

static Parameters* parameters() { return Parameters::instance(); }


}//namespace coc
