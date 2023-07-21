#ifndef SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
#define SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H

#include <vector>

#include "../graph/s21_graph.h"
#include "../stack/s21_stack.h"

namespace s21 {
class GraphAlgorithms {
 public:
  struct TsmResult {
    int *vertices;
    double distance;
  };

  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  BreadthFirstSearch(Graph &graph, int start_vertex);

  GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  GetShortestPathsBetweenAllVertices(Graph &graph);

  GetLeastSpanningTree(Graph &graph);

 private:
  void DeapthSearch(int vertex_row_index, Matrix &adjacency_matrix,
                    s21::stack<int> &adjacent_vertices,
                    s21::list<int> &visited_vertices);
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
