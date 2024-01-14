#ifndef GRAPHFORCES_H
#define GRAPHFORCES_H

#include <QMap>
#include <QVector2D>
#include <QVector>

#include "s21_graph.h"

class Helpers {
 public:
  static QMap<float, QVector2D> ApplyForces(QMap<float, QVector2D> vertices,
                                            s21::Graph graph) {

    for (int i = 0; i < 500; ++i) {
      auto spring_forces = SpringForce(vertices, graph);
      auto repulsion_force = RepulsionForce(vertices);
      for (auto vertex : vertices.keys()) {
        vertices[vertex] += spring_forces[vertex] + repulsion_force[vertex];
      }
    }
    return vertices;
  }

  static QMap<float, QVector2D> RepulsionForce(
      QMap<float, QVector2D> vertices) {
    const qreal k = -0.5;
    QMap<float, QVector2D> forces;
    for (auto vertex_1 : vertices.keys()) {
      QVector2D force(0, 0);
      for (auto vertex_2 : vertices.keys()) {
        if (vertex_1 != vertex_2) {
          QVector2D delta = vertices[vertex_2] - vertices[vertex_1];
          qreal distance = delta.length();
          force += delta.normalized() * float(1.f / distance) * k * distance;
        }
      }
      forces[vertex_1] += force;
    }
    return forces;
  }

  static QMap<float, QVector2D> SpringForce(
      QMap<float, QVector2D> vertices,  s21::Graph graph) {
    // fix: all positions is NaN
    const qreal k = 0.3;
    QMap<float, QVector2D> forces;
    QList<float> keys = vertices.keys();
    for (int i = 0; i < keys.size(); ++i) {
      for (int j = i + 1; j < keys.size(); ++j) {
        float key_i = keys[i];
        float key_j = keys[j];
        if (graph(key_i, key_j) != 0.0) {
          QVector2D delta = vertices[key_j] - vertices[key_i];
          qreal distance = delta.length();
          QVector2D force = delta.normalized() *
                            float(distance - graph(key_i, key_j) * 10) * k;
          forces[key_i] += force;
          forces[key_j] -= force;
        }
      }
    }
    return forces;
  }

  static QMap<float, QVector2D> CenterGraph(QMap<float, QVector2D> vertices, int window_width,
                                            int window_height) {
    qreal minX = std::numeric_limits<qreal>::max();
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::min();
    qreal maxY = std::numeric_limits<qreal>::min();

    for (auto vertex : vertices) {
      minX = qMin(minX, vertex.x());
      minY = qMin(minY, vertex.y());
      maxX = qMax(maxX, vertex.x());
      maxY = qMax(maxY, vertex.y());
    }

    qreal graphWidth = maxX - minX;
    qreal graphHeight = maxY - minY;

    qreal scale = qMin(0.8 * window_width / graphWidth,
                       0.8 * window_height / graphHeight);

    qreal offsetX = (window_width - scale * graphWidth) / 2;
    qreal offsetY = (window_height - scale * graphHeight) / 2;

    for (auto& position : vertices) {
      position.setX((position.x() - minX) * scale + offsetX);
      position.setY((position.y() - minY) * scale + offsetY);

      qDebug() << position.x();

    }
    return vertices;
  }
};
#endif  // GRAPHFORCES_H
