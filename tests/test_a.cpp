#include "gtest/gtest.h"
#include "test.h"

TEST(TestA, Test_CAP_LT) {
  ASSERT_LT(_pinyin_compare("A", CAP_A_MACRON), 0);
  ASSERT_LT(_pinyin_compare(CAP_A_MACRON, CAP_A_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(CAP_A_ACUTE, CAP_A_CARON), 0);
  ASSERT_LT(_pinyin_compare(CAP_A_CARON, CAP_A_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(CAP_A_GRAVE, "B"), 0);
}

TEST(TestA, Test_CAP_GT) {
  ASSERT_GT(_pinyin_compare("B", CAP_A_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(CAP_A_GRAVE, CAP_A_CARON), 0);
  ASSERT_GT(_pinyin_compare(CAP_A_CARON, CAP_A_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(CAP_A_ACUTE, CAP_A_MACRON), 0);
  ASSERT_GT(_pinyin_compare(CAP_A_MACRON, "A"), 0);
}

TEST(TestA, Test_SM_LT) {
  ASSERT_LT(_pinyin_compare("a", SM_A_MACRON), 0);
  ASSERT_LT(_pinyin_compare(SM_A_MACRON, SM_A_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(SM_A_ACUTE, SM_A_CARON), 0);
  ASSERT_LT(_pinyin_compare(SM_A_CARON, SM_A_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(SM_A_GRAVE, "b"), 0);
}

TEST(TestA, Test_SM_GT) {
  ASSERT_GT(_pinyin_compare("b", SM_A_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(SM_A_GRAVE, SM_A_CARON), 0);
  ASSERT_GT(_pinyin_compare(SM_A_CARON, SM_A_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(SM_A_ACUTE, SM_A_MACRON), 0);
  ASSERT_GT(_pinyin_compare(SM_A_MACRON, "a"), 0);
}
