#include <driver/driver.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

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

void search_and_print(const SearchConfig &options) {

  const searcher::TextIndexAccessor accessor(
      options.path_to_index_, options.parser_opts_);
  const searcher::Result result = searcher::search(options.query_, accessor);

  std::cout << "Query: " << options.query_ << "\n\n";
  std::cout << "id\t"
            << "score\t"
            << "\ttext" << '\n';

  for (auto const &[doc_id, score] : result.results_) {
    const std::string text = accessor.load_document(doc_id);
    std::cout << doc_id << '\t' << score << "\t\t" << text << '\n';
  }
  std::cout << std::endl;
}

} // namespace driver