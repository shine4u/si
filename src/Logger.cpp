#include "Logger.h"


namespace si {

const int FATAL = 1;
const int WARN  = 2;
const int NOTICE = 4;
const int DEBUG  = 8;
const int LOG_ALL = FATAL|WARN|NOTICE|DEBUG;
int LOG_LEVEL = 7;

const string SET_TIME_STR_NOW(void) {    
    time_t v1 = time(NULL);
    struct tm *v2 = localtime(&v1);
    if(!v2)
        return "unknown";

    char tmpstr[64];
    if(strftime(tmpstr, 64, "%m-%d %H:%M:%S", v2) == 0)
        return "unknown";
    return string(tmpstr);
}

void set_log_level(int mask) {
    if (IN_RANGE(mask, 0, si::LOG_ALL+1)) {
        LOG_LEVEL = mask;
    }
}

}
