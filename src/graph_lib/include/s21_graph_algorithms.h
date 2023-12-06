#ifndef SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
#define SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H

#include <algorithm>
#include <limits>
#include <list>
#include <map>
#include <vector>

#include "s21_graph.h"
#include "queue.h"
#include "stack.h"

namespace s21 {
class GraphAlgorithms {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };
  // Part 1
  static std::list<int> DepthFirstSearch(Graph &graph, int start_vertex);
  static std::list<int> BreadthFirstSearch(Graph &graph, int start_vertex);

  // Part 2
  static int GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                            int vertex2);
  static matrix<int> GetShortestPathsBetweenAllVertices(Graph &graph);

  // Part 3
  static matrix<int> GetLeastSpanningTree(Graph &graph);

  // Part 4
  static TsmResult SolveTravelingSalesmanProblem(Graph &graph_test_);

 private:
  static void UpdateAdjacentVertices(int vertex, matrix<int> &adjacency_matrix,
                                     s21::stack<int> &adjacent_vertices,
                                     std::list<int> &visited_vertices);
  static void UpdateAdjacentVertices(int vertex, matrix<int> &adjacency_matrix,
                                     s21::queue<int> &adjacent_vertices,
                                     std::list<int> &visited_vertices);
  static int GetIndexOfVertex(int vertex, matrix<int> &adjacency_matrix);
  static bool Contains(const s21::stack<int> &stack, int elem);
  static bool Contains(const s21::queue<int> &queue, int elem);
  static bool Contains(const std::list<int> &list, int elem);
  static void UpdateCost(int vertex, matrix<int> &adjacency_matrix,
                         s21::queue<int> &adjacent_vertices,
                         std::list<int> &visited_vertices,
                         std::map<int, int> &path_cost);
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
