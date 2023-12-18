#ifndef SIMPLENAVIGATOR_S_21_GRAPH_H
#define SIMPLENAVIGATOR_S_21_GRAPH_H

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "matrix.h"

namespace s21 {
class Graph {
 public:
  using adjacency_vertices = std::map<float, std::vector<float>>;

  bool LoadGraphFromFile(const std::string& filename);
  bool ExportGraphToDot(const std::string& filename);

  matrix<float> GetGraph() { return adjacency_matrix_; };
 private:

  adjacency_vertices adjacency_vertices_;
  matrix<float> adjacency_matrix_{};
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S_21_GRAPH_H
