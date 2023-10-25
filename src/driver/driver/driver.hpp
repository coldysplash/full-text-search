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

void index_command(const IndexConfig &options);

class SearchCommand {
private:
  fs_path path_;
  parser::ParserOpts parses_opts_;

public:
  SearchCommand(fs_path path_to_index, parser::ParserOpts parser_opts)
      : path_(path_to_index), parses_opts_(parser_opts) {}

  void search_and_print(const std::string &query) const;
};

} // namespace driver