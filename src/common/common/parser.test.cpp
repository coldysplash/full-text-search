#include <common/parser.hpp>
#include <gtest/gtest.h>
#include <iostream>

TEST(test_modify_text, parser_test) {
  std::string text =
      "WHEN YOU START SEEING YOUR WORTH, YOU'LL STOP SEEING PEOPLE WHO DON.T.";
  std::string expected_text =
      "when you start seeing your worth youll stop seeing people who dont";
  parser::normalize_text(text);
  ASSERT_EQ(text, expected_text);
}

TEST(test_delete_spaces, parser_test) {
  std::vector<std::string> list_strings;
  std::string text = "hello my name is tony";
  std::vector<std::string> expected_list_strings = {
      "hello", "my", "name", "is", "tony"};
  parser::delete_spaces(list_strings, text);
  ASSERT_EQ(list_strings, expected_list_strings);
}

TEST(test_delete_stop_words, parser_test) {
  std::vector<std::string> list_strings = {
      "hello", "and", "my", "name", "is", "a", "tony"};
  std::vector<std::string> expected_list_strings = {"hello", "name", "tony"};

  parser::ParserOpts parser_opts;
  parser_opts.ngram_min_length_ = 3;
  parser_opts.ngram_max_length_ = 6;
  parser_opts.stop_words_ = {"and", "my", "is", "a"};

  parser::delete_stop_words(list_strings, parser_opts);
  ASSERT_EQ(list_strings, expected_list_strings);
}

TEST(test_NgramParser, parser_test) {
  std::string text = "Dr. Jekyll and Mr. Hyde";

  parser::ParserOpts parser_opts;
  parser_opts.ngram_min_length_ = 3;
  parser_opts.ngram_max_length_ = 6;
  parser_opts.stop_words_ = {"and"};

  std::vector<std::vector<std::string>> ngram_words;

  parser::parse_text(text, ngram_words, parser_opts);
  std::vector<std::vector<std::string>> ngram_words_expected = {
      {"jek", "jeky", "jekyl", "jekyll"}, {"hyd", "hyde"}};
  ASSERT_EQ(ngram_words, ngram_words_expected);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}