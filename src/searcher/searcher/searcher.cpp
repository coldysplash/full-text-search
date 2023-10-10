#include <common/parser.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <picosha2.h>

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

namespace searcher {

Result search(const std::string &query, TextIndexAccessor &index_accessor) {

  std::vector<std::vector<std::string>> terms;
  const parser::ParserOpts opts;
  parser::parse_text(query, terms, opts);

  TermInfos term_info;
  for (const auto &items : terms) {
    for (const auto &term : items) {
      term_info = index_accessor.get_term_infos(term);
    }
  }

  // size_t doc_id = 0;
  // const size_t total_docs = index_accessor.total_docs();
  // size_t tf = 0;
  // size_t df = 0;
  // size_t res = 0;
  // for (const auto &[key, value] : term_info.entries_) {
  //   for (const auto &[k, v] : value) {
  //     doc_id = k;
  //     tf = v[0];
  //     df = v[1];
  //     res = tf_idf(tf, df, total_docs);
  //   }
  // }
  Result result;
  return result;
}

// double score(TermInfos term_info, size_t doc_id) {}

// double tf_idf(const size_t tf, const size_t df, const size_t N) {
//   const double result = tf * log(N / df);
//   return result;
// }

TermInfos TextIndexAccessor::get_term_infos(const std::string &term) {

  std::string hash_term;
  picosha2::hash256_hex_string(term, hash_term);
  std::ifstream file(path_ / "index/entries" / hash_term.substr(0, 6));

  std::string term_entries;
  while (file) {
    std::getline(file, term_entries);
  }

  std::vector<std::string> list_terms;
  parser::delete_spaces(list_terms, term_entries);

  const size_t doc_frequency = std::stoi(list_terms[1]);
  size_t i = 2;
  while (i < list_terms.size()) {
    const size_t doc_id = std::stoi(list_terms[i]);
    i++;
    const size_t term_frequency = std::stoi(list_terms[i]);
    term_infos_.entries_[term][doc_id].push_back(term_frequency);
    term_infos_.entries_[term][doc_id].push_back(doc_frequency);
    i++;
    for (size_t j = 0; j < term_frequency; ++j) {
      i++;
    }
  }

  return term_infos_;
}

std::string TextIndexAccessor::load_document(size_t document_id) {
  std::string text;
  std::ifstream file(path_ / "index/docs" / std::to_string(document_id));
  std::getline(file, text);

  return text;
}

size_t TextIndexAccessor::total_docs() {
  size_t total_docs = 0;
  std::ifstream file(path_ / "index/docs" / "total_docs");
  file >> total_docs;

  return total_docs;
}

} // namespace searcher