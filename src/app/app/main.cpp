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
    CLI::App app("Full-Text-Searcher");
    app.set_help_all_flag("--help-all", "Expand all help");

    std::string filename = "config.json";
    app.add_option("--config", filename, "<path> (default=config.json)");

    CLI::App *index = app.add_subcommand("index", "");
    CLI::App *search = app.add_subcommand("search", "");
    app.require_subcommand(); // 1 or more

    driver::fs_path path_csv;
    driver::fs_path path_index;
    index->add_option("--csv", path_csv, "Path to .csv file")->required();
    index->add_option("--index", path_index, "Path to index save")->required();

    search->add_option("--index", path_index, "Path to index")->required();
    std::string query_text;
    search->add_option("--query", query_text, "Query text");

    CLI11_PARSE(app, argc, argv);

    std::ifstream file(filename);
    json data = json::parse(file);

    parser::ParserOpts parser_opts;
    parser_opts.stop_words_ = data["stop_words"];
    parser_opts.ngram_min_length_ = data["ngram_min_length"];
    parser_opts.ngram_max_length_ = data["ngram_max_length"];

    driver::IndexConfig index_options;
    index_options.parser_opts_ = parser_opts;
    index_options.path_to_csv_ = path_csv;
    index_options.path_to_index_ = path_index;

    driver::SearchConfig search_options;
    search_options.parser_opts_ = parser_opts;
    search_options.path_to_index_ = path_index;

    if (index->parsed()) {
      driver::index_build_and_write(index_options);
    }

    if (search->parsed() && !query_text.empty()) {
      search_options.query_ = query_text;
      driver::search_and_print(search_options);
    } else if (search->parsed() && query_text.empty()) {
      search_options.query_ = "Harry Potter Chamber";
      driver::search_and_print(search_options);
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Invalid input file!" << '\n';
    return -1;
  }
}