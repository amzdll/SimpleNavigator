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
  static std::list<float> DepthFirstSearch(Graph &graph, int start_vertex);
  static std::list<float> BreadthFirstSearch(Graph &graph, int start_vertex);

  // Part 2
  static int GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                            int vertex2);
  static matrix<int> GetShortestPathsBetweenAllVertices(Graph &graph);

  // Part 3
  static matrix<int> GetLeastSpanningTree(Graph &graph);

  // Part 4
  static TsmResult SolveTravelingSalesmanProblem(Graph &graph_test_);

 private:
  static void UpdateAdjacentVertices(float vertex,
                                     matrix<float> &adjacency_matrix,
                                     s21::stack<float> &adjacent_vertices,
                                     std::list<float> &visited_vertices);
  static void UpdateAdjacentVertices(float vertex,
                                     matrix<float> &adjacency_matrix,
                                     s21::queue<float> &adjacent_vertices,
                                     std::list<float> &visited_vertices);
  static int GetIndexOfVertex(float vertex, matrix<float> &adjacency_matrix);
  static bool Contains(const s21::stack<float> &stack, float elem);
  static bool Contains(const s21::queue<float> &queue, float elem);
  static bool Contains(const std::list<float> &list, float elem);
  static void UpdateCost(int vertex, matrix<float> &adjacency_matrix,
                         s21::queue<float> &adjacent_vertices,
                         std::list<float> &visited_vertices,
                         std::map<float, float> &path_cost);
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
