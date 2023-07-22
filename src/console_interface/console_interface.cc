#include "console_interface.h"

namespace s21 {
void ConsoleInterface::Run() {
  std::string choice = "-1";
  std::regex regexPattern("^[2-7]$");

  PrintStartMenu();
  while (choice != "0") {
    std::cin >> choice;
    if (choice == "0") {
      std::cout << "Exiting the program." << std::endl;
    } else if (choice == "1") {
      RunInitLogic();
    } else if (is_open && std::regex_match(choice, regexPattern)) {
      RunMainLogic(choice);
    } else {
      if (is_open) {
        PrintMainMenu();
      } else {
        PrintStartMenu();
      }
      std::cout << "\033[1;31mInvalid command.\033[0m" << std::endl;
    }
  }
}
void ConsoleInterface::PrintStartMenu() {
  ClearConsole();
  std::cout << "\033[1;32m";
  std::cout << "Choose an option" << std::endl;
  std::cout << "1. Load the source graph from a file" << std::endl;
  std::cout << "0. Exit" << std::endl;
  std::cout << "\033[0m";
}

void ConsoleInterface::PrintMainMenu() {
  ClearConsole();
  std::cout << "\033[1;32m";
  std::cout << "Choose an option:\n" << std::endl;
  std::cout << "1. Load the source graph from a file." << std::endl;
  std::cout << "2. Perform breadth-first traversal and display the "
               "result in "
               "the console."
            << std::endl;
  std::cout << "3. Perform depth-first traversal and display the "
               "result in "
               "the console."
            << std::endl;
  std::cout << "4. Find the shortest path between arbitrary two "
               "vertices and "
               "display the result in the console."
            << std::endl;
  std::cout << "5. Find the shortest paths between all pairs of vertices "
               "in "
               "the graph and display the resulting matrix in the console."
            << std::endl;
  std::cout << "6. Find the minimum spanning tree in the graph and "
               "display "
               "the resulting adjacency matrix in the console."
            << std::endl;
  std::cout << "7. Solve the traveling salesman problem and display the "
               "resulting route  and its length in the console."
            << std::endl;
  std::cout << "0. Exit." << std::endl;
  std::cout << "\033[0m";
}

void ConsoleInterface::ClearConsole() { std::cout << "\033[H\033[2J"; }

bool ConsoleInterface::LoadData(Graph& graph) {
  std::string file_path;
  std::cout << "File path: ";
  std::cin >> file_path;
  return graph.LoadGraphFromFile(file_path);
}

void ConsoleInterface::RunInitLogic() {
  if (LoadData(graph_)) {
    PrintMainMenu();
    is_open = true;
  } else {
    PrintStartMenu();
    std::cout << "\033[1;31mInvalid File.\n\n\033[0m" << std::endl;
    is_open = false;
  }
}

void ConsoleInterface::RunMainLogic(std::string& choice) {
  if (choice == "1") {
    if (LoadData(graph_)) {
      PrintMainMenu();
    } else {
      PrintStartMenu();
      std::cout << "\033[1;31mInvalid File.\n\n\033[0m" << std::endl;
      is_open = false;
    }
  } else if (choice == "2") {
    ;
  } else if (choice == "3") {
    ;
  } else if (choice == "4") {
    ;
  } else if (choice == "5") {
    ;
  } else if (choice == "6") {
    ;
  } else if (choice == "7") {
    ;
  }
}

}  // namespace s21

int main() {
  s21::ConsoleInterface ci;
  ci.Run();
  return 0;
}
