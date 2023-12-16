
#include "ant_colony_optimization.h"

#include <random>
#include <utility>

#include "iostream"
#include "unordered_map"

namespace s21 {
Colony::Colony(matrix<float> adjacency_matrix)
    : adjacency_matrix_(std::move(adjacency_matrix)) {
  global_pheromones_matrix_ =
      matrix(adjacency_matrix_.GetRows(), adjacency_matrix_.GetCols(), 1.f);
  colony_configuration_.pheromon =
      float(local_pheromones_matrix_.GetRows() - 1);
  colony_configuration_.evaporation_rate = 3.5;
}

void Colony::BypassColony() {
  EvaporatePheromones();
  local_pheromones_matrix_ = global_pheromones_matrix_;
  //  matrix<float> temp_graph = global_pheromones_matrix_;
  //  for (int row = 1; row < global_pheromones_matrix_.GetRows(); ++row) {
  //    AntBypass(row);
  //
  //    for (int i = 1; i < temp_graph.GetRows(); ++i) {
  //      for (int j = 1; j < temp_graph.GetCols(); ++j) {
  //        temp_graph[i][j] += local_pheromones_matrix_[i][j];
  //      }
  //    }
  //    break;
  //  }
  tsm_result_.pheromones = global_pheromones_matrix_;
}

void Colony::EvaporatePheromones() const {
  for (int i = 1; i < global_pheromones_matrix_.GetRows(); ++i) {
    for (int j = 1; j < global_pheromones_matrix_.GetCols(); ++j) {
      global_pheromones_matrix_[i][j] *= colony_configuration_.evaporation_rate;
    }
  }
}

void Colony::AntBypass(int start_position) {
  std::map<float, float> visited_vertices;
  std::vector<float> cost_vertices;
  float path_cost = 0;
  float partial_sum = 0;

  for (int row = start_position, col = 1;
       col < local_pheromones_matrix_.GetCols(); ++col) {
    if (adjacency_matrix_[row][col] != 0 &&
        !visited_vertices.count(adjacency_matrix_[row][col])) {
      visited_vertices.insert({col, adjacency_matrix_[row][col]});
      path_cost += adjacency_matrix_[row][col];
    }
  }

  for (const auto vertex : visited_vertices) {
    cost_vertices.emplace_back(vertex.second / path_cost + partial_sum);
    partial_sum += vertex.second / path_cost;
  }

  for (const auto vertex : cost_vertices) {
    std::cout << vertex << " ";
  }
}

GraphAlgorithms::TsmResult Colony::GetResult() { return tsm_result_; }

}  // namespace s21
// namespace s21

// int main() {
//   s21::Graph graph;
//   //  graph.LoadGraphFromFile(
//   //      "/Users/glenpoin/W/Projects/Algorithms/SimpleNavigator/materials/"
//   //      "examples/graph_1.txt");
//   graph.LoadGraphFromFile(
//       "/home/freiqq/Projects/Algorithms/SimpleNavigator/materials/examples/"
//       "graph_1.txt");
//
//   s21::Colony ac(graph.GetGraph());
//   //  ac.InitializeColony();
//     ac.BypassColony();
////  ac.EvaporatePheromones();
//}
