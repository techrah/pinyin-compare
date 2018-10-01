#include "gtest/gtest.h"
#include "test.h"

TEST(TestU, Test_CAP_LT) {
  ASSERT_LT(_pinyin_compare("T", CAP_U_MACRON), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_MACRON, CAP_U_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_ACUTE, CAP_U_CARON), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_CARON, CAP_U_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_GRAVE, "V"), 0);
}

TEST(TestU, Test_CAP_GT) {
  ASSERT_GT(_pinyin_compare("V", CAP_U_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_GRAVE, CAP_U_CARON), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_CARON, CAP_U_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_ACUTE, CAP_U_MACRON), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_MACRON, "T"), 0);
}

TEST(TestU, Test_SM_LT) {
  ASSERT_LT(_pinyin_compare("t", SM_U_MACRON), 0);
  ASSERT_LT(_pinyin_compare(SM_U_MACRON, SM_U_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(SM_U_ACUTE, SM_U_CARON), 0);
  ASSERT_LT(_pinyin_compare(SM_U_CARON, SM_U_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(SM_U_GRAVE, "v"), 0);
}

TEST(TestU, Test_SM_GT) {
  ASSERT_GT(_pinyin_compare("v", SM_U_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(SM_U_GRAVE, SM_U_CARON), 0);
  ASSERT_GT(_pinyin_compare(SM_U_CARON, SM_U_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(SM_U_ACUTE, SM_U_MACRON), 0);
  ASSERT_GT(_pinyin_compare(SM_U_MACRON, "t"), 0);
}
