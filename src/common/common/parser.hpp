#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace parser {

void modify_text(std::string &pars_string);
void delete_spaces(
    std::vector<std::string> &list_strings, std::string &pars_string);
void delete_stop_words(
    std::vector<std::string> &list_strings,
    const std::unordered_set<std::string> &stop_words);
void split_to_ngrams(
    std::unordered_map<std::string, int> &ngram_words,
    std::vector<std::string> &list_strings,
    uint16_t ngram_min_length,
    uint16_t ngram_max_length);
void NgramParser(
    std::string &pars_string,
    const std::unordered_set<std::string> &stop_words,
    std::unordered_map<std::string, int> &ngram_words,
    uint16_t ngram_min_length,
    uint16_t ngram_max_length);

} // namespace parser