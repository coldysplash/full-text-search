#include <common/parser.hpp>
#include <indexer/indexer.hpp>
#include <searcher/searcher.hpp>

#include <gtest/gtest.h>

int main(int argc, char **argv) {
  parser::ParserOpts parser_opts;
  indexer::IndexBuilder index(parser_opts);
  index.add_document(100, "Hello World");
  index.add_document(102, "Hello Earth");
  const indexer::Index doc_index = index.index();
  indexer::TextIndexWriter w;
  const std::filesystem::path path = ".";
  w.write(path, doc_index);

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_search, Searcher_test) {
  parser::ParserOpts parser_opts;
  const std::filesystem::path path = ".";
  const std::string query = "World";
  searcher::TextIndexAccessor accessor(path, parser_opts);
  const searcher::Result result = searcher::search(query, accessor);
}

TEST(test_get_term_infos, TextIndexAccessor) {
  // const std::filesystem::path path = ".";
  // parser::ParserOpts parser_opts;

  // searcher::TextIndexAccessor a(path, parser_opts);
  // const std::string term = "wor";
  // searcher::TermInfos terminfos;
  // terminfos = a.get_term_infos(term);
  // std::string term_infos_exit;
  // for (const auto &[key, val] : terminfos.entries_) {
  //   term_infos_exit.append(key);
  //   for (const auto &[k, v] : val) {
  //     term_infos_exit.append(std::to_string(k));
  //     for (const auto &i : v) {
  //       term_infos_exit.append(std::to_string(i));
  //     }
  //   }
  // }
  // std::cout << term_infos_exit;
  // std::string terminfos_expected = "wor10011";
  // ASSERT_EQ(term_infos_exit, terminfos_expected);
}

TEST(test_load_document, TextIndexAccessor) {
  const std::filesystem::path path = ".";
  parser::ParserOpts parser_opts;
  searcher::TextIndexAccessor a(path, parser_opts);
  std::string document = a.load_document(100);
  std::string document_expected = "Hello World";
  ASSERT_EQ(document, document_expected);
}

TEST(test_total_docs, TextIndexAccessor) {
  const std::filesystem::path path = ".";
  parser::ParserOpts parser_opts;
  searcher::TextIndexAccessor a(path, parser_opts);

  size_t total_docs = a.total_docs();
  size_t total_docs_expected = 2;
  ASSERT_EQ(total_docs, total_docs_expected);
}