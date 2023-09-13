#include <gtest/gtest.h>
#include <libfts/fts.hpp>

TEST(sum_two_numbers, test) {
  ASSERT_DOUBLE_EQ(fts::sum_two_numbers(10.4, 10.5), 20.9);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}