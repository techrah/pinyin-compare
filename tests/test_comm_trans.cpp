#include "gtest/gtest.h"
#include "test.h"

TEST(TEST1, TEST1) {
  test_commutative_eq("YÚAN", "yúan");
  test_transitive_eq("YÚAN", "Yúan", "yúan");
  test_commutative_compare("aì", "ɡuǎn");
  test_transitive_compare("aì", "ɡuǎn", "zi");
}
