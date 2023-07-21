#ifndef SIMPLENAVIGATOR_S_21_GRAPH_H
#define SIMPLENAVIGATOR_S_21_GRAPH_H

#include <string>
#include <fstream>
#include <sstream>


#include "../matrix/s21_matrix_oop.h"

namespace s21 {
class Graph {
 public:
  bool LoadGraphFromFile(const std::string& filename);
  bool ExportGraphToDot(std::string filename);

  Matrix GetGraph() { return adjacency_matrix_; };

 private:
  Matrix adjacency_matrix_{};
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S_21_GRAPH_H
