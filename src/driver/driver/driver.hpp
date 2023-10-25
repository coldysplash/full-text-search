#pragma once

#include <common/parser.hpp>

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
void search_and_print(const SearchConfig &options);

} // namespace driver