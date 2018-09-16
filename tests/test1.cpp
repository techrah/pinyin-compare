#include <string.h>
#include "gtest/gtest.h"
#include "../src/pinyin_compare.h"

TEST(VowelTest, ATone1) {
  const char *s1 = "a";
  const char *s2 = "ā";
  int res = pinyin_compare(0, strlen(s1), s1, strlen(s2), s2);
  ASSERT_LT(res, 0);
}

TEST(VowelTest, ATone2) {
  const char *s1 = "ā";
  const char *s2 = "á";
  int res = pinyin_compare(0, strlen(s1), s1, strlen(s2), s2);
  ASSERT_LT(res, 0);
}
