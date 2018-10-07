#include "gtest/gtest.h"
#include "test.h"

// https://www.sqlite.org/c3ref/create_collation.html

void test_commutative_eq(const char *s1, const char *s2) {
  ASSERT_EQ(_pinyin_compare(s1, s2), _pinyin_compare(s2, s1));
}

void test_transitive_eq(const char *s1, const char *s2, const char *s3) {
  const int r1 = _pinyin_compare(s1, s2);
  const int r2 = _pinyin_compare(s2, s3);
  ASSERT_EQ(r1, r2);
}

void test_transitive_lt(const char *s1, const char *s2, const char *s3) {
  const int r1 = _pinyin_compare(s1, s2);
  const int r2 = _pinyin_compare(s2, s3);
  ASSERT_LT(r1, r2);
}

void test_commutative_compare(const char *s1, const char *s2) {
  const int r1 = _pinyin_compare(s1, s2);
  const int r2 = _pinyin_compare(s2, s1);
  if (r1 < 0) ASSERT_GT(r2, 0);
  if (r1 > 0) ASSERT_LT(r2, 0);
}

void test_transitive_compare(const char *s1, const char *s2, const char *s3) {
  const int r1 = _pinyin_compare(s1, s2);
  const int r2 = _pinyin_compare(s2, s3);
  const int r3 = _pinyin_compare(s1, s3);
  ASSERT_LT(r1, 0);
  ASSERT_LT(r2, 0);
  ASSERT_LT(r3, 0);
}
