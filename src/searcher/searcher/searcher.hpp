#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_set>

struct Result {
  double score;
  size_t document_id;
};

struct Config {
  size_t ngram_min_length_ = 3;
  size_t ngram_max_length_ = 6;
  std::unordered_set<std::string> stop_words_;
};

struct TermInfos {
  size_t term_frequency = 0;
  size_t document_frequency = 0;
};

Result search(std::string query, IndexAccessor &index_accessor);

// interface
class IndexAccessor {
public:
  virtual Config config() = 0;
  virtual TermInfos get_term_infos(const std::string &term) = 0;
  virtual std::string load_document(size_t document_id) = 0;
  virtual size_t total_docs() = 0;
  virtual ~IndexAccessor() = default;
}

class TextIndexAccessor : public IndexAccessor {
private:
  std::filesystem path_;

public:
  void TextIndexAccessor(std::filesystem::path &path);
  Config config() const override;
  TermInfos get_term_infos(const std::string &term) override;
  std::string load_document(size_t document_id) override;
  size_t total_docs() override;
};
