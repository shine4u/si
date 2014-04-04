/*
 * author: wangbangxu
 * date: 2013-08-26
 */

#ifndef _LINE_PARSER_H_
#define _LINE_PARSER_H_

#include <boost/regex.hpp>
#include "BasicDefs.h"
#include "Logger.h"
#include "Configer.h"

namespace si {

class LineParser {
public:
        typedef pair<boost::regex, string> my_regex; // 添加正则表达式的name

        /*  默认分隔符为\t */
        LineParser(int field_num, const string &seperators = "\t");

        /* 设置第'id'列的名称为'name' */
        bool set_name(int id, const string &name);
    bool set_name_from_cfg(Configer &cfg, const string &path);

        /* 设置'name'列的断言'assertion' */
        bool set_assert(const string &name, const string &assertion);

        /* 设置'name'列的值为'value'，和parse_line 可以相互覆盖 
         * 如果'name'找不到，则会添加其到临时KV中，下次parse_line时清除
         */
        bool set_value(const string &name, const string &value);

        /* 按顺序添加特征名称到dump_ids_中，如果name找不到，那么会认为是临时name */
        bool set_dump(const string &name);
    bool set_dump_from_cfg(Configer &cfg, const string &path);

        /* 解析当前行 */
        bool parse_line(const string &line);

        /* 按照设置的set_dump， 输出数据到到文件流中 */
        bool dump(FILE *fout = NULL);
private:
    void reset_temp_kv();
    /* 获取列为'name'的值，在标准或者临时KV中获取 */
    bool get_value(const string &name, string &value);

        string separators_; // 分隔符列表
        vector< pair<int, my_regex> > assertions_; // 断言列id，断言表达式
        int field_num_; // 列数
        vector<string> field_names_; // 每列数据的名称
        vector<string> field_values_; // 列数据的值
        vector< pair<string, string> > temp_kv_;
        vector< pair<int,string> > dump_ids_; // 需要输出的id列表
};
} // end namespace si

#endif // _LINE_PARSER_H_
