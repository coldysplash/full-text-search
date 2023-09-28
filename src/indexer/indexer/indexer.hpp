#pragma once
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

namespace indexer {

using Docs = std::map<size_t, std::string>;
using Entries = std::map<std::string, std::map<size_t, std::set<size_t>>>;

struct Index {
  Docs docs;
  Entries entries;
};

class IndexWriter {
public:
  virtual void write(std::string path, Index index_) = 0;
};

class TextIndexWriter : public IndexWriter {
public:
  void write(std::string path, Index index_);
};

class IndexBuilder {
private:
  Index index_;
  const uint16_t ngram_min_length;
  const uint16_t ngram_max_length;
  const std::unordered_set<std::string> stop_words;

public:
  explicit IndexBuilder(
      const uint16_t ngram_min_length,
      const uint16_t ngram_max_length,
      const std::unordered_set<std::string> stop_words)
      : ngram_min_length(ngram_min_length), ngram_max_length(ngram_max_length),
        stop_words(stop_words) {}

  void add_document(size_t document_id, const std::string &text);
  Index index() const { return index_; };
};

} // namespace indexer