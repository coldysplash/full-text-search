#include <common/parser.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <picosha2.h>

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

double tf_idf(const double tf, const double df, const double N) {
  const double result = tf * log(N / df);
  return result;
}

namespace searcher {

Result search(const std::string &query, TextIndexAccessor &index_accessor) {

  std::vector<std::vector<std::string>> terms;
  parser::parse_text(query, terms, index_accessor.config());

  TermInfos term_info;
  for (const auto &items : terms) {
    for (const auto &term : items) {
      term_info = index_accessor.get_term_infos(term);
    }
  }

  Result result;
  const auto total_docs = static_cast<double>(index_accessor.total_docs());
  for (const auto &[key, value] : term_info.entries_) {
    for (const auto &[k, v] : value) {
      const size_t doc_id = k;
      const auto tf = static_cast<double>(v[0]);
      const auto df = static_cast<double>(v[1]);
      const double tmp_res = tf_idf(tf, df, total_docs);
      result.results_[doc_id] += tmp_res;
    }
  }

  sort_results(result);

  return result;
}

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
    i += term_frequency + 1;
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

void sort_results(Result &result) {
  std::copy(
      result.results_.begin(),
      result.results_.end(),
      std::back_inserter<std::vector<pair>>(result.sorted_results_));

  std::sort(
      result.sorted_results_.begin(),
      result.sorted_results_.end(),
      [](const pair &l, const pair &r) {
        if (l.second != r.second) {
          return l.second > r.second;
        }

        return l.first > r.first;
      });

} /*https://www.techiedelight.com/ru/sort-map-values-cpp/*/

} // namespace searcher