#include "s21_graph.h"

namespace s21 {
bool Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file_data(filename);
  if (!file_data.is_open()) {
    return false;
  }
  unsigned int dimension;
  file_data >> dimension;
  // todo: fix
  matrix<float> adjacency_matrix(dimension, dimension);
  for (int row = 0; row < adjacency_matrix.GetRows(); ++row) {
    for (int col = 0; col < adjacency_matrix.GetCols(); ++col) {
      file_data >> adjacency_matrix[row][col];
    }
    vertex_indices_.insert({adjacency_matrix[row][0], row});
  }
  adjacency_matrix_ = adjacency_matrix;
  size_ = adjacency_matrix.GetRows();
  file_data.close();
  return true;
}

bool Graph::ExportGraphToDot(const std::string& filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    return false;
  }

  std::stringstream dot_content;
  dot_content << "graph graphname {\n";
  for (int i = 0; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      if (adjacency_matrix_(i, j) > 0) {
        dot_content << "    " << i << " -- " << j << ";\n";
      }
    }
  }
  dot_content << "}";
  file << dot_content.str();
  return true;
}
float Graph::operator()(float first_vertex, float second_vertex)  {
  return adjacency_matrix_[vertex_indices_[first_vertex]]
                          [vertex_indices_[second_vertex]];
}

const matrix<float>& Graph::GetGraph() const { return adjacency_matrix_; }

size_t Graph::GetSize() const { return size_; }

}  // namespace s21
