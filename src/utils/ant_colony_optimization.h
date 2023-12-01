#ifndef SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_
#define SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_

#include <unordered_set>
#include <vector>

#include "matrix.h"
#include "s21_graph.h"

namespace s21 {

class Ant {
 public:
  Ant() = default;
  Ant(const matrix<int>& adjacency_matrix, int start_position)
      : adjacency_matrix_(adjacency_matrix), start_position_(start_position) {}
  //  explicit Ant(const  int start_position) : start_position_(start_position)
  //  {}
  ~Ant() = default;

  void Bypass(const matrix<int>& adjacency_matrix);

 private:
  const matrix<int>& adjacency_matrix_{};
  std::unordered_set<int> visited_vertices_{};
  int start_position_{};
};

class Colony {
 public:
  explicit Colony(matrix<int> adjacency_matrix);
  void InitializeColony();
  void BypassColony();

 private:
  std::vector<Ant> colony_;
  matrix<int> adjacency_matrix_{};
  //  ant ant_;
};

}  // namespace s21

#endif  // SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_OPTIMIZATION_H_
