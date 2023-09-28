#include <common/parser.hpp>
#include <indexer/indexer.hpp>

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace indexer {

void IndexBuilder::add_document(size_t document_id, const std::string &text) {

  index_.docs.emplace(document_id, text);

  std::unordered_map<std::string, size_t> ngrams_out;

  parser::parse_text(
      text, stop_words, ngrams_out, ngram_min_length, ngram_max_length);
  // std::string term;
  // size_t doc_count = 0;
  // std::unordered_set<size_t> doc_id;
  // size_t pos_count = 0;
  // size_t pos = 0;

  // for (const auto &[key, val] : ngrams_out) {
  //   std::cout << key << ' ' << val << ' ';
  // }
  // std::cout << '\n';
}
} // namespace indexer