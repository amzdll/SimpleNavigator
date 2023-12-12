#include "s21_graph_algorithms.h"

namespace s21 {
std::list<float> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                 float start_vertex) {
  float vertex = start_vertex;
  matrix<float> adjacency_matrix = graph.GetGraph();
  stack<float> adjacent_vertices;
  std::list<float> visited_vertices{static_cast<float>(start_vertex)};

  if (!GetIndexOfVertex(start_vertex, adjacency_matrix)) {
    return {};
 }

  do {
    UpdateAdjacentVertices(vertex, adjacency_matrix, adjacent_vertices,
                           visited_vertices);
    vertex = adjacent_vertices.top();
    visited_vertices.push_back(vertex);
    adjacent_vertices.pop();

  } while (!adjacent_vertices.empty());

  return visited_vertices;
}

std::list<float> GraphAlgorithms::BreadthFirstSearch(Graph& graph,
                                                   float start_vertex) {
  matrix<float> adjacency_matrix = graph.GetGraph();
  s21::queue<float> adjacent_vertices;
  std::list<float> visited_vertices{start_vertex};

  float vertex = start_vertex;
  if (!GetIndexOfVertex(vertex, adjacency_matrix)) {
    return {};
  }

  do {
    UpdateAdjacentVertices(vertex, adjacency_matrix, adjacent_vertices,
                           visited_vertices);
    vertex = adjacent_vertices.front();
    visited_vertices.push_back(vertex);
    adjacent_vertices.pop();
  } while (!adjacent_vertices.empty());

  return visited_vertices;
}
}