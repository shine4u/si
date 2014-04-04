#ifndef _BASIC_DEFS_H_
#define _BASIC_DEFS_H_

#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <cassert>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

using std::max;
using std::min;
using std::vector;
using std::string;
using std::stringstream;
using std::ostringstream;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::map;
using std::set;
using std::istringstream;
using std::make_pair;
using std::pair;

// 一些为了代码简化的定义，多以STL为主
#define SIZE(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define STR(x) (x).c_str()
#define IN_RANGE(x, a, b) ((a)<=(x)&&(x)<(b))

#define REP(i, n) for(int i = 0; i < (n); ++ i)
#define FOREACH(x, cont) for(__typeof((cont).begin()) x=(cont).begin(); x!=(cont).end(); ++x)

// ASSERT
#define ASSERT(x) assert(x)

// 类型转换函数，此函数效率不高，注意使用场景
// 推荐使用typecvtor
template <typename S, typename T>
S inline convert(const T &t) { stringstream ss; S s; ss << t; ss >>  s; return s; }

#endif // _BASIC_DEFS_H_
