#include <common/parser.hpp>

#include <nlohmann/json.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace parser {

void normalize_text(std::string &pars_string) {
  pars_string.erase(
      std::remove_if(pars_string.begin(), pars_string.end(), ispunct),
      pars_string.end());

  std::transform(
      pars_string.begin(), pars_string.end(), pars_string.begin(), tolower);
}

std::vector<std::string> delete_spaces(std::string &pars_string) {

  std::vector<std::string> list_strings;

  size_t start = 0;
  size_t end = 0;

  while ((start = pars_string.find_first_not_of(' ', end)) !=
         std::string::npos) {
    end = pars_string.find(' ', start);
    list_strings.push_back(pars_string.substr(start, end - start));
  }

  return list_strings;
}

void delete_stop_words(
    std::vector<std::string> &list_strings, const ParserOpts &parser_opts) {

  list_strings.erase(
      std::remove_if(
          list_strings.begin(),
          list_strings.end(),
          [&](const auto &item) {
            return (
                parser_opts.stop_words_.find(item) !=
                    parser_opts.stop_words_.end() ||
                item.size() < parser_opts.ngram_min_length_);
          }),
      list_strings.end());
}

void split_to_ngrams(
    std::vector<std::vector<std::string>> &ngram_words,
    std::vector<std::string> &list_strings,
    const ParserOpts &parser_opts) {

  ngram_words.resize(list_strings.size());

  size_t ngram_index = 0;

  for (auto &item : list_strings) {
    const size_t size = item.size();
    if (size < parser_opts.ngram_max_length_ &&
        size >= parser_opts.ngram_min_length_) {
      for (size_t i = parser_opts.ngram_min_length_; i <= size; i++) {
        ngram_words[ngram_index].push_back(item.substr(0, i));
      }
      ngram_index++;
    } else if (size >= parser_opts.ngram_max_length_) {
      for (size_t i = parser_opts.ngram_min_length_;
           i <= parser_opts.ngram_max_length_;
           i++) {
        ngram_words[ngram_index].push_back(item.substr(0, i));
      }
      ngram_index++;
    }
  }
}

void parse_text(
    std::string pars_string,
    std::vector<std::vector<std::string>> &ngram_words,
    const ParserOpts &parser_opts) {

  std::vector<std::string> list_strings;

  normalize_text(pars_string);
  list_strings = delete_spaces(pars_string);
  delete_stop_words(list_strings, parser_opts);
  split_to_ngrams(ngram_words, list_strings, parser_opts);
}

ParserOpts parse_config(const std::string &filename) {
  using json = nlohmann::json;

  std::ifstream file(filename);
  json data = json::parse(file);
  parser::ParserOpts parser_opts;
  parser_opts.stop_words_ = data["stop_words"];
  parser_opts.ngram_min_length_ = data["ngram_min_length"];
  parser_opts.ngram_max_length_ = data["ngram_max_length"];

  return parser_opts;
}

ParsedCsvDoc parse_csv_file(const fs_path &path_to_csv) {

  std::ifstream file(path_to_csv);

  ParsedCsvDoc parsed_docs;

  std::string pars_string;
  /*skipping the first line*/
  std::getline(file, pars_string);

  /*reading all lines*/
  while (std::getline(file, pars_string)) {
    std::vector<std::string> list_strings;

    size_t start = 0;
    size_t end = 0;
    for (size_t pos = 0; pos < 2; pos++) {
      start = pars_string.find_first_not_of(',', end);
      end = pars_string.find(',', start);
      list_strings.push_back(pars_string.substr(start, end - start));
    }
    const size_t doc_id = std::stoi(list_strings[0]);
    const auto text = list_strings[1];
    parsed_docs.insert({doc_id, text});
  }

  return parsed_docs;
}

} // namespace parser