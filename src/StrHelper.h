#ifndef _STR_HELPER_H_
#define _STR_HELPER_H_

#include "Logger.h"

namespace si {
class StrHelper {
public:
        static bool contains(const string &str, const string &sub);
        static bool next_gbk(const string &str, unsigned char &low, unsigned char &high);
        static void reverse(string &str);
    static string join(const vector<string> &tokens, const char sep='\t');
};
}
#endif // _STR_HELPER_H_
