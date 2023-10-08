#include <common/parser.hpp>
#include <searcher/searcher.hpp>

#include <string>
#include <vector>

Result search(std::string query, IndexAccessor &index_accessor) {
  std::vector<std::vector<std::string>> terms;
  parser::parse_text(query, terms, index_accessor.config);
}

Config TextIndexAccessor::config() const { return config; }