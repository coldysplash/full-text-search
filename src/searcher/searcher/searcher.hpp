#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace searcher {

using Entries = std::map<std::string, std::map<size_t, std::vector<size_t>>>;

struct Result {
  std::map<size_t, double> result_;
};

struct TermInfos {
  Entries entries_;
};

class IndexAccessor {
public:
  virtual TermInfos get_term_infos(const std::string &term) = 0;
  virtual std::string load_document(size_t document_id) = 0;
  virtual size_t total_docs() = 0;
  virtual ~IndexAccessor() = default;
};

class TextIndexAccessor : public IndexAccessor {
private:
  std::filesystem::path path_;
  TermInfos term_infos_;

public:
  TextIndexAccessor(std::filesystem::path path) : path_(path) {}

  TermInfos get_term_infos(const std::string &term) override;
  std::string load_document(size_t document_id) override;
  size_t total_docs() override;
};

Result search(const std::string &query, TextIndexAccessor &index_accessor);

} // namespace searcher

// double tf_idf(const double tf, const double df, const double N);