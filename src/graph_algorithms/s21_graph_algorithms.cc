#include "s21_graph_algorithms.h"

namespace s21 {
std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                   int start_vertex) {
  Matrix adjacency_matrix = graph.GetGraph();
  s21::stack<int> adjacent_vertices;
  std::list<int> visited_vertices;
  int vertex_row_index = 0;

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
//  visited_vertices.push_front(start_vertex);
  UpdateAdjacentVertices(1,adjacency_matrix, adjacent_vertices, visited_vertices);
//  DeapthSearch(vertex_row_index, adjacency_matrix, adjacent_vertices,
//               visited_vertices);


  while(!adjacent_vertices.empty()) {
    std::cout << adjacent_vertices.top() << " ";
    adjacent_vertices.pop();
  }
  UpdateAdjacentVertices(1,adjacency_matrix, adjacent_vertices, visited_vertices);
  std::cout << std::endl;
  while(!adjacent_vertices.empty()) {
    std::cout << adjacent_vertices.top() << " ";
    adjacent_vertices.pop();
  }
  return {};
}

//void GraphAlgorithms::DeapthSearch(int vertex_row_index,
//                                   Matrix& adjacency_matrix,
//                                   s21::stack<int>& adjacent_vertices,
//                                   std::list<int>& visited_vertices) {
//  bool is_visited = false;
//  for (int col = 1; col < adjacency_matrix.GetCols(); ++col) {
//    if (adjacency_matrix(vertex_row_index, col) != 0) {
//      for (int& visited_vertex : visited_vertices) {
//        if (adjacency_matrix(vertex_row_index, col) == visited_vertex) {
//          is_visited = true;
//        }
//      }
//      if (!is_visited) {
//        visited_vertices.push_back(adjacency_matrix(vertex_row_index, 0));
//        DeapthSearch();
//      }
//    }
//  }
//}

void GraphAlgorithms::UpdateAdjacentVertices(int vertex_row_index,
                                             Matrix& adjacency_matrix,
                                             s21::stack<int>& adjacent_vertices,
                                             std::list<int>& visited_vertices) {
  for (int row = 0,  col = 1; col < adjacency_matrix.GetCols(); ++col) {
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
  graph.LoadGraphFromFile("/home/freiqq/Projects/Algorithms/SimpleNavigator/src/graph/graph");
  s21::GraphAlgorithms graph_a;
  graph_a.DepthFirstSearch(graph, 29);
  return 0;
}