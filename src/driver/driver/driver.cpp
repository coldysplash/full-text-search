#include <driver/driver.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <fstream>
#include <iostream>

namespace driver {

ParsedCsvDoc parse_csv_file(const fs_path &path_to_csv) {

  std::ifstream file(path_to_csv);

  ParsedCsvDoc parsed_docs;

  std::string pars_string;
  /*skipping the first line*/
  std::getline(file, pars_string);

  /*reading all lines*/
  while (std::getline(file, pars_string)) {
    std::vector<std::string> list_strings;

    size_t start = 0;
    size_t end = 0;
    for (size_t pos = 0; pos < 2; pos++) {
      start = pars_string.find_first_not_of(',', end);
      end = pars_string.find(',', start);
      list_strings.push_back(pars_string.substr(start, end - start));
    }
    const size_t doc_id = std::stoi(list_strings[0]);
    const auto text = list_strings[1];
    parsed_docs.insert({doc_id, text});
  }

  return parsed_docs;
}

void index_command(const IndexConfig &options) {

  const ParsedCsvDoc parsed_docs = parse_csv_file(options.path_to_csv_);

  indexer::IndexBuilder index(options.parser_opts_);
  for (const auto &[doc_id, text] : parsed_docs) {
    index.add_document(doc_id, text);
  }

  const indexer::Index index_docs = index.index();
  indexer::TextIndexWriter to_write;
  to_write.write(options.path_to_index_, index_docs, false);
}

void SearchCommand::search_command(const std::string &query) const {

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