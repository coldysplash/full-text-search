#include <driver/driver.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <fstream>
#include <iostream>

namespace driver {

void index_command(const IndexConfig &options) {

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

void SearchCommand::search_and_print(const std::string &query) const {

  const searcher::TextIndexAccessor accessor(path_, parses_opts_);
  const searcher::Result result = searcher::search(query, accessor);

  std::cout << "Query: " << query << "\n\n";
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