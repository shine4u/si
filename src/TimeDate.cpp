#include "TimeDate.h"
#include "TypeCvtor.h"
#include  <boost/algorithm/string.hpp>

using namespace boost::posix_time;
using namespace boost::gregorian;

namespace si {
bool TimeDate::set(const string &time) {
        vector<string> tokens;
        boost::split(tokens, time, boost::is_any_of(" \t:-"), boost::token_compress_on);
        PASS_OR_FAIL(SIZE(tokens) == 6, "bad time [%s]", time.c_str());

        int year, month, day, hour, minute, sec;
        bool flag = true;
        flag = flag && TypeCvtor::as_int(tokens[0], year);
        flag = flag && TypeCvtor::as_int(tokens[1], month);
        flag = flag && TypeCvtor::as_int(tokens[2], day);
        flag = flag && TypeCvtor::as_int(tokens[3], hour);
        flag = flag && TypeCvtor::as_int(tokens[4], minute);
        flag = flag && TypeCvtor::as_int(tokens[5], sec);
        PASS_OR_FAIL(flag, "bad time [%s]", time.c_str());

        time_ = ptime(date(year, month, day), time_duration(hour, minute, sec));
        return true;
}

bool TimeDate::set_now() {
        time_ = ptime(second_clock::local_time());
        return true;
}
int TimeDate::diff_secs(TimeDate &from) {
        time_period tp = time_period(from.time_, time_);
        time_duration td = tp.length();
        return td.total_seconds();
}
string TimeDate::show() {
        date d = time_.date();
        time_duration td = time_.time_of_day(); 
        return to_simple_string(d) + " " + to_simple_string(td);
}
}
