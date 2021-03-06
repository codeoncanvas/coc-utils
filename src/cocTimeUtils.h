#pragma once

#ifdef COC_CI

#include "cinder/app/App.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

namespace coc {

//boost format flags:
//http://www.boost.org/doc/libs/1_35_0/doc/html/date_time/date_time_io.html#date%5Ftime.format%5Fflags
//windows only supports a subset in VC2013::
//https://msdn.microsoft.com/en-us/library/fe06s4ak(v=vs.100).aspx

	static std::string formatPosixDateTime(boost::posix_time::ptime &p, std::string fmt, int hourOffset = 0)
{
	if (hourOffset) p += boost::posix_time::hours(hourOffset);
    boost::posix_time::time_facet* facet( new boost::posix_time::time_facet(fmt.c_str()) );
    std::stringstream ss;
    ss.imbue( std::locale( std::locale::classic(), facet ) );
    ss << p;

    return ss.str();
}

static std::string formatStringForBoostIso( std::string &strIso ) {
	std::string strIsoBoost ="";
	for (int i=0; i<strIso.length(); i++) {
		if (strIso[i] == ' ') {
			strIsoBoost += 'T';
		}
		else if (strIso[i] != '-' && strIso[i] != ':') {
			strIsoBoost += strIso[i];
		}
	}
	return strIsoBoost;
}

//http://www.boost.org/doc/libs/1_43_0/doc/html/date_time/date_time_io.html
static std::string formatIsoDateTime( const std::string& iso, const std::string& fmt, int hourOffset = 0, bool trimTimezone = false )
{
    //parse iso for boost, very picky
    std::string strIso;
    if (trimTimezone) { //todo: revisit, should prob trim from start if at all
        strIso = std::string(iso,0,iso.length()-6);
    }
    else {
        strIso = iso;
    }
    std::string strIsoBoost = formatStringForBoostIso(strIso);

    //format with boost
    boost::posix_time::ptime p = boost::posix_time::from_iso_string( strIsoBoost );
	if (hourOffset) p += boost::posix_time::hours(hourOffset);
    boost::posix_time::time_facet* facet( new boost::posix_time::time_facet(fmt.c_str()) );
    std::stringstream ss;
    ss.imbue( std::locale( std::locale::classic(), facet ) );
    ss << p;
    return ss.str();

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