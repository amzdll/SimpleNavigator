
#include "ant_colony.h"

#include <utility>

#include "iostream"

namespace s21 {
AntColony::AntColony(matrix<int> adjacency_matrix)
    : adjacency_matrix_(std::move(adjacency_matrix)) {}

void AntColony::Bypass() {
  int position = ant_.start_positon;
  int number_of_vertices = adjacency_matrix_.GetRows() - 1;

  ant_.visited_vertices.insert(ant_.start_positon);
  while (ant_.visited_vertices.size() < number_of_vertices) {
    for (int col = 1; col < adjacency_matrix_.GetCols(); ++col) {
      if (adjacency_matrix_[position][col] &&
          ant_.visited_vertices.find(col) == ant_.visited_vertices.end()) {
        ant_.visited_vertices.insert(col);
        position = col;
        std::cout << col << std::endl;
        break;
      }
    }
  }

}
}  // namespace s21

int main() {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "/Users/glenpoin/W/Projects/Algorithms/SimpleNavigator/materials/"
      "examples/graph_1.txt");
  s21::AntColony ac(graph.GetGraph());
  ac.Bypass();

  //  std::cout << "hui" << std::endl;
}