#ifndef _TYPE_CVTOR_H_
#define _TYPE_CVTOR_H_

#include "BasicDefs.h"
#include "StrHelper.h"
namespace si {

class TypeCvtor {
public:
        static bool as_string(int from, string &to);
        static bool as_string(int64_t from, string &to);
        static bool as_string(double from, string &to, int retain = 2);

        static bool as_int(const string &from, int &to, bool full_match = true);
        static bool as_int64(const string &from, int64_t &to, bool full_match = true);
};

}
#endif // _TYPE_CVTOR_H_
