#ifndef SIMPLENAVIGATOR_S_21_GRAPH_H
#define SIMPLENAVIGATOR_S_21_GRAPH_H

#include <fstream>
#include <sstream>
#include <string>

#include "../utils/s21_matrix.hpp"

namespace s21 {
class Graph {
 public:
  bool LoadGraphFromFile(const std::string& filename);
  bool ExportGraphToDot(const std::string& filename);

  matrix<int> GetGraph() { return adjacency_matrix_; };

 private:
  matrix<int> adjacency_matrix_{};
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S_21_GRAPH_H
