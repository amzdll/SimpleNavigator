#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QVector>
#include <QPointF>
#include <QTimer>
#include <QApplication>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const double kRepulsionFactor = 500.0; // Фактор отталкивания
const double kSpringFactor = 0.1;      // Фактор пружины

class GraphLayout : public QGraphicsScene {
 public:
  GraphLayout(const QVector<QVector<int>>& adjacencyMatrix)
      : adjacencyMatrix_(adjacencyMatrix) {

    // Установка размеров сцены
    setSceneRect(0, 0, 300, 300);

    // Создание вершин графа
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {

      QGraphicsEllipseItem* vertex = addEllipse(0, 0, 20, 20);
      vertex->setPos(0, 0);  // Исправленные позиции вершин
      vertices_.append(vertex);
    }

    // Создание таймера для обновления расположения вершин
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &GraphLayout::updateLayout);
    timer_->start(20);  // Интервал обновления

    updateLayout();
  }

 private:
  QVector<QVector<int>> adjacencyMatrix_;
  QVector<QGraphicsEllipseItem*> vertices_;
  QTimer* timer_;


  void updateLayout() {
    QVector<QPointF> forces(vertices_.size(), QPointF(0, 0));
    // Вычисление силы отталкивания между вершинами
    for (int i = 0; i < vertices_.size(); ++i) {
      for (int j = 0; j < vertices_.size(); ++j) {
        if (i != j) {
          QPointF direction = vertices_[j]->pos() - vertices_[i]->pos();
          double distance = std::max(1.0, std::sqrt(QPointF::dotProduct(direction, direction)));
          forces[i] -= kRepulsionFactor * direction / (distance * distance);
        }
      }
    }

    // Вычисление силы пружины между соединенными вершинами
    for (int i = 0; i < vertices_.size(); ++i) {
      for (int j = 0; j < vertices_.size(); ++j) {
        if (adjacencyMatrix_[i][j] == 1) {
          QPointF direction = vertices_[j]->pos() - vertices_[i]->pos();
          double distance = std::max(1.0, std::sqrt(QPointF::dotProduct(direction, direction)));
          forces[i] += kSpringFactor * direction * distance;
        }
      }
    }

    // Применение силы к вершинам
    for (int i = 0; i < vertices_.size(); ++i) {
      vertices_[i]->setPos(vertices_[i]->pos() + forces[i]);
    }
  }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
