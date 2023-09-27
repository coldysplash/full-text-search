#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace indexer {

using Docs = std::unordered_map<std::size_t, std::string>;
using Entries =
    std::unordered_map<std::string, std::vector<std::unordered_set>>;

class IndexWriter {
public:
  virtual void write(std::string path, size_t index) = 0;
};

class TextIndexWriter::public IndexWriter {
  void write(std::string path, size_t index);
};

struct Index {
  Docs docs;
  Entries entries;
};

class IndexBuilder {
private:
  Index index_;

public:
  void add_document(std::size_t document_id, std::string text);
  Index index(){return index_};
};

} // namespace indexer