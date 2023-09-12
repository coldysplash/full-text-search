#include <common/parser.hpp>

#include <CLI/CLI.hpp>

#include <iostream>

#include <string>

#include <vector>

// int main(int argc, char **argv) {
int main() {
  std::string text = "Hello and goodbye!!!";
  parser::delete_puncts(text);
  parser::str_tolower(text);
  std::vector<std::string> list_strings;
  parser::delete_spaces(list_strings, text);
  std::vector<std::string> stop_words = {"and", "a", "an"};
  parser::delete_stop_words(list_strings, stop_words);
  for(auto &s: list_strings){
    std::cout << s << '\n';
  }
  // const std::vector<std::string> stop_words = {"and", "a" , "an"};
  // parser::delete_stop_words(text, stop_words);

  // std::cout << text << std::endl;

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