#include <common/parser.hpp>
#include <indexer/indexer.hpp>

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace indexer {

void IndexBuilder::add_document(size_t document_id, const std::string &text) {

  index_.docs.insert({document_id, text});

  std::vector<std::vector<std::string>> ngrams;

  parser::parse_text(
      text, stop_words, ngrams, ngram_min_length, ngram_max_length);

  for (size_t pos = 0; pos < ngrams.size(); ++pos) {
    for (const auto &word : ngrams[pos]) {
      index_.entries[word][document_id].insert(pos);
    }
  }
}
} // namespace indexer