#include <common/parser.hpp>
#include <driver/driver.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <CLI/CLI.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  try {
    CLI::App app("Full-Text-Searcher");
    app.set_help_all_flag("--help-all", "Expand all help");

    std::string filename = "config.json";
    app.add_option("--config", filename, "<path> (default=config.json)");

    driver::IndexConfig index_options;
    driver::SearchConfig search_options;
    CLI::App *indexer = driver::create_indexer(app, index_options);
    CLI::App *searcher = driver::create_searcher(app, search_options);
    app.require_subcommand(); // 1 or more

    CLI11_PARSE(app, argc, argv);

    const parser::ParserOpts parser_opts = parser::parse_config(filename);
    index_options.parser_opts_ = parser_opts;
    search_options.parser_opts_ = parser_opts;

    if (indexer->parsed()) {
      driver::index_build_and_write(index_options);
    } else if (searcher->parsed()) {
      driver::search_and_print(search_options);
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Invalid input file!" << '\n';
    return -1;
  }
}