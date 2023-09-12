#include <common/parser.hpp>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

namespace parser {

void delete_puncts(std::string &pars_string) {
  pars_string.erase(
      std::remove_if(pars_string.begin(), pars_string.end(), ::ispunct),
      pars_string.end());
}

void str_tolower(std::string &pars_string) {
  std::transform(
      pars_string.begin(), pars_string.end(), pars_string.begin(), [](char &c) {
        return std::tolower(c);
      });
}

void delete_spaces(
    std::vector<std::string> &list_strings, std::string &pars_string) {

  size_t start;
  size_t end = 0;

  while ((start = pars_string.find_first_not_of(' ', end)) !=
         std::string::npos) {
    end = pars_string.find(' ', start);
    list_strings.push_back(pars_string.substr(start, end - start));
  }
}

void delete_stop_words(
    std::vector<std::string> &list_strings,
    const std::vector<std::string> &stop_words) {
  for (auto iter{list_strings.begin()}; iter != list_strings.end(); iter++) {
    for (auto &c : stop_words) {
      if (*iter == c) {
        list_strings.erase(iter);
      }
    }
  }
}

// void list_ngram(std::vector<std::string> &list_strings, const short &ngram_min_length, const short &ngram_max_length){

// }

} // namespace parser