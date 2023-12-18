#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {
std::pair<float, std::vector<float>>
GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph, float vertex1,
                                                float vertex2) {
  return {1, {vertex1, vertex2}};
}

matrix<float> GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    Graph& graph) {
  return graph.GetGraph();
}

}  // namespace s21
