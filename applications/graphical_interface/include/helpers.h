#ifndef GRAPHFORCES_H
#define GRAPHFORCES_H

#include <QVector2D>
#include <QVector>

#include "s21_graph.h"

class Helpers {
 public:
  static QVector<QPair<float, QVector2D>> ApplyForces(
      QVector<QPair<float, QVector2D>> vertices,
      const s21::matrix<float>& adjacency_matrix) {
    for (int i = 0; i < 500; ++i) {
      auto spring_forces = SpringForce(vertices, adjacency_matrix);
      auto repulsion_force = RepulsionForce(vertices, adjacency_matrix);
      for (int index = 0; index < vertices.size(); ++index) {
        vertices[index].second +=
            spring_forces[index].second + repulsion_force[index].second;
      }
    }
    return vertices;
  }

  static QVector<QPair<float, QVector2D>> RepulsionForce(
      QVector<QPair<float, QVector2D>> vertices,
      const s21::matrix<float>& adjacency_matrix) {
    const qreal k = -0.5;
    QVector<QPair<float, QVector2D>> forces(vertices.size(), {});
    for (int i = 1; i < vertices.size(); ++i) {
      QVector2D force(0, 0);
      for (int j = 1; j < vertices.size(); ++j) {
        if (i != j) {
          QVector2D delta = vertices[j].second - vertices[i].second;
          qreal distance = delta.length();
          force += delta.normalized() * float (1.f / distance) * k * distance;
        }
      }
      forces[i].second += force;
    }
    return forces;
  }

  static QVector<QPair<float, QVector2D>> SpringForce(
      QVector<QPair<float, QVector2D>> vertices,
      const s21::matrix<float>& adjacency_matrix) {
    const qreal k = 0.3;
    QVector<QPair<float, QVector2D>> forces(vertices.size(), {});
    for (int i = 1; i < vertices.size(); ++i) {
      for (int j = i + 1; j < vertices.size(); ++j) {
        if (adjacency_matrix[i][j] != 0) {
          QVector2D delta = vertices[j].second - vertices[i].second;
          qreal distance = delta.length();
          QVector2D force =
              delta.normalized() * float(distance - adjacency_matrix[i][j] * 10) * k;
          forces[i].second += force;
          forces[j].second -= force;
        }
      }
    }
    return forces;
  }

  static QVector<QPair<float, QVector2D>> CenterGraph(
      QVector<QPair<float, QVector2D>> vertices, int window_width,
      int window_height) {
    qreal minX = std::numeric_limits<qreal>::max();
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::min();
    qreal maxY = std::numeric_limits<qreal>::min();

    for (int i = 1; i < vertices.size(); ++i) {
      minX = qMin(minX, vertices[i].second.x());
      minY = qMin(minY, vertices[i].second.y());
      maxX = qMax(maxX, vertices[i].second.x());
      maxY = qMax(maxY, vertices[i].second.y());
    }

    qreal graphWidth = maxX - minX;
    qreal graphHeight = maxY - minY;

    qreal scale = qMin(0.8 * window_width / graphWidth,
                       0.8 * window_height / graphHeight);

    qreal offsetX = (window_width - scale * graphWidth) / 2;
    qreal offsetY = (window_height - scale * graphHeight) / 2;

    for (auto &position : vertices) {
      position.second.setX((position.second.x() - minX) * scale + offsetX);
      position.second.setY((position.second.y() - minY) * scale + offsetY);
    }
    return vertices;
  }
};
#endif  // GRAPHFORCES_H
