#include "gtest/gtest.h"
#include "../src/pinyin_compare.h"

__inline int _latin_compare(const char *s1, const char* s2) {
  return latin_compare(0, strlen(s1), s1, strlen(s2), s2);
}

TEST(TestLatinCommpare, TestEq) {
  ASSERT_EQ(_latin_compare("This", "this"), 0);
  ASSERT_EQ(_latin_compare("Ça", "ÇA"), 0);

  // For this library, accents don't matter for sorting
  // even if the meaning changes completely
  ASSERT_EQ(_latin_compare("fermé", "ferme"), 0);
}

TEST(TestLatinCommpare, TestOrder) {
  ASSERT_LT(_latin_compare("a", "b"), 0);
  ASSERT_LT(_latin_compare("d", "é"), 0);
  ASSERT_LT(_latin_compare("these", "this"), 0);

  ASSERT_GT(_latin_compare("z", "y"), 0);
}
