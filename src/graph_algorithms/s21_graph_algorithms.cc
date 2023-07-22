#include "s21_graph_algorithms.h"

namespace s21 {
std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                   int start_vertex) {
  Matrix adjacency_matrix = graph.GetGraph();
  s21::stack<int> adjacent_vertices;
  std::list<int> visited_vertices;

  int vertex_row_index = 0;
  int vertex = start_vertex;
  bool is_founded = false;
  for (int row = 0, col = 0; row < adjacency_matrix.GetRows() && !is_founded;
       ++row) {
    if (adjacency_matrix(row, col) == start_vertex) {
      vertex_row_index = row;
      is_founded = true;
    }
  }
  if (!is_founded) {
    return std::vector<int>{};
  }

  do {
    visited_vertices.push_front(vertex);
    UpdateAdjacentVertices(vertex, adjacency_matrix, adjacent_vertices,
                           visited_vertices);
    std::cout << adjacent_vertices.size() << std::endl;
    vertex = adjacent_vertices.top();
    adjacent_vertices.pop();
  } while (!adjacent_vertices.empty());

//  for (auto itr : visited_vertices) {
//    std::cout << itr << " ";
//  }
  return {};
}

void GraphAlgorithms::UpdateAdjacentVertices(int vertex,
                                             Matrix& adjacency_matrix,
                                             s21::stack<int>& adjacent_vertices,
                                             std::list<int>& visited_vertices) {
  int vertex_row_index = 0;
  for (int row = 0, col = 0;
       row < adjacency_matrix.GetRows() && vertex_row_index == 0; ++row) {
    if (vertex == adjacency_matrix(row, col)) {
      vertex_row_index = row;
    }
  }

  for (int row = 0, col = 1; col < adjacency_matrix.GetCols(); ++col) {
    if (adjacency_matrix(vertex_row_index, col) != 0 &&
        std::find(visited_vertices.begin(), visited_vertices.end(),
                  adjacency_matrix(row, col)) == visited_vertices.end()) {
      adjacent_vertices.push(adjacency_matrix(row, col));
    }
  }
}

}  // namespace s21

int main() {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "/home/freiqq/Projects/Algorithms/SimpleNavigator/src/graph/graph");
  s21::GraphAlgorithms graph_a;
  graph_a.DepthFirstSearch(graph, 100);
  return 0;
}