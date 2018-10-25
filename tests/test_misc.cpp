#include "gtest/gtest.h"
#include "test.h"

TEST(TestMisc, TestHomonymPrefixes) {
  ASSERT_LT(_pinyin_compare("⁰shí", "¹shí"), 0);
  ASSERT_LT(_pinyin_compare("¹shí", "²shí"), 0);
  ASSERT_LT(_pinyin_compare("²shí", "³shí"), 0);
  ASSERT_LT(_pinyin_compare("³shí", "⁴shí"), 0);
  ASSERT_LT(_pinyin_compare("⁴shí", "⁵shí"), 0);
  ASSERT_LT(_pinyin_compare("⁵shí", "⁶shí"), 0);
  ASSERT_LT(_pinyin_compare("⁶shí", "⁷shí"), 0);
  ASSERT_LT(_pinyin_compare("⁷shí", "⁸shí"), 0);
  ASSERT_LT(_pinyin_compare("⁸shí", "⁹shí"), 0);
  ASSERT_LT(_pinyin_compare("⁹shí", "¹⁰shí"), 0);
  ASSERT_LT(_pinyin_compare("¹⁰shí", "¹¹shí"), 0);
  ASSERT_LT(_pinyin_compare("¹⁰shí", "¹²shí"), 0);

  // Test against words with no prefix
  ASSERT_LT(_pinyin_compare("⁰a", "b"), 0);
  ASSERT_LT(_pinyin_compare("b", "⁰c"), 0);
}

TEST(TestMisc, TestDash) {
  ASSERT_EQ(_pinyin_compare("yǒu-xié", "yǒuxié"), 0);
}

TEST(TestMisc, TestToneVsNoTone) {
  ASSERT_EQ(_pinyin_compare("wucai", "wǔcǎi*"), 0);
}

TEST(TestMisc, TestOneOneMarker) {
  ASSERT_EQ(_pinyin_compare("bụ̀duì", "bùduì"), 0);
}

TEST(TestMisc, TestTwoThreeMarker) {
  ASSERT_EQ(_pinyin_compare("wǔcǎi", "wụ̌cǎi"), 0);
}

TEST(TestMisc, TestApostrophe) {
  ASSERT_EQ(_pinyin_compare("Xī'ān", "xīān"), 0);
}

TEST(TestMisc, TestUppercase) {
  ASSERT_EQ(_pinyin_compare("XIAN", "xian"), 0);
  ASSERT_EQ(_pinyin_compare("E", "e"), 0);
  ASSERT_EQ(_pinyin_compare("OU", "ou"), 0);
  ASSERT_EQ(_pinyin_compare("PINYIN", "pInYiN"), 0);
  ASSERT_LT(_pinyin_compare("XIAN", "xuan"), 0);
  ASSERT_GT(_pinyin_compare("xuan", "XI"), 0);
}

TEST(TestMisc, TestUmlaut) {
  // When words are equal, u < ü
  ASSERT_LT(_pinyin_compare("nù", "nǚ"), 0);

  // When words are not equal, umlaut doesn't matter
  ASSERT_LT(_pinyin_compare("lǚ", "luguan"), 0);
  ASSERT_LT(_pinyin_compare("nǜ", "nuǎn"), 0);
}

TEST(TestMisc, TestAutoStrLen) {
  ASSERT_LT(pinyin_compare(NULL, 4, "abcde", 5, "abcde"), 0);
  ASSERT_GT(pinyin_compare(NULL, 5, "abcde", 4, "abcde"), 0);
  ASSERT_EQ(pinyin_compare(NULL, 5, "abcde", -1, "abcde"), 0);
  ASSERT_EQ(pinyin_compare(NULL, -1, "abcde", 5, "abcde"), 0);
  ASSERT_EQ(pinyin_compare(NULL, -1, "abcde", -1, "abcde"), 0);
}
