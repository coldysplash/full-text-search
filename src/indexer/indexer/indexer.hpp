#pragma once

#include <common/parser.hpp>

#include <map>
#include <set>
#include <string>

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
  parser::ParserOpts parser_opts_;

public:
  explicit IndexBuilder(parser::ParserOpts parser_opts)
      : parser_opts_(std::move(parser_opts)) {}

  void add_document(size_t document_id, const std::string &text);
  Index index() const { return index_; };
};

} // namespace indexer