#include "s21_graph_algorithms.h"

namespace s21 {
void GraphAlgorithms::UpdateCost(float vertex, matrix<float>& adjacency_matrix,
                                 s21::queue<float>& adjacent_vertices,
                                 std::list<float>& visited_vertices,
                                 std::map<float, float>& path_cost,
                                 std::map<float, float>& predecessor) {
  int row_index = GetIndexOfVertex(vertex, adjacency_matrix);
  for (int row = 0, col = 1; col < adjacency_matrix.GetCols(); ++col) {
    if (adjacency_matrix[row_index][col] > 0 &&
        !Contains(visited_vertices, adjacency_matrix[row][col])) {
      if (path_cost[adjacency_matrix[row][col]] >
          adjacency_matrix[row_index][col] +
              path_cost[adjacency_matrix[row_index][0]]) {
        path_cost[adjacency_matrix[row][col]] =
            adjacency_matrix[row_index][col] +
            path_cost[adjacency_matrix[row_index][0]];
        predecessor[adjacency_matrix[row][col]] = vertex; // Сохраняем предшественника
        adjacent_vertices.push(adjacency_matrix[row][col]);
      }
    }
  }
}
void GraphAlgorithms::UpdateAdjacentVertices(
    float vertex, matrix<float>& adjacency_matrix,
    s21::stack<float>& adjacent_vertices, std::list<float>& visited_vertices) {
  int vertex_row_index = GetIndexOfVertex(vertex, adjacency_matrix);
  for (int row = 0, col = 1; col < adjacency_matrix.GetCols(); ++col) {
    if (adjacency_matrix[vertex_row_index][col] != 0 &&
        !Contains(visited_vertices, adjacency_matrix[row][col]) &&
        !Contains(adjacent_vertices, adjacency_matrix[row][col])) {
      adjacent_vertices.push(adjacency_matrix[row][col]);
    }
  }
}

void GraphAlgorithms::UpdateAdjacentVertices(
    float vertex, matrix<float>& adjacency_matrix,
    s21::queue<float>& adjacent_vertices, std::list<float>& visited_vertices) {
  int vertex_row_index = GetIndexOfVertex(vertex, adjacency_matrix);
  for (int row = 0, col = 1; col < adjacency_matrix.GetCols(); ++col) {
    if (adjacency_matrix[vertex_row_index][col] != 0 &&
        !Contains(visited_vertices, adjacency_matrix[row][col]) &&
        !Contains(adjacent_vertices, adjacency_matrix[row][col])) {
      adjacent_vertices.push(adjacency_matrix[row][col]);
    }
  }
}

int GraphAlgorithms::GetIndexOfVertex(float vertex,
                                      matrix<float>& adjacency_matrix) {
  for (int row = 0, col = 0; row < adjacency_matrix.GetRows(); ++row) {
    if (vertex == adjacency_matrix[row][col]) {
      return row;
    }
  }
  return 0;
}

bool GraphAlgorithms::Contains(const std::list<float>& list, float elem) {
  return std::find(list.begin(), list.end(), elem) != list.end();
}

bool GraphAlgorithms::Contains(const s21::stack<float>& stack, float elem) {
  s21::stack<float> temporary_stack(stack);
  while (!temporary_stack.empty()) {
    if (temporary_stack.top() == elem) {
      return true;
    }
    temporary_stack.pop();
  }
  return false;
}

bool GraphAlgorithms::Contains(const s21::queue<float>& queue, float elem) {
  s21::queue<float> temporary_queue(queue);
  while (!temporary_queue.empty()) {
    if (temporary_queue.front() == elem) {
      return true;
    }
    temporary_queue.pop();
  }
  return false;
}
}  // namespace s21
