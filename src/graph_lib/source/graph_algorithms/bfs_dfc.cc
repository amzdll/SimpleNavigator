#include "s21_graph_algorithms.h"

namespace s21 {
//std::list<int> GraphAlgorithms::DepthFirstSearch(Graph& graph,
//                                                 int start_vertex) {
//  int vertex = start_vertex;
//  matrix<int> adjacency_matrix = graph.GetGraph();
//  stack<int> adjacent_vertices;
//  std::list<int> visited_vertices{start_vertex};
//
//  if (!GetIndexOfVertex(start_vertex, adjacency_matrix)) {
//    return {};
// w }
//
//  do {
//    UpdateAdjacentVertices(vertex, adjacency_matrix, adjacent_vertices,
//                           visited_vertices);
//    vertex = adjacent_vertices.top();
//    visited_vertices.push_back(vertex);
//    adjacent_vertices.pop();
//
//  } while (!adjacent_vertices.empty());
//
//  return visited_vertices;
//}
//
//std::list<int> GraphAlgorithms::BreadthFirstSearch(Graph& graph,
//                                                   int start_vertex) {
//  matrix<int> adjacency_matrix = graph.GetGraph();
//  s21::queue<int> adjacent_vertices;
//  std::list<int> visited_vertices{start_vertex};
//
//  int vertex = start_vertex;
//  if (!GetIndexOfVertex(vertex, adjacency_matrix)) {
//    return {};
//  }
//
//  do {
//    UpdateAdjacentVertices(vertex, adjacency_matrix, adjacent_vertices,
//                           visited_vertices);
//    vertex = adjacent_vertices.front();
//    visited_vertices.push_back(vertex);
//    adjacent_vertices.pop();
//  } while (!adjacent_vertices.empty());
//
//  return visited_vertices;
//}
}