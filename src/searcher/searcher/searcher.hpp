#pragma once
#include <common/parser.hpp>

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace searcher {

struct IdScore {
  size_t doc_id;
  double score;
};

struct Result {
  std::vector<IdScore> results_;
};

using Entries = std::map<std::string, std::map<size_t, std::vector<size_t>>>;

struct TermInfos {
  Entries entries_;
};

using Config = parser::ParserOpts;

class IndexAccessor {
public:
  virtual Config config() const = 0;
  virtual TermInfos
  get_term_infos(const std::string &term, bool testflag) const = 0;
  virtual std::string load_document(size_t document_id) const = 0;
  virtual size_t total_docs() const = 0;
  virtual ~IndexAccessor() = default;
};

class TextIndexAccessor : public IndexAccessor {
private:
  std::filesystem::path path_;
  Config parser_opts_;

public:
  TextIndexAccessor(std::filesystem::path path, parser::ParserOpts parser_opts)
      : path_(std::move(path)), parser_opts_(std::move(parser_opts)) {}

  Config config() const override { return parser_opts_; }
  TermInfos
  get_term_infos(const std::string &term, bool testflag) const override;
  std::string load_document(size_t document_id) const override;
  size_t total_docs() const override;
};

Result
search(const std::string &query, const TextIndexAccessor &index_accessor);

Result sort_results(const std::map<size_t, double> &tmp_results);

} // namespace searcher