#include <common/parser.hpp>
#include <indexer/indexer.hpp>

#include <picosha2.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace indexer {

void IndexBuilder::add_document(size_t document_id, const std::string &text) {

  index_.docs.insert({document_id, text});

  std::vector<std::vector<std::string>> ngrams;

  parser::parse_text(text, ngrams, parser_opts_);

  for (size_t pos = 0; pos < ngrams.size(); ++pos) {
    for (const auto &word : ngrams[pos]) {
      index_.entries[word][document_id].insert(pos);
    }
  }
}

void TextIndexWriter::write(std::filesystem::path &path, Index const &index) {

  std::filesystem::create_directories(path / "index");

  if (!index.docs.empty()) {
    const std::filesystem::path path_docs = path / "index/docs";
    size_t total_docs = 0;
    std::filesystem::create_directories(path_docs);
    for (const auto &[id, str] : index.docs) {
      std::ofstream file(path_docs / std::to_string(id));
      file << str;
      total_docs++;
    }
    std::ofstream file(path_docs / "total_docs");
    file << total_docs;
  }

  if (!index.entries.empty()) {
    const std::filesystem::path path_entries = path / "index/entries";
    std::filesystem::create_directories(path_entries);
    for (const auto &[term, term_info] : index.entries) {
      std::string hash_term;
      picosha2::hash256_hex_string(term, hash_term);
      std::ofstream file(path_entries / hash_term.substr(0, 6));
      file << term << ' ';
      file << term_info.size() << ' ';
      for (const auto &[doc_id, info] : term_info) {
        file << doc_id << ' ';
        file << info.size() << ' ';
        for (const auto &i : info) {
          file << i << ' ';
        }
      }
    }
  }
}

} // namespace indexer