#ifndef SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_
#define SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_

#include <unordered_set>
#include <vector>

#include "map"
#include "matrix.h"
#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {

class AntColonyOptimization {
 public:
  explicit AntColonyOptimization(matrix<float> adjacency_matrix);

  // temp
  void PrintMatrix(const s21::matrix<float>& matrix) {
    for (int i = 0; i < matrix.GetRows(); ++i) {
      for (int j = 0; j < matrix.GetCols(); ++j) {
        std::cout << matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
  //

  void BypassColony();

  GraphAlgorithms::TsmResult GetResult();

 private:
  struct Ant {
    Ant(float start_position);

    Ant() = delete;
    Ant(Ant&) = delete;
    Ant(Ant&&) = delete;
    ~Ant() = default;

    float current_position;
    float path_cost;
    std::unordered_set<float> visited_vertices;
    matrix<float> pheromone_matrix;
  };

  struct ColonyConfiguration {
    float pheromone;
    float evaporation_rate;
  };

  GraphAlgorithms::TsmResult tsm_result_;
  ColonyConfiguration colony_configuration_{};

  matrix<float> adjacency_matrix_{};
  matrix<float> global_pheromones_matrix_{};
  matrix<float> local_pheromones_matrix_{};

  float AntStepChoice(std::vector<std::pair<float, float>> available_vertices);
  std::vector<std::pair<float, float>> AccessAvailableVertices(const Ant& ant);

  void AntBypass(Ant ant);
  void EvaporatePheromones() const;
  float GetDistanceBetweenVertex(float f_vertex, float s_vertex);
};

}  // namespace s21

#endif  // SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_
