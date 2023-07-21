#include "s21_graph_algorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                   int start_vertex) {
  Matrix adjacency_matrix_ = graph.GetGraph();
  s21::stack<int> adjacent_vertices;
  s21::list<int> visited_vertices;
  int vertex_row_index = 0;

  bool is_founded = false;
  for (int row = 0, col = 0; row < adjacency_matrix_.GetRows() && !is_founded;
       ++row) {
    if (adjacency_matrix_(row, col) == start_vertex) {
      vertex_row_index = row;
      is_founded = true;
    }
  }
  if (!is_founded) {
    return std::vector<int>{};
  }

  visited_vertices.push_front(start_vertex);
  DeapthSearch(vertex_row_index, adjacency_matrix_, adjacent_vertices,
               visited_vertices);
  //  return std::vector<int>();
}
void GraphAlgorithms::DeapthSearch(int vertex_row_index,
                                   Matrix& adjacency_matrix,
                                   s21::stack<int>& adjacent_vertices,
                                   s21::list<int>& visited_vertices) {
  bool is_visited = false;
  for (int col = 1; col < adjacency_matrix.GetCols(); ++col) {
    if (adjacency_matrix(vertex_row_index, col) != 0) {
      for (int& visited_vertex : visited_vertices) {
        if (adjacency_matrix(vertex_row_index, col) == visited_vertex) {
          is_visited = true;
        }
      }
      if (!is_visited) {
        visited_vertices.push_back(adjacency_matrix(vertex_row_index, 0));
        DeapthSearch();
      }
    }
  }
}
}  // namespace s21