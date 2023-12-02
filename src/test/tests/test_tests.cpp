#include <gtest/gtest.h>

#include <Window.h>


TEST(Test, BasicTest) {
  gol::Window a(200, 200);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}