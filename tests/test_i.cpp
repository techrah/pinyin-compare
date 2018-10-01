#include "gtest/gtest.h"
#include "test.h"

TEST(TestI, Test_CAP_LT) {
  ASSERT_LT(_pinyin_compare("H", CAP_I_MACRON), 0);
  ASSERT_LT(_pinyin_compare(CAP_I_MACRON, CAP_I_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(CAP_I_ACUTE, CAP_I_CARON), 0);
  ASSERT_LT(_pinyin_compare(CAP_I_CARON, CAP_I_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(CAP_I_GRAVE, "J"), 0);
}

TEST(TestI, Test_CAP_GT) {
  ASSERT_GT(_pinyin_compare("J", CAP_I_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(CAP_I_GRAVE, CAP_I_CARON), 0);
  ASSERT_GT(_pinyin_compare(CAP_I_CARON, CAP_I_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(CAP_I_ACUTE, CAP_I_MACRON), 0);
  ASSERT_GT(_pinyin_compare(CAP_I_MACRON, "H"), 0);
}

TEST(TestI, Test_SM_LT) {
  ASSERT_LT(_pinyin_compare("h", SM_I_MACRON), 0);
  ASSERT_LT(_pinyin_compare(SM_I_MACRON, SM_I_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(SM_I_ACUTE, SM_I_CARON), 0);
  ASSERT_LT(_pinyin_compare(SM_I_CARON, SM_I_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(SM_I_GRAVE, "j"), 0);
}

TEST(TestI, Test_SM_GT) {
  ASSERT_GT(_pinyin_compare("j", SM_I_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(SM_I_GRAVE, SM_I_CARON), 0);
  ASSERT_GT(_pinyin_compare(SM_I_CARON, SM_I_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(SM_I_ACUTE, SM_I_MACRON), 0);
  ASSERT_GT(_pinyin_compare(SM_I_MACRON, "h"), 0);
}
