#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

namespace parser {

using fs_path = std::filesystem::path;
using ParsedCsvDoc = std::map<size_t, std::string>;

struct ParserOpts {
  size_t ngram_min_length_ = 3;
  size_t ngram_max_length_ = 6;
  std::unordered_set<std::string> stop_words_;
};

void normalize_text(std::string &pars_string);
std::vector<std::string> delete_spaces(std::string &pars_string);
void delete_stop_words(
    std::vector<std::string> &list_strings, const ParserOpts &parser_opts);
void split_to_ngrams(
    std::vector<std::vector<std::string>> &ngram_words,
    std::vector<std::string> &list_strings,
    const ParserOpts &parser_opts);
void parse_text(
    std::string pars_string,
    std::vector<std::vector<std::string>> &ngram_words,
    const ParserOpts &parser_opts);

ParsedCsvDoc parse_csv_file(const fs_path &path_to_csv);

} // namespace parser