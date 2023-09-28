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
  const std::unordered_set<std::string> stop_words = {"and", "a", "is"};
  std::vector<std::string> expected_list_strings = {"hello", "name", "tony"};
  uint16_t ngram_min_length = 3;
  parser::delete_stop_words(list_strings, stop_words, ngram_min_length);
  ASSERT_EQ(list_strings, expected_list_strings);
}

TEST(test_NgramParser, parser_test) {
  std::string text = "Dr. Jekyll and Mr. Hyde";
  const std::unordered_set<std::string> stop_words = {
      "a",     "an",    "and",  "are",  "as", "at",   "be",   "but",   "by",
      "for",   "if",    "in",   "into", "is", "it",   "no",   "not",   "of",
      "on",    "or",    "s",    "such", "t",  "that", "the",  "their", "then",
      "there", "these", "they", "this", "to", "was",  "will", "with"};
  uint16_t ngram_min_length = 3;
  uint16_t ngram_max_length = 6;

  std::vector<std::vector<std::string>> ngram_words;

  parser::parse_text(
      text, stop_words, ngram_words, ngram_min_length, ngram_max_length);
  std::vector<std::vector<std::string>> ngram_words_expected = {
      {"jek", "jeky", "jekyl", "jekyll"}, {"hyd", "hyde"}};
  ASSERT_EQ(ngram_words, ngram_words_expected);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}