#include <algorithm>
#include <cctype>
#include <common/parser.hpp>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace parser {

void modify_text(std::string &pars_string) {
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

// void list_ngram(
//     std::vector<std::string> &list_strings,
//     std::vector<std::string> &ngram_words,
//     const short &ngram_min_length,
//     const short &ngram_max_length) {}

} // namespace parser