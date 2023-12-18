#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {
std::pair<float, std::vector<float>>
GraphAlgorithms::GetShortestPathBetweenVertices(
    Graph& graph, float vertex1, float vertex2) {
  return {1,{vertex1, vertex2}};
//  matrix adjacency_matrix = graph.GetGraph();
//  s21::queue<float> adjacent_vertices;
//  std::map<float, float> path_cost;
//  std::map<float, float> predecessor;
//  std::list<float> visited_vertices{vertex1};
//
//  if (!GetIndexOfVertex(vertex1, adjacency_matrix) ||
//      !GetIndexOfVertex(vertex2, adjacency_matrix)) {
//    return {0, {}};
//  }
//
//  float start_vertex = vertex1;
//  for (int row = 0, col = 1; col < adjacency_matrix.GetCols(); ++col) {
//    path_cost.insert({(adjacency_matrix(row, col)), INT32_MAX});
//  }
//  path_cost[start_vertex] = 0;
//
//  do {
//    UpdateCost(start_vertex, adjacency_matrix, adjacent_vertices,
//               visited_vertices, path_cost, predecessor);
//    start_vertex = adjacent_vertices.front();
//    visited_vertices.push_back(start_vertex);
//    adjacent_vertices.pop();
//  } while (!adjacent_vertices.empty());
//
//  float end_vertex = vertex2;
//  std::vector<float> path;
//  while (end_vertex != vertex1) {
//    path.insert(path.begin(), end_vertex);
//    end_vertex = predecessor[end_vertex];
//  }
//  path.insert(path.begin(), vertex1);
//  return {path_cost[vertex2], path};
}


 matrix<float> GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph&
 graph) {
//  matrix<float> adjacency_matrix = graph.GetGraph();
//  for (float k = 0; k < adjacency_matrix.GetCols(); ++k) {
//    for (float i = 0; i < adjacency_matrix.GetRows(); ++i) {
//      for (float j = 0; j < adjacency_matrix.GetCols(); ++j) {
//        if (adjacency_matrix(i, k) != 0 && adjacency_matrix(k, j) != 0) {
//          float new_distance = adjacency_matrix(i, k) + adjacency_matrix(k,
//          j); if (adjacency_matrix(i, j) == 0 ||
//              new_distance < adjacency_matrix(i, j)) {
//            adjacency_matrix(i, j) = new_distance;
//          }
//        }
//      }
//    }
//  }
  return graph.GetGraph();
}

// std::vector<float> GraphAlgorithms::GetShortestPathBetweenTwoVertices(Graph&
// graph,
//                                                                       float
//                                                                       vertex1,
//                                                                       float
//                                                                       vertex2)
//                                                                       {
//   return {5, 3 ,1, 2};
// }

}  // namespace s21
