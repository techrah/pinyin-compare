#include "gtest/gtest.h"
#include "test.h"

TEST(TestE, Test_CAP_LT) {
  ASSERT_LT(_pinyin_compare("E", CAP_E_MACRON), 0);
  ASSERT_LT(_pinyin_compare(CAP_E_MACRON, CAP_E_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(CAP_E_ACUTE, CAP_E_CARON), 0);
  ASSERT_LT(_pinyin_compare(CAP_E_CARON, CAP_E_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(CAP_E_GRAVE, "F"), 0);
}

TEST(TestE, Test_CAP_GT) {
  ASSERT_GT(_pinyin_compare("F", CAP_E_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(CAP_E_GRAVE, CAP_E_CARON), 0);
  ASSERT_GT(_pinyin_compare(CAP_E_CARON, CAP_E_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(CAP_E_ACUTE, CAP_E_MACRON), 0);
  ASSERT_GT(_pinyin_compare(CAP_E_MACRON, "E"), 0);
}

TEST(TestE, Test_SM_LT) {
  ASSERT_LT(_pinyin_compare("e", SM_E_MACRON), 0);
  ASSERT_LT(_pinyin_compare(SM_E_MACRON, SM_E_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(SM_E_ACUTE, SM_E_CARON), 0);
  ASSERT_LT(_pinyin_compare(SM_E_CARON, SM_E_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(SM_E_GRAVE, "f"), 0);
}

TEST(TestE, Test_SM_GT) {
  ASSERT_GT(_pinyin_compare("f", SM_E_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(SM_E_GRAVE, SM_E_CARON), 0);
  ASSERT_GT(_pinyin_compare(SM_E_CARON, SM_E_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(SM_E_ACUTE, SM_E_MACRON), 0);
  ASSERT_GT(_pinyin_compare(SM_E_MACRON, "e"), 0);
}
