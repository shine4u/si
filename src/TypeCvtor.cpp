#include "TypeCvtor.h"

namespace si {

bool TypeCvtor::as_string(int from, string &to) {
        to.clear();
        if (from == 0) {
                to.append(1, '0');
                return true;
        }
        bool is_neg = (from < 0);
        if (from < 0)
                from = -from;
        while (from != 0) {
                to.append(1, from % 10 + '0');
                from /= 10;
        }
        if (is_neg)
                to.append(1, '-');
        StrHelper::reverse(to);
        return true;
}
bool TypeCvtor::as_string(int64_t from, string &to) {
        to.clear();
        if (from == 0) {
                to.append(1, '0');
                return true;
        }

        bool is_neg = (from < 0);
        if (from < 0)
                from = -from;
        while (from != 0) {
                to.append(1, from % 10 + '0');
                from /= 10;
        }
        if (is_neg)
                to.append(1, '-');
        StrHelper::reverse(to);
         return true;
}
bool TypeCvtor::as_string(double from, string &to, int retain) {
        static char buffer[1024];
        static char fmt[1024];
        sprintf(fmt, "%%.%dlf", retain);
        sprintf(buffer, fmt, from);
        to.assign(buffer);
        return true;
}

bool TypeCvtor::as_int(const string &from, int &to, bool full_match) {
        int neg = 0, dig_pos = 0; // neg: -1 or 1 dig_pos 0, or 1
        int len = SIZE(from);
#define LOCAL_FAIL \
        do { \
                SI_WARN("TypeCvtor::as_int bad [%s]", from.c_str()); \
                return false; \
        } while(0)
        if ( len == 0)
                LOCAL_FAIL;
        else if (from[0] == '-') {
                if (len == 1)
                        LOCAL_FAIL;
                else if (!isdigit(from[1]))
                        LOCAL_FAIL;
                else {
                        neg = -1;
                        dig_pos = 1;
                }
        } else if (!isdigit(from[0])) 
                LOCAL_FAIL;
        else {
                neg = 1;
                dig_pos = 0;
        }
        to = 0;
        for (int x = dig_pos; x < len; ++ x) {
                if (!isdigit(from[x])) {
                        if (full_match)
                                LOCAL_FAIL;
                        else
                                break;
                } else {
                        to = to * 10 + from[x] - '0';
                        if (to < 0) {
                                SI_WARN("TypeCvtor::as_int bad [%s] overflow", from.c_str());
                                return false;
                        }
                }
        }
        to *= neg;
        return true;
}

bool TypeCvtor::as_int64(const string &from, int64_t &to, bool full_match) {
    int neg = 0, dig_pos = 0; // neg: -1 or 1 dig_pos 0, or 1
    int len = SIZE(from);
#undef LOCAL_FAIL
#define LOCAL_FAIL \
    do { \
            SI_WARN("TypeCvtor::as_int64 bad [%s]", from.c_str()); \
            return false; \
        } while(0)
    if ( len == 0)
            LOCAL_FAIL;
    else if (from[0] == '-') {
        if (len == 1)
            LOCAL_FAIL;
        else if (!isdigit(from[1]))
            LOCAL_FAIL;
        else {
            neg = -1;
                dig_pos = 1;
        }
    } else if (!isdigit(from[0])) 
        LOCAL_FAIL;
    else {
        neg = 1;
        dig_pos = 0;
        }
    to = 0;
    for (int x = dig_pos; x < len; ++ x) {
        if (!isdigit(from[x])) {
            if (full_match)
                LOCAL_FAIL;
            else
                break;
        } else {
            to = to * 10 + from[x] - '0';
                if (to < 0) {
                                SI_WARN("TypeCvtor::as_int bad [%s] overflow", from.c_str());
                                return false;           
                        }
        }
    }
        to *= neg;
    return true;
}

}
