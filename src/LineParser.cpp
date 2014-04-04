#include <boost/algorithm/string.hpp>
#include "LineParser.h"
//#include "json/json.h"
namespace si {

LineParser::LineParser(int field_num, const string &separators) {
        field_num_ = field_num;
        separators_ = separators;

        field_names_.assign(field_num, string());
        field_values_.assign(field_num, string());
}

bool LineParser::set_name(int id, const string &name) {
        PASS_OR_FAIL(0<=id && id<field_num_, "bad id[%d]", id);
        PASS_OR_FAIL(find(ALL(field_names_), name)==field_names_.end(), "dup names[%s]", name.c_str());
        PASS_OR_FAIL(field_names_[id]=="", "field[%d]==[%s]", id, field_names_[id].c_str());

        field_names_[id] = name;
        SI_NOTICE("add new field to LineParser field[%d]==[%s]", id, field_names_[id].c_str());

        return true;
}
bool LineParser::set_name_from_cfg(Configer &cfg, const string &path) {
    vector<string> fnames;
    bool retval = cfg.get(path, fnames);
    PASS_OR_FAIL(retval, "err cfg.get");
    field_names_ = fnames;

    return true;
}

void LineParser::reset_temp_kv() {
        temp_kv_.clear();
}
bool LineParser::set_value(const string &name, const string &value) {
        for (int x = 0; x < SIZE(field_names_); ++ x) {
                if (field_names_[x] == name) {
                        field_values_[x] = value;
                        return true;
                }
        }
        SI_DEBUG("name no found [%s], treat as temp kv", name.c_str());
        temp_kv_.push_back(make_pair(name, value));
        return true;
}
bool LineParser::get_value(const string &name, string &value) {
        for (int x = 0; x < SIZE(field_names_); ++ x) {
                if (field_names_[x] == name) {
                        value = field_values_[x];
                        return true;
                }
        }
        SI_DEBUG("name no found [%s], treat as temp kv", name.c_str());
        for (int x = 0; x < SIZE(temp_kv_); ++ x) {
                if (temp_kv_[x].first == name) {
                        value = temp_kv_[x].second;
                        return true;
                }
        }
        return false;
}
bool LineParser::set_assert(const string &name, const string &assertion) {
        vector<string>::iterator it = find(ALL(field_names_), name);
        PASS_OR_FAIL(it != field_names_.end(), "name no found [%s]", name.c_str());
        int id = it - field_names_.begin();
        assertions_.push_back(make_pair(id, make_pair(boost::regex(assertion), assertion)));
        SI_NOTICE("add new assertion to LineParser [%d] with[%s]", id, assertion.c_str());
        return true;
}
bool LineParser::set_dump(const string &name) {
        for (int x = 0; x < SIZE(field_names_); ++ x) {
                if ( field_names_[x] == name) {
                        dump_ids_.push_back(make_pair(x, name));
                        SI_NOTICE("add new dump to LineParser field[%d]==[%s]", x, field_names_[x].c_str());
                        return true;
                }
        }
        dump_ids_.push_back(make_pair(-1, name));
        SI_NOTICE("add new dump to LineParser temp-kv[%s]", name.c_str());
        return true;
}
bool LineParser::set_dump_from_cfg(Configer &cfg, const string &path) {
    vector<string> fnames;
    bool retval = cfg.get(path, fnames);
    PASS_OR_FAIL(retval, "err cfg.get");
    dump_ids_.clear();
    REP (x, SIZE(fnames))
        dump_ids_.push_back(make_pair(x, fnames[x]));

    return true;
}
bool LineParser::parse_line(const string &line) {
        reset_temp_kv();
        boost::split(field_values_, line, boost::is_any_of(separators_), boost::token_compress_off);
        PASS_OR_FAIL(SIZE(field_values_) == field_num_, "field_value size[%d]", SIZE(field_values_));
        for (int x = 0; x < SIZE(assertions_); ++x) {
                int id = assertions_[x].first;
                boost::regex reg = assertions_[x].second.first;
                string &reg_name = assertions_[x].second.second;
                PASS_OR_FAIL(boost::regex_match(field_values_[id], reg), "value[%s] reg[%s]",
                                field_values_[id].c_str(), reg_name.c_str());
        }
        SI_DEBUG("parse_line success! line[%s]", line.c_str());
        return true;
}
bool LineParser::dump(FILE *fout) {
        if (!fout)
                fout = stdout;
        for (int x = 0; x < SIZE(dump_ids_); ++x) {
                int id = dump_ids_[x].first;
                if (id != -1) {
                        fprintf(fout, "%s", field_values_[id].c_str());
                        fprintf(fout, "%c", x+1==SIZE(dump_ids_)?'\n':'\t');
                } else {
                        for (int y = 0; y < SIZE(temp_kv_); ++ y) 
                                if (temp_kv_[y].first == dump_ids_[x].second) {
                                        id = y;
                                        break;
                                }
                        PASS_OR_FAIL(id != -1, "dump attr no found [%s]", dump_ids_[x].second.c_str());
                        fprintf(fout, "%s", temp_kv_[id].second.c_str());
                        fprintf(fout, "%c", x+1==SIZE(dump_ids_)?'\n':'\t');
                }
        }
        SI_DEBUG("dump success!");
        return true;
}
}
