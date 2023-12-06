#ifndef SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_
#define SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_

#include <unordered_set>
#include <vector>

#include "map"
#include "matrix.h"
#include "s21_graph.h"

namespace s21 {

struct Ant {
 public:
  Ant() = default;
  Ant(const matrix<float>& adjacency_matrix, int start_position)
      : adjacency_matrix_(adjacency_matrix), start_position_(start_position) {}
  //  explicit Ant(const  int start_position) : start_position_(start_position)
  //  {}
  ~Ant() = default;

  void Bypass(const matrix<float>& adjacency_matrix);
  int PathSelection(float* path, int size);

 private:
  bool IsVisited(int vertex);

  const matrix<float>& adjacency_matrix_{};
  std::unordered_set<int> visited_vertices_{};
  int start_position_{};
};

class Colony {
 public:
  explicit Colony(matrix<float> adjacency_matrix);
  void InitializeColony();
  void BypassColony();
  void AntBypass(int start_position);

  void EvaporatePheromones() const;

 private:
  struct ColonyConfiguration {
    float pheromon;
    float evaporation_rate;
  };

  ColonyConfiguration colony_configuration_{};
  std::vector<Ant> colony_;

  matrix<float> adjacency_matrix_{};
  matrix<float> global_pheromones_matrix_{};
  matrix<float> local_pheromones_matrix_{};
  //  ant ant_;
};

}  // namespace s21

#endif  // SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_