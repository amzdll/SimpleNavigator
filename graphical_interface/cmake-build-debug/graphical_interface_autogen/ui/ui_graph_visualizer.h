/********************************************************************************
** Form generated from reading UI file 'graph_visualizer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_VISUALIZER_H
#define UI_GRAPH_VISUALIZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphVisualizer
{
public:

    void setupUi(QWidget *GraphVisualizer)
    {
        if (GraphVisualizer->objectName().isEmpty())
            GraphVisualizer->setObjectName(QString::fromUtf8("GraphVisualizer"));
        GraphVisualizer->resize(900, 900);

        retranslateUi(GraphVisualizer);

        QMetaObject::connectSlotsByName(GraphVisualizer);
    } // setupUi

    void retranslateUi(QWidget *GraphVisualizer)
    {
        GraphVisualizer->setWindowTitle(QCoreApplication::translate("GraphVisualizer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphVisualizer: public Ui_GraphVisualizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_VISUALIZER_H
