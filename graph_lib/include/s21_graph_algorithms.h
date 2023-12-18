#ifndef SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
#define SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H

#include <algorithm>
#include <limits>
#include <list>
#include <map>
#include <vector>

#include "queue.h"
#include "s21_graph.h"
#include "stack.h"

namespace s21 {
class GraphAlgorithms {
 public:
  struct TsmResult {
    std::vector<float> vertices;
    s21::matrix<float> pheromones;
    double distance;
  };
  // Part 1
  static std::vector<float> DepthFirstSearch(Graph &graph, float start_vertex);
  static std::vector<float> BreadthFirstSearch(Graph &graph, float start_vertex);

  // Part 2
  static std::pair<float, std::vector<float>> GetShortestPathBetweenVertices(
      Graph &graph, float vertex1, float vertex2);
  static matrix<float> GetShortestPathsBetweenAllVertices(Graph &graph);

  // Part 3
  static matrix<float> GetLeastSpanningTree(Graph &graph);

  // Part 4
  static TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
  static void UpdateAdjacentVertices(float vertex,
                                     matrix<float> &adjacency_matrix,
                                     s21::stack<float> &adjacent_vertices,
                                     std::vector<float> &visited_vertices);
  static void UpdateAdjacentVertices(float vertex,
                                     matrix<float> &adjacency_matrix,
                                     s21::queue<float> &adjacent_vertices,
                                     std::vector<float> &visited_vertices);
  static int GetIndexOfVertex(float vertex, matrix<float> &adjacency_matrix);
  static bool Contains(const s21::stack<float> &stack, float elem);
  static bool Contains(const s21::queue<float> &queue, float elem);
  static bool Contains(const std::vector<float> &vector, float elem);
  static void UpdateCost(float vertex, matrix<float> &adjacency_matrix,
                         s21::queue<float> &adjacent_vertices,
                         std::vector<float> &visited_vertices,
                         std::map<float, float> &path_cost,
                         std::map<float, float> &predecessor);
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
