#ifndef SIMPLENAVIGATOR_S_21_GRAPH_H
#define SIMPLENAVIGATOR_S_21_GRAPH_H

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "matrix.h"

namespace s21 {
class Graph {
 public:
  using adjacency_vertices = std::map<float, std::vector<float>>;

  bool LoadGraphFromFile(const std::string& filename);
  bool ExportGraphToDot(const std::string& filename);

  [[nodiscard]] const matrix<float>& GetGraph() const;
  [[nodiscard]] float operator()(float first_vertex, float second_vertex);
  [[nodiscard]] size_t GetSize() const;

 private:
  size_t size_;
  matrix<float> adjacency_matrix_{};
  std::map<float, int> vertex_indices_{};
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S_21_GRAPH_H
