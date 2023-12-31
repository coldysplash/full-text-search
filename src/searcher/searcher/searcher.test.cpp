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
  indexer::TextIndexWriter docs;
  const std::filesystem::path path = "./searchtests";
  docs.write(path, doc_index, false);

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_search, Searcher_test) {
  parser::ParserOpts parser_opts;
  const std::filesystem::path path = "./searchtests";
  const std::string query = "World";
  const searcher::TextIndexAccessor accessor(path, parser_opts);
  const searcher::Result result = searcher::search(query, accessor);
}

TEST(test_get_term_infos, TextIndexAccessor) {
  const std::filesystem::path path = "./indextest";
  std::filesystem::create_directories(path);
  parser::ParserOpts parser_opts;
  indexer::IndexBuilder index(parser_opts);
  index.add_document(100, "World");
  const indexer::Index doc_index = index.index();
  indexer::TextIndexWriter w;
  w.write(path, doc_index, true);

  const searcher::TextIndexAccessor a(path, parser_opts);
  const std::string term = "world";
  searcher::TermInfos terminfos;
  terminfos = a.get_term_infos(term, true);
  std::string term_infos_exit;
  for (const auto &[key, val] : terminfos.entries_) {
    term_infos_exit.append(key).append(" ");
    for (const auto &[k, v] : val) {
      term_infos_exit.append(std::to_string(k)).append(" ");
      for (const auto &i : v) {
        term_infos_exit.append(std::to_string(i)).append(" ");
      }
    }
  }
  std::string terminfos_expected = "wor 100 1 1 worl 100 1 1 world 100 1 1 ";
  ASSERT_EQ(term_infos_exit, terminfos_expected);
  std::uintmax_t n{std::filesystem::remove_all(path)};
}

TEST(test_load_document, TextIndexAccessor) {
  const std::filesystem::path path = "./searchtests";
  parser::ParserOpts parser_opts;
  const searcher::TextIndexAccessor a(path, parser_opts);
  std::string document = a.load_document(100);
  std::string document_expected = "Hello World";
  ASSERT_EQ(document, document_expected);
}

TEST(test_total_docs, TextIndexAccessor) {
  const std::filesystem::path path = "./searchtests";
  parser::ParserOpts parser_opts;
  const searcher::TextIndexAccessor a(path, parser_opts);

  size_t total_docs = a.total_docs();
  size_t total_docs_expected = 2;
  ASSERT_EQ(total_docs, total_docs_expected);
}