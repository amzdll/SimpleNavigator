#include <unordered_map>

#include "../utils/ant_colony_optimization.h"
#include "s21_graph_algorithms.h"

namespace s21 {
GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph& graph) {
  Colony colony(graph.GetGraph());
  colony.BypassColony();
  return colony.GetResult();
}

}  // namespace s21
