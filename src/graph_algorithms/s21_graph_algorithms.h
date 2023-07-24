#ifndef SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
#define SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H

#include <algorithm>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>

#include "../graph/s21_graph.h"
#include "../include/stack/s21_stack.cc"
// #include "../include/queue/s21_queue.cc"

namespace s21 {
class GraphAlgorithms {
 public:
  struct TsmResult {
    int *vertices;
    double distance;
  };
  // Part 1
  static std::list<int> DepthFirstSearch(Graph &graph, int start_vertex);
  static std::list<int> BreadthFirstSearch(Graph &graph, int start_vertex);

  // Part 2
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Matrix GetShortestPathsBetweenAllVertices(Graph &graph);


  // Part 3
  //  GetLeastSpanningTree(Graph &graph);

 private:
  static void UpdateAdjacentVertices(int vertex, Matrix &adjacency_matrix,
                                     s21::stack<int> &adjacent_vertices,
                                     std::list<int> &visited_vertices);
  static void UpdateAdjacentVertices(int vertex, Matrix &adjacency_matrix,
                                     std::queue<int> &adjacent_vertices,
                                     std::list<int> &visited_vertices);
  static int GetIndexOfVertex(int vertex, Matrix &adjacency_matrix);
  static bool Contains(const s21::stack<int> &stack, int elem);
  static bool Contains(const std::queue<int> &queue, int elem);
  static bool Contains(const std::list<int> &list, int elem);
  static void UpdateCost(
      int vertex, Matrix &adjacency_matrix, std::queue<int> &adjacent_vertices,
      std::list<int> &visited_vertices, std::map<int, int> &path_cost);
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
