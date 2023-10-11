#include <common/parser.hpp>
#include <searcher/searcher.hpp>

#include <gtest/gtest.h>

#include <iostream>

TEST(test_search, Searcher_test) {

  parser::ParserOpts parse_opts;
  parse_opts.stop_words_ = {"the"};

  std::filesystem::path path = ".";
  std::string q = "Hello world";

  searcher::TextIndexAccessor accessor(path, parse_opts);
  searcher::search(q, accessor);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}