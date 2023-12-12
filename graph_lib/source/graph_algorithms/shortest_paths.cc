#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {
float GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph, float vertex1,
                                                    float vertex2) {
  matrix adjacency_matrix = graph.GetGraph();
  queue<float> adjacent_vertices;
  std::map<float, float> path_cost;
  std::list<float> visited_vertices{vertex1};

  if (!GetIndexOfVertex(vertex1, adjacency_matrix) ||
      !GetIndexOfVertex(vertex2, adjacency_matrix)) {
    return {};
  }

  float vertex = vertex1;
  for (int row = 0, col = 1; col < adjacency_matrix.GetCols(); ++col) {
    path_cost.insert({(adjacency_matrix(row, col)), INT32_MAX});
  }
  path_cost[vertex] = 0;

  do {
    UpdateCost(vertex, adjacency_matrix, adjacent_vertices, visited_vertices,
               path_cost);
    vertex = adjacent_vertices.front();
    visited_vertices.push_back(vertex);
    adjacent_vertices.pop();
  } while (!adjacent_vertices.empty());

  return path_cost[vertex2];
}

//
//matrix<float> GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) {
//  matrix<float> adjacency_matrix = graph.GetGraph();
//  for (float k = 0; k < adjacency_matrix.GetCols(); ++k) {
//    for (float i = 0; i < adjacency_matrix.GetRows(); ++i) {
//      for (float j = 0; j < adjacency_matrix.GetCols(); ++j) {
//        if (adjacency_matrix(i, k) != 0 && adjacency_matrix(k, j) != 0) {
//          float new_distance = adjacency_matrix(i, k) + adjacency_matrix(k, j);
//          if (adjacency_matrix(i, j) == 0 ||
//              new_distance < adjacency_matrix(i, j)) {
//            adjacency_matrix(i, j) = new_distance;
//          }
//        }
//      }
//    }
//  }
//  return adjacency_matrix;
//}
}  // namespace s21
