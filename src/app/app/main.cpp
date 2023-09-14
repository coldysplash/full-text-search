#include <common/parser.hpp>

#include <CLI/CLI.hpp>

#include <iostream>

#include <string>

#include <vector>

#include <unordered_set>

// int main(int argc, char **argv) {
int main() {
  std::string text = "Hello and goodbye!!!";
  const std::unordered_set<std::string> stop_words{"and", "a", "an"};
  uint16_t ngram_min_length = 2;
  uint16_t ngram_max_length = 6;

  std::vector<std::string> ngram_words;

  parser::NgramParser(
      text, stop_words, ngram_words, ngram_min_length, ngram_max_length);

  for (auto &item : ngram_words) {
    std::cout << item << ' ';
  }

  // CLI::App app("Sum two numbers");

  // double value_1{0.0};
  // double value_2{0.0};
  // app.add_option("--first", value_1, "./app --first x --second
  // y")->required(); app.add_option(
  //        "--second", value_2, "app - name exe file | x, y - value numbers")
  //     ->required();

  // CLI11_PARSE(app, argc, argv);

  // std::cout << "Sum = " << fts::sum_two_numbers(value_1, value_2) << '\n';
}