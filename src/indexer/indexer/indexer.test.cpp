#include <common/parser.hpp>
#include <indexer/indexer.hpp>

#include <gtest/gtest.h>

#include <iostream>

TEST(test_add_document, IndexBuilder_test) {

  parser::ParserOpts parser_opts;
  parser_opts.ngram_min_length_ = 3;
  parser_opts.ngram_max_length_ = 6;
  parser_opts.stop_words_ = {"the"};

  indexer::IndexBuilder index(parser_opts);
  index.add_document(100, "The Matrix matrix");
  index.add_document(101, "The Matrix Reloaded");

  indexer::Index doci = index.index();

  indexer::Index doci_expected;
  doci_expected.docs = {
      {100, "The Matrix matrix"}, {101, "The Matrix Reloaded"}};

  doci_expected.entries = {
      {"mat", {{100, {0, 1}}, {101, {0}}}},
      {"matr", {{100, {0, 1}}, {101, {0}}}},
      {"matri", {{100, {0, 1}}, {101, {0}}}},
      {"matrix", {{100, {0, 1}}, {101, {0}}}},
      {"rel", {{101, {1}}}},
      {"relo", {{101, {1}}}},
      {"reloa", {{101, {1}}}},
      {"reload", {{101, {1}}}}};

  ASSERT_EQ(doci.docs, doci_expected.docs);
  ASSERT_EQ(doci.entries, doci_expected.entries);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}