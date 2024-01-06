
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
 */

namespace s21 {
AntColonyOptimization::AntColonyOptimization(matrix<float> adjacency_matrix)
    : adjacency_matrix_(std::move(adjacency_matrix)) {
  global_pheromones_matrix_ =
      matrix<float>(adjacency_matrix_.GetRows(), adjacency_matrix_.GetCols());
  vertex_indices_[0] = 0;
  for (int row = 1; row < adjacency_matrix_.GetRows(); ++row) {
    vertex_indices_[adjacency_matrix_[row][0]] = row;
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
  // for { - epoch
  EvaporatePheromones();
  local_pheromones_matrix_ = global_pheromones_matrix_;
  //  // for { - ants
  local_pheromones_matrix_ += AntBypass(Ant(1));
  //  // }
  //  global_pheromones_matrix_ += local_pheromones_matrix_;
  //  //}
  //  tsm_result_.pheromones = global_pheromones_matrix_;

  //  PrintMatrix(global_pheromones_matrix_);
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
        (std::find(ant.visited_vertices.begin(), ant.visited_vertices.end(),
                   adjacency_matrix_[row][col]) ==
         ant.visited_vertices.end())) {
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
  return -1;
}

matrix<float> AntColonyOptimization::AntBypass(Ant ant) {
  std::vector<std::pair<float, float>> available_vertices =
      AccessAvailableVertices(ant);
  matrix<float> pheromone_matrix(adjacency_matrix_.GetRows(),
                                 adjacency_matrix_.GetCols());
  float next_position = 0;
  while (!available_vertices.empty()) {
    next_position = AntStepChoice(available_vertices);
    ant.path_cost +=
        GetDistanceBetweenVertex(ant.current_position, next_position);
    ant.current_position = next_position;
    ant.visited_vertices.emplace_back(next_position);
    available_vertices = AccessAvailableVertices(ant);
  }

  //  if (GetDistanceBetweenVertex(ant.current_position, ant.start_position)) {
  //    for (int i = 1; i < ant.visited_vertices.size(); ++i) {
  //      // 3 test constant
  //      std::cout << ant.path_cost;
  //      pheromone_matrix[i][i-1] = 1 / ant.path_cost;
  //    }
  //  }
  PrintMatrix(pheromone_matrix);
  return pheromone_matrix;
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
    : start_position(start_position), current_position(start_position) {
  visited_vertices.emplace_back(start_position);
}

}  // namespace s21

// int main() {
//   s21::Graph graph;
//     graph.LoadGraphFromFile(
//         "/Users/glenpoin/W/Projects/Algorithms/SimpleNavigator/materials/"
//         "examples/graph_1.txt");
//   graph.LoadGraphFromFile(
//       "/home/freiqq/Projects/Algorithms/SimpleNavigator/materials/examples/"
//       "graph_1.txt");
//
//   s21::AntColonyOptimization ac(graph.GetGraph());
//   //  ac.InitializeColony();
//     ac.BypassColony();
////  ac.EvaporatePheromones();
//}

// lower_bound