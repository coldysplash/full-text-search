#pragma once
#include <string>
#include <unordered_set>
#include <vector>

namespace parser {

void modify_text(std::string &pars_string);
void delete_spaces(
    std::vector<std::string> &list_strings, std::string &pars_string);
void delete_stop_words(
    std::vector<std::string> &list_strings,
    const std::unordered_set<std::string> &stop_words);
// void list_ngram(
//     std::vector<std::string> &list_strings,
//     std::vector<std::string> &ngram_words,
//     const short &ngram_min_length,
//     const short &ngram_max_length);

} // namespace parser