#pragma once
#include <common/parser.hpp>

#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace searcher {

using pair = std::pair<size_t, double>;

struct Result {
  std::map<size_t, double> results_;
  std::vector<pair> sorted_results_;
};

using Entries = std::map<std::string, std::map<size_t, std::vector<size_t>>>;

struct TermInfos {
  Entries entries_;
};

using Config = parser::ParserOpts;

class IndexAccessor {
public:
  virtual Config config() = 0;
  virtual TermInfos get_term_infos(const std::string &term) = 0;
  virtual std::string load_document(size_t document_id) = 0;
  virtual size_t total_docs() = 0;
  virtual ~IndexAccessor() = default;
};

class TextIndexAccessor : public IndexAccessor {
private:
  std::filesystem::path path_;
  TermInfos term_infos_;
  Config parser_opts_;

public:
  TextIndexAccessor(std::filesystem::path path, parser::ParserOpts parser_opts)
      : path_(path), parser_opts_(std::move(parser_opts)) {}

  Config config() override { return parser_opts_; }
  TermInfos get_term_infos(const std::string &term) override;
  std::string load_document(size_t document_id) override;
  size_t total_docs() override;
};

Result search(const std::string &query, TextIndexAccessor &index_accessor);

void sort_results(Result &result);

} // namespace searcher

double tf_idf(const double tf, const double df, const double N);