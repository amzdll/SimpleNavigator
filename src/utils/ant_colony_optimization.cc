
#include "ant_colony_optimization.h"

#include <utility>

#include "iostream"

namespace s21 {
Colony::Colony(matrix<int> adjacency_matrix)
    : adjacency_matrix_(std::move(adjacency_matrix)) {}

void Colony::InitializeColony() {
  for (int row = 0, col = 1; col < adjacency_matrix_.GetRows(); ++col) {
    colony_.emplace_back(adjacency_matrix_, adjacency_matrix_[row][col]);
  }
}

void Colony::BypassColony() {
  for (auto ant : colony_) {
    ant.Bypass(adjacency_matrix_);
  }
}

void Ant::Bypass(const matrix<int>& adjacency_matrix) {
  int position = start_position_;
  int number_of_vertices = adjacency_matrix.GetRows() - 1;

  visited_vertices_.insert(start_position_);
  while (visited_vertices_.size() < number_of_vertices) {
    for (int col = 1; col < adjacency_matrix.GetCols(); ++col) {
      if (adjacency_matrix[position][col] &&
          visited_vertices_.find(col) == visited_vertices_.end()) {
        visited_vertices_.insert(col);
        position = col;
        break;
      }
    }
  }
  for (auto visit : visited_vertices_) {
    std::cout << visit << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21

int main() {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "/Users/glenpoin/W/Projects/Algorithms/SimpleNavigator/materials/"
      "examples/graph_1.txt");
  s21::Colony ac(graph.GetGraph());
  ac.InitializeColony();
  ac.BypassColony();
}