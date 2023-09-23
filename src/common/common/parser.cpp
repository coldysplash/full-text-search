#include <common/parser.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace parser {

void normalize_text(std::string &pars_string) {
  pars_string.erase(
      std::remove_if(pars_string.begin(), pars_string.end(), ispunct),
      pars_string.end());

  std::transform(
      pars_string.begin(), pars_string.end(), pars_string.begin(), tolower);
}

void delete_spaces(
    std::vector<std::string> &list_strings, std::string &pars_string) {

  size_t start = 0;
  size_t end = 0;

  while ((start = pars_string.find_first_not_of(' ', end)) !=
         std::string::npos) {
    end = pars_string.find(' ', start);
    list_strings.push_back(pars_string.substr(start, end - start));
  }
}

void delete_stop_words(
    std::vector<std::string> &list_strings,
    const std::unordered_set<std::string> &stop_words) {

  list_strings.erase(
      std::remove_if(
          list_strings.begin(),
          list_strings.end(),
          [&stop_words](std::string &item) {
            return (stop_words.find(item) != stop_words.end());
          }),
      list_strings.end());
}

void split_to_ngrams(
    std::unordered_map<std::string, int> &ngram_words,
    std::vector<std::string> &list_strings,
    uint16_t ngram_min_length,
    uint16_t ngram_max_length) {

  int ngram_index = 0;

  std::for_each(
      list_strings.begin(),
      list_strings.end(),
      [&ngram_words, &ngram_min_length, &ngram_max_length, &ngram_index](
          std::string &item) {
        const size_t size = item.size();
        if (size < ngram_max_length && size > ngram_min_length) {
          for (size_t i = ngram_min_length; i <= size; i++) {
            ngram_words.insert({item.substr(0, i), ngram_index});
          }
          ngram_index++;
        } else if (size >= ngram_max_length) {
          for (size_t i = ngram_min_length; i <= ngram_max_length; i++) {
            ngram_words.insert({item.substr(0, i), ngram_index});
          }
          ngram_index++;
        }
      });
}

void parse_text(
    std::string pars_string,
    const std::unordered_set<std::string> &stop_words,
    std::unordered_map<std::string, int> &ngram_words,
    uint16_t ngram_min_length,
    uint16_t ngram_max_length) {

  std::vector<std::string> list_strings;

  normalize_text(pars_string);
  delete_spaces(list_strings, pars_string);
  delete_stop_words(list_strings, stop_words);
  split_to_ngrams(
      ngram_words, list_strings, ngram_min_length, ngram_max_length);
}

} // namespace parser