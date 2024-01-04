
#include "ant_colony_optimization.h"

#include <random>
#include <utility>
#include <numeric>

#include "iostream"
#include "unordered_map"

namespace s21 {
Colony::Colony(matrix<float> adjacency_matrix)
    : adjacency_matrix_(std::move(adjacency_matrix)) {
  global_pheromones_matrix_ = matrix<float>(adjacency_matrix_.GetRows(), adjacency_matrix_.GetCols());
  for (int row = 1; row < adjacency_matrix_.GetRows(); ++row) {
    for (int col = 1; col < adjacency_matrix_.GetCols(); ++col) {
      global_pheromones_matrix_[row][col] =
          adjacency_matrix_[row][col] != 0.0 ? 1.f : 0;
    }
  }


  // temp
//  for (int row = 1, col = 0; row < adjacency_matrix_.GetCols(); ++row) {
//    global_pheromones_matrix_[row][col] = adjacency_matrix_[row][col];
//  }
//
//  for (int row = 0, col = 1; col < adjacency_matrix_.GetCols(); ++col) {
//    global_pheromones_matrix_[row][col] = adjacency_matrix_[row][col];
//  }

  colony_configuration_.pheromon = float(local_pheromones_matrix_.GetRows() - 1);
  colony_configuration_.evaporation_rate = 0.5;
}

void Colony::BypassColony() {
  EvaporatePheromones();
  PrintMatrix(global_pheromones_matrix_);
  local_pheromones_matrix_ = global_pheromones_matrix_;
  matrix<float> change_matrix =  ;
  AntBypass(1);
//    for (int row = 1; row < global_pheromones_matrix_.GetRows(); ++row) {
//      AntBypass(row);
//      for (int i = 1; i < change_matrix.GetRows(); ++i) {
//        for (int j = 1; j < change_matrix.GetCols(); ++j) {
//          change_matrix[i][j] += local_pheromones_matrix_[i][j];
//        }
//      }
//    }
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
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(0.0, 1.0);
  double random_float = dis(gen);
  for (int row = start_position, col = 1; col < adjacency_matrix_.GetCols(); ++col) {
    if (adjacency_matrix_[row][col] != 0 && !visited_vertices.count(adjacency_matrix_[row][col])) {
      visited_vertices.insert({col, adjacency_matrix_[row][col]});
      path_cost += adjacency_matrix_[row][col];
    }
  }

  for (const auto vertex : visited_vertices) {
    cost_vertices.emplace_back(vertex.second / path_cost + partial_sum);
    partial_sum += vertex.second / path_cost;
  }

  for (const auto vertex : cost_vertices) {
    std::cout << vertex << std::endl;
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
