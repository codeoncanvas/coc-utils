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

#include "cocParameters.h"


namespace coc {

using namespace std;

Parameters::Parameters() : bVerbose(false) {}
Parameters* Parameters::pInst = nullptr;
Parameters* Parameters::instance()
{
	if(pInst == nullptr) {
		pInst = new Parameters();
	}
	return pInst;
}


void Parameters::save( std::string _filename )
{

	ci::XmlTree xml("parameters","");
	for (int i=0; i<params.size(); i++) {

		ci::XmlTree p( "parameter", "" );
		p.setAttribute( "name", params[i].name );
		p.setAttribute( "type", (int) params[i].type );

		switch (params[i].type) {
			case PARAM_FLOAT:
				p.setAttribute( "val", *(float*) params[i].val );
				break;
			case PARAM_INT:
				p.setAttribute( "val", *(int*) params[i].val );
				break;
			case PARAM_BOOL:
				p.setAttribute( "val", (int) *(bool*) params[i].val );
				break;
			case PARAM_STR:
				p.setAttribute( "val", *(string*) params[i].val );
				break;
			case PARAM_VEC2:
				p.setAttribute( "x", (*(glm::vec2*) params[i].val).x );
				p.setAttribute( "y", (*(glm::vec2*) params[i].val).y );
				break;
            case PARAM_COL3:
                p.setAttribute( "r", (*(ci::Color*) params[i].val).r );
                p.setAttribute( "g", (*(ci::Color*) params[i].val).g );
                p.setAttribute( "b", (*(ci::Color*) params[i].val).b );
                break;
            case PARAM_COL4:
                p.setAttribute( "r", (*(ci::ColorA*) params[i].val).r );
                p.setAttribute( "g", (*(ci::ColorA*) params[i].val).g );
                p.setAttribute( "b", (*(ci::ColorA*) params[i].val).b );
                p.setAttribute( "a", (*(ci::ColorA*) params[i].val).a );
                break;
			case PARAM_RECT:
				p.setAttribute( "x1", (*(ci::Rectf*) params[i].val).x1 );
				p.setAttribute( "y1", (*(ci::Rectf*) params[i].val).y1 );
				p.setAttribute( "x2", (*(ci::Rectf*) params[i].val).x2 );
				p.setAttribute( "y2", (*(ci::Rectf*) params[i].val).y2 );
				break;
		}

		xml.push_back( p );
	}


	#ifndef CINDER_LINUX_EGL_RPI2

	xml.write( ci::writeFile( ci::app::getAssetPath( _filename ) ) );

	#else
	//temp workaround for xml bug
	string filePath = ci::app::getAssetPath( _filename ).generic_string();
	ofstream tmp(filePath);
	if (tmp.is_open())
	{
		tmp << xml;
		tmp.close();
	}
	else {
		CI_LOG_E("Failed to save file");
	}

	#endif

    if(bVerbose) {
        CI_LOG_I( "Saved GUI: " <<  params.size() << " parameters");
    }
}

void Parameters::load( std::string _filename )
{

	ci::XmlTree xml;
	try {
		xml = ci::XmlTree( ci::app::loadAsset( _filename ) );
	}
	catch( ci::Exception exc ){
		CI_LOG_EXCEPTION( "Loading XML failed, creating file", exc )
		std::ofstream file( (ci::app::getAssetPath("") / _filename).string() );
		file.close();
	}


	for( auto parameter = xml.begin( "parameters/parameter" ); parameter != xml.end(); parameter ++ ) {

		std::string 	name = parameter->getAttributeValue<std::string>("name","");
		parameterType 	type = (parameterType) parameter->getAttributeValue<int>( "type", 0 );

		for (int i=0; i<params.size(); i++) {

			if ( name == params[i].name ) {

				if (type != params[i].type) CI_LOG_E( name << " types do not match!");

				switch ( type ) {
					case PARAM_FLOAT:
						*(float *) params[i].val = parameter->getAttributeValue<float>( "val", 0.0f );
						break;
					case PARAM_INT:
						*(int *) params[i].val = parameter->getAttributeValue<int>( "val", 0.0f );
						break;
					case PARAM_BOOL:
						*(bool *) params[i].val = (bool) parameter->getAttributeValue<int>( "val", 0 );
						break;
					case PARAM_STR:
						*(string *) params[i].val = parameter->getAttributeValue<string>( "val", "" );
						break;
					case PARAM_VEC2:
						(*(glm::vec2 *) params[i].val).x = parameter->getAttributeValue<float>( "x", 0 );
						(*(glm::vec2 *) params[i].val).y = parameter->getAttributeValue<float>( "y", 0 );
						break;
                    case PARAM_COL3:
                        (*(ci::Color *) params[i].val).r = parameter->getAttributeValue<float>( "r", 0 );
                        (*(ci::Color *) params[i].val).g = parameter->getAttributeValue<float>( "g", 0 );
                        (*(ci::Color *) params[i].val).b = parameter->getAttributeValue<float>( "b", 0 );
                        break;
                    case PARAM_COL4:
                        (*(ci::ColorA *) params[i].val).r = parameter->getAttributeValue<float>( "r", 0 );
                        (*(ci::ColorA *) params[i].val).g = parameter->getAttributeValue<float>( "g", 0 );
                        (*(ci::ColorA *) params[i].val).b = parameter->getAttributeValue<float>( "b", 0 );
                        (*(ci::ColorA *) params[i].val).a = parameter->getAttributeValue<float>( "a", 0 );
                        break;
					case PARAM_RECT:
						(*(ci::Rectf *) params[i].val).x1 = parameter->getAttributeValue<float>( "x1", 0 );
						(*(ci::Rectf *) params[i].val).y1 = parameter->getAttributeValue<float>( "y1", 0 );
						(*(ci::Rectf *) params[i].val).x2 = parameter->getAttributeValue<float>( "x2", 0 );
						(*(ci::Rectf *) params[i].val).y2 = parameter->getAttributeValue<float>( "y2", 0 );
						break;
				}

			}
		}
	}
    
    if(bVerbose) {
        CI_LOG_I( "Loaded GUI: " <<  params.size() << " parameters");
    }
}

}//namespace coc
