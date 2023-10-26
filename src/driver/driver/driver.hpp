#pragma once

#include <common/parser.hpp>
#include <searcher/searcher.hpp>

#include <CLI/CLI.hpp>

#include <filesystem>
#include <map>
#include <string>

namespace driver {

using fs_path = std::filesystem::path;

struct IndexConfig {
  fs_path path_to_csv_;
  fs_path path_to_index_;
  parser::ParserOpts parser_opts_;
};

struct SearchConfig {
  fs_path path_to_index_;
  std::string query_;
  parser::ParserOpts parser_opts_;
};

void index_build_and_write(const IndexConfig &options);
void print_search_result(
    const searcher::Result &result, const searcher::IndexAccessor &accessor);
void search_and_print(const SearchConfig &options);

CLI::App *create_indexer(CLI::App &app, IndexConfig &options);
CLI::App *create_searcher(CLI::App &app, SearchConfig &options);

} // namespace driver