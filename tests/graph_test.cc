#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "s21_graph.h"

class GraphTest : public ::testing::Test {
 protected:
  s21::Graph graph_test_;
};

TEST_F(GraphTest, LoadGraphFromFile_Success) {
  std::string filename = "../materials/examples/graph_1.txt";
  bool result = graph_test_.LoadGraphFromFile(filename);
  EXPECT_TRUE(result) << "Failed to load graph from file: " << filename;
}

TEST_F(GraphTest, LoadGraphFromFile_CheckNormalDimenssion) {
  std::string filename = "../materials/examples/graph_1.txt";
  graph_test_.LoadGraphFromFile(filename);
  auto result = graph_test_.GetGraph().GetRows();
  EXPECT_TRUE(result == 7);
}

TEST_F(GraphTest, LoadGraphFromFile_CheckInvalidDimenssion) {
  std::string filename = "../materials/examples/graph_2.txt";
  graph_test_.LoadGraphFromFile(filename);
  auto result = graph_test_.GetGraph().GetRows();
  EXPECT_TRUE(result == 8);
}

TEST_F(GraphTest, LoadGraphFromFile_CheckData) {
  std::vector data({0,  1, 2,  3, 4,  5,  6,  1,  0, 10, 20, 0,  0,
                    0,  2, 10, 0, 0,  50, 10, 0,  3, 20, 0,  0,  20,
                    33, 0, 4,  0, 50, 20, 0,  20, 2, 5,  0,  10, 33,
                    20, 0, 1,  6, 0,  0,  0,  2,  1, 0});
  graph_test_.LoadGraphFromFile("../materials/examples/graph_1.txt");
  s21::matrix<int> source_graph = graph_test_.GetGraph();
  for (size_t row = 0; row < graph_test_.GetGraph().GetRows(); ++row) {
    for (size_t col = 0; col < graph_test_.GetGraph().GetCols(); ++col) {
      EXPECT_TRUE(source_graph[row][col] ==
                  data[row * graph_test_.GetGraph().GetCols() + col])
          << "Incorrect value: " << source_graph[row][col] << " "
          << data[row * graph_test_.GetGraph().GetCols() + col];
    }
  }
}

TEST_F(GraphTest, LoadGraphFromFile_FileNotFound) {
  std::string filename = "non_existent_file.txt";
  bool result = graph_test_.LoadGraphFromFile(filename);
  EXPECT_FALSE(result) << "Expected failure for file not found: " << filename;
}

TEST_F(GraphTest, LoadGraphFromFile_InvalidData) {
  std::string filename = "invalid_graph.txt";
  bool result = graph_test_.LoadGraphFromFile(filename);
  EXPECT_FALSE(result) << "Expected failure for invalid data in file: "
                       << filename;
}
