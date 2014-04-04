#ifndef _CONFIGER_H_
#define _CONFIGER_H_

/*
 * author: wangbangxu
 * date: 2013-08-30
 */

#include "Logger.h"
#include "libxml/tree.h"
#include "libxml/parser.h"
#include "libxml/xpath.h"
#include "libxml/xpathInternals.h"

namespace si {

class Configer {
public:
        ~Configer();
        bool load(const string &cfg_path);
        bool get(const string &xpath, string &value);
        bool get(const string &xpath, vector<string> &values);
private:
        xmlDocPtr doc_;
        xmlXPathContextPtr xpath_context_;
        xmlXPathObjectPtr xpath_obj_;
        xmlNodeSetPtr nodeset_;
};
}
#endif // _CONFIGER_H_
