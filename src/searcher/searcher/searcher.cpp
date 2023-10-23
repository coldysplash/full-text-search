#include <common/parser.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <picosha2.h>

#include <cmath>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace {

double tf_idf(double tf, double df, double N) { return tf * log(N / df); }

} // namespace

namespace searcher {

Result
search(const std::string &query, const TextIndexAccessor &index_accessor) {

  std::vector<std::vector<std::string>> terms;
  parser::parse_text(query, terms, index_accessor.config());

  TermInfos term_info;
  std::map<size_t, double> results;
  const auto total_docs = static_cast<double>(index_accessor.total_docs());

  for (const auto &t_info : terms) {
    for (const auto &term : t_info) {
      term_info = index_accessor.get_term_infos(term, false);
      for (const auto &[term, t_infos] : term_info.entries_) {
        for (const auto &[doc_id, doc_id_info] : t_infos) {
          const size_t document_id = doc_id;
          const auto tf = static_cast<double>(doc_id_info[0]);
          const auto df = static_cast<double>(doc_id_info[1]);
          const double tmp_res = tf_idf(tf, df, total_docs);
          results[document_id] += tmp_res;
        }
      }
    }
  }

  return sort_results(results);
}

TermInfos TextIndexAccessor::get_term_infos(
    const std::string &term, bool testflag) const {

  std::ifstream file(
      path_ / "index" / "entries" / indexer::hashing_term(term, testflag));

  std::string term_entries;
  TermInfos term_infos;
  while (std::getline(file, term_entries)) {
    if (term_entries.empty()) {
      continue;
    }
    std::vector<std::string> list_terms = parser::delete_spaces(term_entries);
    const std::string word = list_terms[0];
    const size_t doc_frequency = std::stoi(list_terms[1]);
    size_t i = 2;
    while (i < list_terms.size()) {
      const size_t doc_id = std::stoi(list_terms[i]);
      i++;
      const size_t term_frequency = std::stoi(list_terms[i]);
      term_infos.entries_[word][doc_id].push_back(term_frequency);
      term_infos.entries_[word][doc_id].push_back(doc_frequency);
      i += term_frequency + 1;
    }
  }

  return term_infos;
}

std::string TextIndexAccessor::load_document(size_t document_id) const {
  std::string text;
  std::ifstream file(path_ / "index" / "docs" / std::to_string(document_id));
  std::getline(file, text);

  return text;
}

size_t TextIndexAccessor::total_docs() const {
  size_t total_docs = 0;
  std::ifstream file(path_ / "index" / "docs" / "total_docs");
  file >> total_docs;

  return total_docs;
}

Result sort_results(const std::map<size_t, double> &tmp_results) {
  Result sorted;
  for (const auto &[doc_id, score] : tmp_results) {
    sorted.results_.push_back({doc_id, score});
  }

  std::sort(
      sorted.results_.begin(),
      sorted.results_.end(),
      [](const IdScore &l, const IdScore &r) {
        if (l.score != r.score) {
          return l.score > r.score;
        }

        return l.doc_id > r.doc_id;
      });

  return sorted;
}

} // namespace searcher