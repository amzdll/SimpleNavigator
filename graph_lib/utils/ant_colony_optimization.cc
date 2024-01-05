
#include "ant_colony_optimization.h"

#include <numeric>
#include <random>
#include <utility>

#include "iostream"
#include "unordered_map"

/*
 * инициализация муравьев
 * проход муравья
 * испарения феромона = const / длину маршрута
 * */

namespace s21 {
AntColonyOptimization::AntColonyOptimization(matrix<float> adjacency_matrix)
    : adjacency_matrix_(std::move(adjacency_matrix)) {
  global_pheromones_matrix_ =
      matrix<float>(adjacency_matrix_.GetRows(), adjacency_matrix_.GetCols());
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

  colony_configuration_.pheromone =
      float(local_pheromones_matrix_.GetRows() - 1);
  colony_configuration_.evaporation_rate = 0.5;
}

void AntColonyOptimization::BypassColony() {
  EvaporatePheromones();
  //  PrintMatrix(global_pheromones_matrix_);
  //  local_pheromones_matrix_ = global_pheromones_matrix_;
  //  matrix<float> change_matrix =  ;
  AntBypass(Ant(1));
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

void AntColonyOptimization::EvaporatePheromones() const {
  for (int i = 1; i < global_pheromones_matrix_.GetRows(); ++i) {
    for (int j = 1; j < global_pheromones_matrix_.GetCols(); ++j) {
      global_pheromones_matrix_[i][j] *= colony_configuration_.evaporation_rate;
    }
  }
}

std::vector<std::pair<float, float>>
AntColonyOptimization::AccessAvailableVertices(const Ant& ant) {
  std::vector<std::pair<float, float>> available_vertices{};
  for (int row = ant.current_position, col = 1;
       col < adjacency_matrix_.GetCols(); ++col) {
    if (global_pheromones_matrix_[row][col] != 0 &&
        !ant.visited_vertices.count(adjacency_matrix_[row][col])) {
      available_vertices.emplace_back(adjacency_matrix_[0][col],
                                      global_pheromones_matrix_[row][col]);
    }
  }
  return available_vertices;
}

float AntColonyOptimization::AntStepChoice(
    std::vector<std::pair<float, float>> available_vertices) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  float total_pheromones = 0;
  float partial_sum = 0;
  float vertex;
  double probability = dis(gen);

  for (auto const& v : available_vertices) {
    total_pheromones += v.second;
  }

  for (auto& v : available_vertices) {
    vertex = v.first;
    partial_sum += v.second / total_pheromones;
    v.second = v.second / total_pheromones + partial_sum - v.second;
    if (probability <= v.second) {
      return vertex;
    }
  }
  return 0;
}

void AntColonyOptimization::AntBypass(Ant ant) {
  float next_position = AntStepChoice(AccessAvailableVertices(ant));
  ant.path_cost += GetDistanceBetweenVertex(ant.current_position, next_position);
  ant.current_position = next_position;
  ant.visited_vertices.emplace(next_position);

  for (int i = 0; i < ; ++i) {

  }

  //  std::cout << random_float << std::endl;

  //  for (const auto vertex : visited_vertices) {
  //    cost_vertices.emplace_back(vertex.second / path_cost + partial_sum);
  //    partial_sum += vertex.second / path_cost;
  //  }

  //  for (const auto vertex : cost_vertices) {
  //    std::cout << vertex << std::endl;
  //  }
}

float AntColonyOptimization::GetDistanceBetweenVertex(float f_vertex,
                                                      float s_vertex) {
  int row_index = 0;
  int col_index = 0;

  for (int row = 0; row < adjacency_matrix_.GetRows(); ++row) {
    if (adjacency_matrix_[row][0] == f_vertex) {
      row_index = row;
      break;
    }
  }

  for (int col = 0; col < adjacency_matrix_.GetCols(); ++col) {
    if (adjacency_matrix_[0][col] == s_vertex) {
      col_index = col;
      break;
    }
  }
  return adjacency_matrix_[row_index][col_index];
}

GraphAlgorithms::TsmResult AntColonyOptimization::GetResult() {
  return tsm_result_;
}

AntColonyOptimization::Ant::Ant(float start_position)
    : current_position(start_position) {
  visited_vertices.emplace(start_position);
}

}  // namespace s21

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

// lower_bound