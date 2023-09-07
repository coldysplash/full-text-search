#include <iostream>

#include <libfts/fts.hpp>

#include <CLI/CLI.hpp>

#include <string>

int main(int argc, char **argv) {
  CLI::App app("Sum two numbers");

  double value_1{0.0};
  double value_2{0.0};
  app.add_option("--first", value_1, "./app --first x --second y");
  app.add_option(
      "--second", value_2, "app - name exe file | x, y - value numbers");

  CLI11_PARSE(app, argc, argv);

  std::cout << "Sum = " << fts::sum_two_numbers(value_1, value_2) << '\n';
}