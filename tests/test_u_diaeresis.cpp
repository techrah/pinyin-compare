#include "gtest/gtest.h"
#include "test.h"

TEST(TestUDiaeresis, Test_CAP_LT) {
  ASSERT_LT(_pinyin_compare("U", CAP_U_DIAERESIS_MACRON), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_DIAERESIS_MACRON, CAP_U_DIAERESIS_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_DIAERESIS_ACUTE, CAP_U_DIAERESIS_CARON), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_DIAERESIS_CARON, CAP_U_DIAERESIS_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(CAP_U_DIAERESIS_GRAVE, "V"), 0);
}

TEST(TestUDiaeresis, Test_CAP_GT) {
  ASSERT_GT(_pinyin_compare("V", CAP_U_DIAERESIS_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_DIAERESIS_GRAVE, CAP_U_DIAERESIS_CARON), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_DIAERESIS_CARON, CAP_U_DIAERESIS_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_DIAERESIS_ACUTE, CAP_U_DIAERESIS_MACRON), 0);
  ASSERT_GT(_pinyin_compare(CAP_U_DIAERESIS_MACRON, "U"), 0);
}

TEST(TestUDiaeresis, Test_SM_LT) {
  ASSERT_LT(_pinyin_compare("u", SM_U_DIAERESIS_MACRON), 0);
  ASSERT_LT(_pinyin_compare(SM_U_DIAERESIS_MACRON, SM_U_DIAERESIS_ACUTE), 0);
  ASSERT_LT(_pinyin_compare(SM_U_DIAERESIS_ACUTE, SM_U_DIAERESIS_CARON), 0);
  ASSERT_LT(_pinyin_compare(SM_U_DIAERESIS_CARON, SM_U_DIAERESIS_GRAVE), 0);
  ASSERT_LT(_pinyin_compare(SM_U_DIAERESIS_GRAVE, "v"), 0);
}

TEST(TestUDiaeresis, Test_SM_GT) {
  ASSERT_GT(_pinyin_compare("v", SM_U_DIAERESIS_GRAVE), 0);
  ASSERT_GT(_pinyin_compare(SM_U_DIAERESIS_GRAVE, SM_U_DIAERESIS_CARON), 0);
  ASSERT_GT(_pinyin_compare(SM_U_DIAERESIS_CARON, SM_U_DIAERESIS_ACUTE), 0);
  ASSERT_GT(_pinyin_compare(SM_U_DIAERESIS_ACUTE, SM_U_DIAERESIS_MACRON), 0);
  ASSERT_GT(_pinyin_compare(SM_U_DIAERESIS_MACRON, "u"), 0);
}
