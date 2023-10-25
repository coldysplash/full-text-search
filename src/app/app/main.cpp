#include <common/parser.hpp>
#include <driver/driver.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;

int main(int argc, char **argv) {
  try {
    CLI::App app("Fts");
    std::string filename = "config.json";
    app.add_option("--config", filename, "<path> (default=config.json)");

    CLI11_PARSE(app, argc, argv);

    std::ifstream file(filename);
    json data = json::parse(file);

    parser::ParserOpts parser_opts;
    parser_opts.stop_words_ = data["stop_words"];
    parser_opts.ngram_min_length_ = data["ngram_min_length"];
    parser_opts.ngram_max_length_ = data["ngram_max_length"];

    driver::IndexConfig index_options;
    index_options.parser_opts_ = parser_opts;
    index_options.path_to_csv_ = "books.csv";
    index_options.path_to_index_ = ".";

    driver::index_command(index_options);

    const driver::SearchCommand search(".", parser_opts);
    const std::string query = "Harry Potter";
    search.search_command(query);

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Invalid input file!" << '\n';
    return -1;
  }
}