#ifndef SIMPLENAVIGATOR_CONSOLE_INTERFACE_H
#define SIMPLENAVIGATOR_CONSOLE_INTERFACE_H

#include "../graph_algorithms/s21_graph_algorithms.h"
#include <stdio.h>
#include <regex>

// загрузка исходного графа из файла
// обход графа в ширину с выводом результата обхода в консоль
// обход графа в глубину с выводом результата обхода в консоль
// поиск кратчайшего пути между произвольными двумя вершинами с выводом результата в консоль
// поиск кратчайших путей между всеми парами вершин в графе с выводом результирующей матрицы в консоль
// поиск минимального остовного дерева в графе с выводом результирующей матрицы смежности в консоль
// решение задачи комивояжера с выводом результирующего маршрута и его длины в консоль

namespace s21 {
class ConsoleInterface {
 public:
  void Run();
 private:
  Graph graph_;
  GraphAlgorithms graph_algorithms_;
  bool is_open = false;

  static void PrintStartMenu();
  static void PrintMainMenu();
  static bool LoadData(Graph &graph);
  void RunMainLogic(std::string &choice);

  static void ClearConsole();
  void RunInitLogic();
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_CONSOLE_INTERFACE_H
