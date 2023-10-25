#pragma once

#include <common/parser.hpp>

#include <filesystem>
#include <map>
#include <string>

namespace driver {

using fs_path = std::filesystem::path;

using ParsedCsvDoc = std::map<size_t, std::string>;

struct IndexConfig {
  fs_path path_to_csv_;
  fs_path path_to_index_;
  parser::ParserOpts parser_opts_;
};

ParsedCsvDoc parse_csv_file(const fs_path &path_to_csv);
void index_command(const IndexConfig &options);

} // namespace driver