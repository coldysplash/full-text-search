#pragma once

#include <common/parser.hpp>

#include <filesystem>
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

using fs_path = std::filesystem::path;

class IndexWriter {
public:
  virtual void
  write(const fs_path &path, Index const &index, bool testflag) = 0;
  virtual ~IndexWriter() = default;
};

class TextIndexWriter : public IndexWriter {
public:
  void write(const fs_path &path, Index const &index, bool testflag) override;
};

void write_direct_index(const fs_path &path, Index const &index);
void write_reverse_index(
    const fs_path &path, Index const &index, bool testflag);

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

std::string hashing_term(const std::string &term, bool testflag);

} // namespace indexer