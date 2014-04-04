#include "StrHelper.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
namespace si {

bool StrHelper::contains(const string &str, const string &sub) {
        return str.find(sub) != string::npos;
}
void StrHelper::reverse(string &str) {
        int len = SIZE(str);
        REP(x, len/2)
                std::swap(str[x], str[len-1-x]);
}
string StrHelper::join(const vector<string> &tokens, const char sep) {
    string res;
    for (int i = 0; i < SIZE(tokens); ++ i) {
        if (i != 0)
            res += sep;
        res += tokens[i];
    }
    return res;
}
bool StrHelper::next_gbk(const string &str, unsigned char &low, unsigned char &high) {
        static string _cur_s = "";
        static int _next_pos = 0;
        if(str != _cur_s) {
                _cur_s = str;
                _next_pos = 0;
        }

        if (SIZE(str) <= _next_pos)
                return false;

        unsigned char mask = *(unsigned char*)(&str[_next_pos]);
        if(!(0x81 <= mask && mask <= 0xfe)) {
                high = '\0';
                low = mask;
                _next_pos ++;
                return true;
        } else {
                low = mask;
                mask = *(unsigned char*)(&str[_next_pos+1]);
                if(mask == '\0')
                        return false;
                high = mask;
                _next_pos += 2;
                return true;
        }
}
} // end of namespace si
