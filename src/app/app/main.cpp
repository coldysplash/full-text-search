#include <common/parser.hpp>
#include <indexer/indexer.hpp>

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
    const std::unordered_set<std::string> stop_words = data["stop_words"];
    const uint16_t ngram_min_length = data["ngram_min_length"];
    const uint16_t ngram_max_length = data["ngram_max_length"];

    indexer::IndexBuilder index(
        {ngram_min_length, ngram_max_length}, stop_words);
    index.add_document(100, "The Matrix matrix");
    index.add_document(101, "The Matrix Reloaded");
    index.add_document(102, "The Matrix Revolutions");

    const indexer::Index doc_index = index.index();

    indexer::TextIndexWriter w;
    std::string path = "index";
    w.write(path, doc_index);

    for (const auto &[key, value] : doc_index.entries) {
      std::cout << key << ' ';
      for (const auto &[k, v] : value) {
        std::cout << k << ' ';
        for (const auto &s : v) {
          std::cout << s << ' ';
        }
      }
      std::cout << '\n';
    }
    std::cout << '\n';
    for (const auto &[key, val] : doc_index.docs) {
      std::cout << key << ' ' << val << '\n';
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Invalid input file!" << '\n';
    return -1;
  }
}