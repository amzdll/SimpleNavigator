#ifndef SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_H_
#define SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_H_

#include <unordered_set>
#include <vector>

#include "matrix.h"
#include "s21_graph.h"
//#include "../include/s21_graph.h"


namespace s21 {
class AntColony {
 public:
  AntColony(matrix<int> adjacency_matrix);

  void Bypass();


  struct ant {
    std::unordered_set<int> visited_vertices;
    int start_positon = 1;
  };
 private:
  matrix<int> adjacency_matrix_{};
  ant ant_;
};

}  // namespace s21

#endif  // SIMPLENAVIGATOR_SRC_UTILS_ANT_COLONY_H_
