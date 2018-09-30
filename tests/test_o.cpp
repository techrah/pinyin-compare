#include "gtest/gtest.h"
#include "test.h"

TEST(TestO, Test_CAP_LT) {
  ASSERT_LT(_pinyin_compare("N", CAP_O_MACRON), 0);
  ASSERT_LT(_pinyin_compare(CAP_O_MACRON, CAP_O_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(CAP_O_ACUTE, CAP_O_CARON), 0);
  ASSERT_LT(_pinyin_compare(CAP_O_CARON, CAP_O_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(CAP_O_GRAVE, "P"), 0);
}

TEST(TestO, Test_CAP_GT) {
  ASSERT_GT(_pinyin_compare("P", CAP_O_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(CAP_O_GRAVE, CAP_O_CARON), 0);
  ASSERT_GT(_pinyin_compare(CAP_O_CARON, CAP_O_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(CAP_O_ACUTE, CAP_O_MACRON), 0);
  ASSERT_GT(_pinyin_compare(CAP_O_MACRON, "N"), 0);
}

TEST(TestO, Test_SM_LT) {
  ASSERT_LT(_pinyin_compare("n", SM_O_MACRON), 0);
  ASSERT_LT(_pinyin_compare(SM_O_MACRON, SM_O_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(SM_O_ACUTE, SM_O_CARON), 0);
  ASSERT_LT(_pinyin_compare(SM_O_CARON, SM_O_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(SM_O_GRAVE, "p"), 0);
}

TEST(TestO, Test_SM_GT) {
  ASSERT_GT(_pinyin_compare("p", SM_O_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(SM_O_GRAVE, SM_O_CARON), 0);
  ASSERT_GT(_pinyin_compare(SM_O_CARON, SM_O_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(SM_O_ACUTE, SM_O_MACRON), 0);
  ASSERT_GT(_pinyin_compare(SM_O_MACRON, "n"), 0);
}
