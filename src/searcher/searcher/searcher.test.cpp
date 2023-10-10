#include <searcher/searcher.hpp>

#include <gtest/gtest.h>

#include <iostream>

TEST(test_search, Searcher_test) {

  std::filesystem::path path = ".";
  std::string q = "matrix revolutions";

  searcher::TextIndexAccessor accessor(path);
  searcher::search(q, accessor);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}