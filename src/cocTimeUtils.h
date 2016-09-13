#pragma once

#ifdef COC_CI

#include "cinder/app/App.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

namespace coc {

//format flags:
//http://www.boost.org/doc/libs/1_35_0/doc/html/date_time/date_time_io.html#date%5Ftime.format%5Fflags

static std::string formatPosixDateTime( boost::posix_time::ptime &p, std::string fmt )
{

    boost::posix_time::time_facet* facet( new boost::posix_time::time_facet(fmt.c_str()) );
    std::stringstream ss;
    ss.imbue( std::locale( std::locale::classic(), facet ) );
    ss << p;

    return ss.str();
}


//todo: trim string from start not end, or start with iso extended format and remove 'T'?
//http://www.boost.org/doc/libs/1_43_0/doc/html/date_time/date_time_io.html

static std::string formatIsoDateTime( const std::string& iso, const std::string& fmt )
{
    //parse iso for boost
    std::string strIso = std::string(iso,0,iso.length()-6);
    std::string strIsoBoost ="";
    for (int i=0; i<strIso.length(); i++) {
        if (strIso[i] != '-' && strIso[i] != ':') strIsoBoost += strIso[i];
    }
    boost::posix_time::ptime p = boost::posix_time::from_iso_string( strIsoBoost );

    //format with boost
    boost::posix_time::time_facet* facet( new boost::posix_time::time_facet(fmt.c_str()) );
    std::stringstream ss;
    ss.imbue( std::locale( std::locale::classic(), facet ) );
    ss << p;
    return ss.str();

//            return formatPosixDateTime( p, fmt );

}


static boost::posix_time::ptime isoStringToPosixTime( const std::string& iso ) {
    //parse iso for boost
    std::string strIso = std::string(iso,0,iso.length()-6);
    std::string strIsoBoost ="";
    for (int i=0; i<strIso.length(); i++) {
        if (strIso[i] != '-' && strIso[i] != ':') strIsoBoost += strIso[i];
    }
    boost::posix_time::ptime p = boost::posix_time::from_iso_string( strIsoBoost );

    return p;
}

static boost::posix_time::time_duration getTimeDuration( boost::posix_time::ptime _start, boost::posix_time::ptime _end ) {
    boost::posix_time::time_duration t = _end - _start;
    return t;
}

}//namespace coc

#endif // COC_CI