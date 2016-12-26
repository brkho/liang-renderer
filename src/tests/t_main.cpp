// The main entry point of the Liang Renderer test suite. This runs all tests.
//
// Author: brian@brkho.com

#include <gtest/gtest.h>

// Run all the tests.
GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
