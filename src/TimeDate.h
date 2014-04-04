#ifndef _SI_TIME_DATE_H_
#define _SI_TIME_DATE_H_

#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "BasicDefs.h"
#include "Logger.h"


namespace si {
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
class TimeDate {
public:
        bool set(const string &time); //  2008-03-25 15:19:52
        bool set_now();
        int diff_secs(TimeDate &from);
        string show();
public:
        ptime time_;
};

}
#endif // _SI_TIME_DATE_H_
