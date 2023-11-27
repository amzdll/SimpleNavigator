#include "graph_test.cc"
#include "graph_algorithms_test.cc"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
