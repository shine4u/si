#include "Configer.h"

namespace si {

bool Configer::load(const string &cfg_path)
{
        PASS_OR_FAIL(doc_ = xmlParseFile(cfg_path.c_str()), "null pointer.");
        PASS_OR_FAIL(xpath_context_ = xmlXPathNewContext(doc_), "null pointer.");
        SI_NOTICE("cfg load success! path[%s]", cfg_path.c_str());
        return true;
}
bool Configer::get(const string &xpath, string &value)
{
        PASS_OR_FAIL(xpath_context_, "null pointer.");
        PASS_OR_FAIL(xpath_obj_=xmlXPathEvalExpression(BAD_CAST xpath.c_str(), xpath_context_),
                        "null xpath path[%s].", xpath.c_str());
        nodeset_ = xpath_obj_->nodesetval;
        PASS_OR_FAIL(!xmlXPathNodeSetIsEmpty(nodeset_), "empty nodeset.");
        PASS_OR_FAIL(nodeset_->nodeNr == 1, "nodeset size not 1, path[%s].", xpath.c_str());

        char *xml_str_ptr = (char*)xmlNodeListGetString(doc_, nodeset_->nodeTab[0]->xmlChildrenNode,1);
        if (xml_str_ptr) {
                value.assign(xml_str_ptr);
                xmlFree(xml_str_ptr);
        } else value = "";

        return true;
}
bool Configer::get(const string &xpath, vector<string> &values)
{
        values.clear();

        PASS_OR_FAIL(xpath_context_, "null pointer.");
        PASS_OR_FAIL(xpath_obj_=xmlXPathEvalExpression(BAD_CAST xpath.c_str(), xpath_context_),
                        "null xpath path[%s].", xpath.c_str());
        nodeset_ = xpath_obj_->nodesetval;
        PASS_OR_FAIL(!xmlXPathNodeSetIsEmpty(nodeset_), "empty nodeset.");

        for (int idx = 0; idx < nodeset_->nodeNr; ++idx) {
                char *xml_str_ptr = (char*)xmlNodeListGetString(doc_, 
                                nodeset_->nodeTab[idx]->xmlChildrenNode, 1);
                if (xml_str_ptr) {
                        values.push_back(string(xml_str_ptr));
                        xmlFree(xml_str_ptr);
                } else {
                        values.push_back("");
                }
        }

        return true;
}
Configer::~Configer()
{
        if(doc_) xmlFreeDoc(doc_);
        if(xpath_context_) xmlXPathFreeContext(xpath_context_);
        if(xpath_obj_) xmlXPathFreeObject(xpath_obj_);
        xmlCleanupParser();
}
}
