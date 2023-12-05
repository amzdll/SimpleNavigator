#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRandomGenerator>
#include <QTimer>
#include <cmath>
#include <random>
#include <vector>

#include "iostream"
#include "s21_graph.h"

const double kRepulsionFactor = 500.0;  // Фактор отталкивания
const double kSpringFactor = 0.1;       // Фактор пружины


struct Node {
  double x, y;
  Node(double x, double y) : x(x), y(y) {}
};



class FruchtermanReingold {
 public:
  FruchtermanReingold(s21::matrix<float> adjacencyMatrix,
                      double width, double height);

  std::vector<Node> layout();

 private:
  s21::matrix<float> adjacencyMatrix_;
  std::vector<Node> nodes_;
  double width_;
  double height_;
  double kRepulsionFactor = 500.0;  // Фактор отталкивания
  double kSpringFactor = 0.1;       // Фактор пружины

  void initializePositions();
  void calculateForces();
  void updatePositions();
};


FruchtermanReingold::FruchtermanReingold(s21::matrix<float> adjacencyMatrix,
                                         double width, double height)
    : adjacencyMatrix_(adjacencyMatrix), width_(width), height_(height) {}

std::vector<Node> FruchtermanReingold::layout() {
  initializePositions();
  const int numIterations = 100;
  for (int iter = 0; iter < numIterations; ++iter) {
    calculateForces();
    updatePositions();
  }

  return nodes_;
}

void FruchtermanReingold::initializePositions() {
  nodes_.clear();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distX(0.0, width_);
  std::uniform_real_distribution<double> distY(0.0, height_);
  for (size_t i = 0; i < adjacencyMatrix_.GetRows(); ++i) {
    nodes_.emplace_back(distX(gen), distY(gen));
  }
}

void FruchtermanReingold::calculateForces() {
  for (size_t i = 0; i < nodes_.size(); ++i) {
    for (size_t j = 0; j < nodes_.size(); ++j) {
      if (i != j) {
        double dx = nodes_[j].x - nodes_[i].x;
        double dy = nodes_[j].y - nodes_[i].y;
        double distance = std::max(1.0, std::sqrt(dx * dx + dy * dy));
        double repulsionForce = kRepulsionFactor / distance;
        nodes_[i].x -= repulsionForce * dx / distance;
        nodes_[i].y -= repulsionForce * dy / distance;
        if (adjacencyMatrix_[i][j] > 0.0) {
          double springForce = kSpringFactor * (distance - adjacencyMatrix_[i][j]);
          nodes_[i].x += springForce * dx / distance;
          nodes_[i].y += springForce * dy / distance;
        }
      }
    }
  }
}

void FruchtermanReingold::updatePositions() {
  for (auto& node : nodes_) {
    node.x = std::max(0.0, std::min(width_, node.x));
    node.y = std::max(0.0, std::min(height_, node.y));
  }
}

class GraphLayout : public QGraphicsScene {
 public:
  GraphLayout(s21::matrix<float> adjacencyMatrix)
      : adjacencyMatrix_(adjacencyMatrix) {
    // Создание вершин графа
    int rows = adjacencyMatrix.GetRows();
    int cols = adjacencyMatrix.GetCols();

    for (int i = 0; i < rows; ++i) {
      QGraphicsEllipseItem* vertex = addEllipse(0, 0, 50, 50);
      vertex->setPos(i * 60, 60);

      QGraphicsTextItem* textItem =
          new QGraphicsTextItem(QString::number(i), vertex);
      textItem->setPos(16, 13);

      vertices_.append(vertex);
    }

    FruchtermanReingold layout(adjacencyMatrix_, 500, 500);
    std::vector<Node> nodePositions = layout.layout();

    // Обновление позиций вершин
    for (int i = 0; i < vertices_.size(); ++i) {
      vertices_[i]->setPos(nodePositions[i].x, nodePositions[i].y);
    }
  }

 private:
  s21::matrix<float> adjacencyMatrix_;
  QVector<QGraphicsEllipseItem*> vertices_;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::Graph graph;
  graph.LoadGraphFromFile(
      "/Users/glenpoin/W/Projects/Algorithms/SimpleNavigator/materials/"
      "examples/graph_1.txt");

  QGraphicsView view;
  GraphLayout scene(graph.GetGraph());
  view.setScene(&scene);
  view.show();

  return a.exec();
}
