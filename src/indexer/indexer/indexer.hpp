#pragma once
#include <map>
#include <set>
#include <string>
#include <unordered_set>

namespace indexer {

using Docs = std::map<size_t, std::string>;
using Entries = std::map<std::string, std::map<size_t, std::set<size_t>>>;

struct Index {
  Docs docs;
  Entries entries;
};

class IndexWriter {
public:
  virtual void write(std::string &path, Index const &index) = 0;
  virtual ~IndexWriter() = default;
};

class TextIndexWriter : public IndexWriter {
public:
  void write(std::string &path, Index const &index) override;
};

class IndexBuilder {
private:
  Index index_;
  uint16_t ngram_min_length_;
  uint16_t ngram_max_length_;
  std::unordered_set<std::string> stop_words_;

public:
  explicit IndexBuilder(
      const std::pair<uint16_t, uint16_t> ngram_ranges,
      const std::unordered_set<std::string> &stop_words)
      : ngram_min_length_(ngram_ranges.first),
        ngram_max_length_(ngram_ranges.second), stop_words_(stop_words) {}

  void add_document(size_t document_id, const std::string &text);
  Index index() const { return index_; };
};

} // namespace indexer