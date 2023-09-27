#include <common/parser.hpp>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using json = nlohmann::json;

int main(int argc, char **argv) {
  try {
    CLI::App app("Parser");
    std::string filename = "config.json";
    app.add_option("--config", filename, "<path> (default=config.json)");

    CLI11_PARSE(app, argc, argv);

    std::ifstream file(filename);
    json data = json::parse(file);
    const std::string text = data["text"];
    const std::unordered_set<std::string> stop_words = data["stop_words"];
    const uint16_t ngram_min_length = data["ngram_min_length"];
    const uint16_t ngram_max_length = data["ngram_max_length"];

    std::cout << "Input: " << text << '\n';

    std::unordered_map<std::string, size_t> ngram_words;
    parser::parse_text(
        text, stop_words, ngram_words, ngram_min_length, ngram_max_length);

    std::cout << "Output: ";
    for (const auto &[en, ru] : ngram_words) {
      std::cout << en << " " << ru << ' ';
    }
    std::cout << '\n';
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Invalid input file!" << '\n';
    return -1;
  }
}