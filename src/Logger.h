#ifndef _SI_LOGGER_H_
#define _SI_LOGGER_H_

#include "BasicDefs.h"

namespace si {

extern const int FATAL;
extern const int WARN;
extern const int NOTICE;
extern const int DEBUG;

extern const int LOG_ALL;
extern int LOG_LEVEL;

// public functions.
void set_log_level(int mask);

// private functions.
const string SET_TIME_STR_NOW(void);

}
#define SI_NOTICE(fmt, ...) SI_LOG(si::NOTICE, "*** NOTICE", fmt, ##__VA_ARGS__)
#define SI_WARN(fmt, ...)   SI_LOG(si::WARN,   "*** WARN  ", fmt, ##__VA_ARGS__)
#define SI_DEBUG(fmt, ...)  SI_LOG(si::DEBUG,  "*** DEBUG ", fmt, ##__VA_ARGS__)
#define SI_FATAL(fmt, ...)  \
    do { \
        SI_LOG(si::FATAL, "*** FATAL ", fmt, ##__VA_ARGS__); \
        exit(1); \
    } while(0)

#define SI_LOG(level, level_name, fmt, ...) \
    do { \
        if (si::LOG_LEVEL&level) { \
            const string timestr = si::SET_TIME_STR_NOW(); \
            fprintf(stderr, "%s %6s %s:%d ", STR(timestr), \
                    level_name, __FILE__, __LINE__); \
            fprintf(stderr, fmt, ##__VA_ARGS__); \
            fprintf(stderr, "\n"); \
        } \
    } while(0)

#define PASS_OR_EXIT(expression_, fmt_, ...) \
    do { \
        if (!(expression_)) { \
            SI_FATAL(fmt_, ##__VA_ARGS__); \
        } \
    } while(0)

#define PASS_OR_FAIL(expression_, fmt_, ...) \
    do { \
        if (!(expression_)) { \
            SI_WARN(fmt_, ##__VA_ARGS__); \
            return 0; \
        } \
    } while(0)

#define SI_RET_DEBUG(retval, fmt_, ...) \
    do { \
        SI_DEBUG(fmt_, ##__VA_ARGS__); \
        return retval; \
    } while(0)

#endif // _si::Logger_H_
