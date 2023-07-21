#ifndef SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
#define SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H

namespace s21 {
class GraphAlgorithms {
 public:
  DepthFirstSearch(Graph &graph, int start_vertex);
  BreadthFirstSearch(Graph &graph, int start_vertex);

  GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  GetShortestPathsBetweenAllVertices(Graph &graph);

  GetLeastSpanningTree(Graph &graph);
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_S21_GRAPH_ALGORITHMS_H
