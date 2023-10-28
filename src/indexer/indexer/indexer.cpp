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

void TextIndexWriter::write(
    const fs_path &path, Index const &index, bool testflag) {

  std::filesystem::create_directories(path / "index");
  write_direct_index(path, index);
  write_reverse_index(path, index, testflag);
}

void write_direct_index(const fs_path &path, Index const &index) {
  if (!index.docs.empty()) {
    const fs_path path_docs = path / "index/docs";
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
}

void write_reverse_index(
    const fs_path &path, Index const &index, bool testflag) {

  if (!index.entries.empty()) {
    const fs_path path_entries = path / "index/entries";
    std::filesystem::create_directories(path_entries);
    for (const auto &[term, term_info] : index.entries) {
      const fs_path path_entries_hash =
          path_entries / hashing_term(term, testflag);

      std::ofstream file(path_entries_hash, std::ios::app);

      file << term << ' ';
      file << term_info.size() << ' ';
      for (const auto &[doc_id, info_id] : term_info) {
        file << doc_id << ' ';
        file << info_id.size() << ' ';
        for (const auto &pos_term : info_id) {
          file << pos_term << ' ';
        }
      }
      file << '\n';
    }
  }
}

std::string hashing_term(const std::string &term, bool testflag) {
  if (!testflag) {
    std::string hashed_term;
    picosha2::hash256_hex_string(term, hashed_term);
    return hashed_term.substr(0, 6);
  }

  return "1";
}

} // namespace indexer