#include <searcher-c/searcher-c.h>

#include <common/parser.hpp>
#include <searcher/searcher.hpp>

#include <fstream>
#include <iostream>

Json *fts_create_json(const char *path) {
  auto *config = new parser::ParserOpts(parser::parse_config(path));
  return reinterpret_cast<Json *>(config);
}

void fts_delete_json(Json *config) {
  delete reinterpret_cast<parser::ParserOpts *>(config);
}

SearcherHandle *fts_create_searcher(const char *path, Json *config) {
  return reinterpret_cast<SearcherHandle *>(
      static_cast<searcher::IndexAccessor *>(new searcher::TextIndexAccessor(
          path, *reinterpret_cast<parser::ParserOpts *>(config))));
}

void fts_delete_searcher(SearcherHandle *handle) {
  delete reinterpret_cast<searcher::IndexAccessor *>(handle);
}

Results *fts_search(const char *query, const SearcherHandle *handle) {
  auto accessor = *(dynamic_cast<const searcher::TextIndexAccessor *>(
      reinterpret_cast<const searcher::IndexAccessor *>(handle)));

  const auto results = searcher::search(query, accessor);

  return reinterpret_cast<Results *>(new searcher::Result(results));
}

void fts_print_result(const SearcherHandle *handle, const Results *result) {
  const auto results = *reinterpret_cast<const searcher::Result *>(result);
  auto accessor = *(dynamic_cast<const searcher::TextIndexAccessor *>(
      reinterpret_cast<const searcher::IndexAccessor *>(handle)));

  for (const auto &[doc_id, score] : results.results_) {
    auto str = accessor.load_document(doc_id);
    std::cout << doc_id << ' ' << score << ' ' << str << '\n';
  }
  std::cout << std::endl;
}

void fts_delete_results(Results *results) {
  delete reinterpret_cast<searcher::Result *>(results);
}