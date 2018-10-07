#include "gtest/gtest.h"
#include "test.h"

TEST(TestCommTrans, TestEq) {
  test_commutative_eq("YÚAN", "yúan");
  test_transitive_eq("YÚAN", "Yúan", "yúan");
}

TEST(TestCommTrans, TestCommCompare) {
  static const char * data[] = {
    "guānguāng",
    "xī'an",
    "kǒuyu",
    "gōngxīnzhàn",
    "guānguó",
    "xiǎn"
  };
  const int len = sizeof(data) / sizeof(*data) - 1;
  for (int i = 0; i < len; i++)
    test_commutative_compare(data[i], data[i + 1]);
}

TEST(TestCommTrans, TestTransCompare) {
  static const char * data[][3] = {
    {"aì", "ɡuǎn", "zi"},
    {"gōngxīnzhàn", "kǒuyu", "xī'an"}
  };
  const int len = sizeof(data) / sizeof(*data);
  for (int i = 0; i < len; i++)
    test_transitive_compare(data[i][0], data[i][1], data[i][2]);
}
