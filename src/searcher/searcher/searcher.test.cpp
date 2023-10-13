#include <common/parser.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <gtest/gtest.h>

#include <iostream>

TEST(test_search, Searcher_test) {

  // parser::ParserOpts parse_opts;
  // parse_opts.stop_words_ = {"the"};

  // std::filesystem::path path = ".";
  // std::string q = "Hello world";

  // searcher::TextIndexAccessor accessor(path, parse_opts);
  // searcher::search(q, accessor);
}

TEST(test_get_term_infos, TextIndexAccessor) {
  // parser::ParserOpts parser_opts;
  // indexer::IndexBuilder index(parser_opts);
  // index.add_document(100, "Hell");
  // const indexer::Index doc_index = index.index();
  // indexer::TextIndexWriter w;
  // const std::filesystem::path path = ".";
  // w.write(path, doc_index);

  // searcher::TextIndexAccessor a(path, parser_opts);
  // const std::string term = "hel";
  // a.get_term_infos(term);
  //   for (const auto &[key, val] : term_infos_.entries_) {
  //   std::cout << key << ' ';
  //   for (const auto &[k, v] : val) {
  //     std::cout << k << ' ';
  //     for (const auto &i : v) {
  //       std::cout << i << ' ';
  //     }
  //   }
  //   std::cout << '\n';
  // }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}