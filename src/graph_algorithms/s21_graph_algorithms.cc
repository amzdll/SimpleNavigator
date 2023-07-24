#include "s21_graph_algorithms.h"

namespace s21 {
std::list<int> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                 int start_vertex) {
  Matrix adjacency_matrix = graph.GetGraph();
  s21::stack<int> adjacent_vertices;
  std::list<int> visited_vertices{start_vertex};

  int vertex = start_vertex;
  if (!GetIndexOfVertex(vertex, adjacency_matrix)) {
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

std::list<int> GraphAlgorithms::BreadthFirstSearch(Graph& graph,
                                                   int start_vertex) {
  Matrix adjacency_matrix = graph.GetGraph();
  std::queue<int> adjacent_vertices;
  std::list<int> visited_vertices{start_vertex};

  int vertex = start_vertex;
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

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                                    int vertex2) {
  Matrix adjacency_matrix = graph.GetGraph();
  std::map<int, int> path_cost;
  std::queue<int> adjacent_vertices;
  std::list<int> visited_vertices{vertex1};

  int vertex = vertex1;
  for (int row = 0, col = 1; col < adjacency_matrix.GetCols(); ++col) {
    path_cost.insert({(adjacency_matrix(row, col)), INT32_MAX});
  }
  path_cost[vertex] = 0;

  do {
    UpdateCost(vertex, adjacency_matrix, adjacent_vertices, visited_vertices,
               path_cost);
    vertex = adjacent_vertices.front();
    visited_vertices.push_back(vertex);
    adjacent_vertices.pop();
  } while (!adjacent_vertices.empty());

  return path_cost[vertex2];
}

Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) {
  Matrix adjacency_matrix = graph.GetGraph();
  //  Matrix adjacency_matrix(adjacency_matrix.GetRows(),
  //  adjacency_matrix.GetCols());
  for (int k = 0; k < adjacency_matrix.GetCols(); ++k) {
    for (int i = 0; i < adjacency_matrix.GetRows(); ++i) {
      for (int j = 0; j < adjacency_matrix.GetCols(); ++j) {
        if (adjacency_matrix(i, k) != 0 && adjacency_matrix(k, j) != 0) {
          int new_distance = adjacency_matrix(i, k) + adjacency_matrix(k, j);
          if (adjacency_matrix(i, j) == 0 || new_distance < adjacency_matrix(i, j)) {
            adjacency_matrix(i, j) = new_distance;
          }
        }
      }
    }
  }

  return adjacency_matrix;
}

}  // namespace s21

int main() {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "/home/freiqq/Projects/Algorithms/SimpleNavigator/src/graph/graph.txt");
  s21::GraphAlgorithms graph_a;
  std::list<int> a;
  std::list<int> b;

  //  int c = graph_a.GetShortestPathBetweenVertices(graph, 1, 4);
  //  std::cout << c;
  Matrix d = graph_a.GetShortestPathsBetweenAllVertices(graph);

  for (int i = 0; i < d.GetRows(); ++i) {
    for (int j = 0; j < d.GetCols(); ++j) {
      std::cout << d(i, j) << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}