#pragma once
#include <string>
#include <vector>

namespace parser {

void delete_puncts(std::string &pars_string);
void str_tolower(std::string &pars_string);
void delete_spaces(std::vector<std::string> &list_strings, std::string &pars_string);
void delete_stop_words(
    std::vector<std::string> &list_strings, const std::vector<std::string> &stop_words);

} // namespace parser