#include <driver/driver.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <CLI/CLI.hpp>
#include <replxx.hxx>

#include <fstream>
#include <iostream>

namespace driver {

void index_build_and_write(const IndexConfig &options) {

  const parser::ParsedCsvDoc parsed_docs =
      parser::parse_csv_file(options.path_to_csv_);

  indexer::IndexBuilder index(options.parser_opts_);
  for (const auto &[doc_id, text] : parsed_docs) {
    index.add_document(doc_id, text);
  }

  const indexer::Index index_docs = index.index();
  indexer::TextIndexWriter to_write;
  to_write.write(options.path_to_index_, index_docs, false);
}

void print_search_result(
    const searcher::Result &result, const searcher::IndexAccessor &accessor) {

  std::cout << "id\t"
            << "score\t"
            << "\ttext" << '\n';
  for (auto const &[doc_id, score] : result.results_) {
    const std::string text = accessor.load_document(doc_id);
    std::cout << doc_id << '\t' << score << "\t\t" << text << '\n';
  }
  std::cout << std::endl;
}

void search_and_print(const SearchConfig &options) {

  const searcher::TextIndexAccessor accessor(
      options.path_to_index_, options.parser_opts_);

  if (options.query_.empty()) {
    /* Interactive input */
  } else {
    const searcher::Result result = searcher::search(options.query_, accessor);
    std::cout << "Query: " << options.query_ << "\n\n";
    print_search_result(result, accessor);
  }
}

CLI::App *create_indexer(CLI::App &app, IndexConfig &options) {

  CLI::App *index = app.add_subcommand("index", "Command for index book");

  index->add_option("--csv", options.path_to_csv_, "Path to .csv file")
      ->required();
  index->add_option("--index", options.path_to_index_, "Path to index save")
      ->required();

  return index;
}

CLI::App *create_searcher(CLI::App &app, SearchConfig &options) {

  CLI::App *search = app.add_subcommand("search", "Command for search query");

  search->add_option("--index", options.path_to_index_, "Path to index")
      ->required();
  search->add_option("--query", options.query_, "<query text>");

  return search;
}

} // namespace driver