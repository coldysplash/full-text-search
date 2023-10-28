#include <common/parser.hpp>
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
    CLI::App app("Parser");
    std::string filename = "config.json";
    app.add_option("--config", filename, "<path> (default=config.json)");

    CLI11_PARSE(app, argc, argv);

    std::ifstream file(filename);
    json data = json::parse(file);

    parser::ParserOpts parser_opts;
    parser_opts.stop_words_ = data["stop_words"];
    parser_opts.ngram_min_length_ = data["ngram_min_length"];
    parser_opts.ngram_max_length_ = data["ngram_max_length"];

    /*indexer*/
    indexer::IndexBuilder index(parser_opts);
    index.add_document(100, "Hello World");
    index.add_document(101, "Bye World");
    index.add_document(102, "Hello Earth");

    const indexer::Index doc_index = index.index();
    indexer::TextIndexWriter w;
    const std::filesystem::path path = ".";
    w.write(path, doc_index, false);

    /*search*/
    const std::string query = "Hello World";
    const searcher::TextIndexAccessor accessor(path, parser_opts);
    const searcher::Result result = searcher::search(query, accessor);

    std::cout << "Query: " << query << '\n';
    std::cout << " id "
              << " score "
              << "      text" << '\n';

    for (auto const &[doc_id, score] : result.results_) {
      const std::string text = accessor.load_document(doc_id);
      std::cout << doc_id << "  " << score << "    " << text << '\n';
    }
    std::cout << std::endl;

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    std::cerr << "Invalid input file!" << '\n';
    return -1;
  }
}