#include <gtest/gtest.h>

#include <vector>

#include "../graph_algorithms/s21_graph_algorithms.h"

class GraphAlgorithmsTest : public ::testing::Test {
 protected:
  GraphAlgorithmsTest() {
    graph_.LoadGraphFromFile("../materials/examples/graph_1.txt");
  }
  s21::Graph graph_;
};

TEST_F(GraphAlgorithmsTest, DepthFirstSearch_ValidStartVertex) {
  std::list<int> result = s21::GraphAlgorithms::DepthFirstSearch(graph_, 1);
  std::list<int> expected_result = {1, 3, 5, 6, 4, 2};
  EXPECT_EQ(result, expected_result);
}

TEST_F(GraphAlgorithmsTest, DepthFirstSearch_InvalidStartVertex) {
  std::list<int> result = s21::GraphAlgorithms::DepthFirstSearch(graph_, 0);
  std::list<int> expected_result = {};
  EXPECT_EQ(result, expected_result);
}

TEST_F(GraphAlgorithmsTest, BreadthFirstSearch_ValidStartVertex) {
  std::list<int> result = s21::GraphAlgorithms::BreadthFirstSearch(graph_, 1);
  std::list<int> expected_result = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(result, expected_result);
}

TEST_F(GraphAlgorithmsTest, BreadthFirstSearch_InvalidStartVertex) {
  std::list<int> result = s21::GraphAlgorithms::BreadthFirstSearch(graph_, 0);
  std::list<int> expected_result = {};
  EXPECT_EQ(result, expected_result);
}

TEST_F(GraphAlgorithmsTest, ShortestPathNormalCase) {
  int shortest_path =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph_, 1, 4);
  EXPECT_EQ(shortest_path, 40);
}

TEST_F(GraphAlgorithmsTest, OneVertex) {
  int shortest_path =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph_, 1, 1);
  EXPECT_EQ(shortest_path, 0);
}

TEST_F(GraphAlgorithmsTest, InvalidStartVertex) {
  int shortest_path =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph_, 100, 1);
  EXPECT_EQ(shortest_path, 0);
}

TEST_F(GraphAlgorithmsTest, InvalidEndVertex) {
  int shortest_path =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph_, 1, 100);
  EXPECT_EQ(shortest_path, 0);
}