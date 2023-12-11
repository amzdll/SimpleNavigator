/********************************************************************************
** Form generated from reading UI file 'graphical_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICAL_INTERFACE_H
#define UI_GRAPHICAL_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicalInterface
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *graph_visualizer;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *interaction_panel;

    void setupUi(QMainWindow *GraphicalInterface)
    {
        if (GraphicalInterface->objectName().isEmpty())
            GraphicalInterface->setObjectName(QString::fromUtf8("GraphicalInterface"));
        GraphicalInterface->resize(1400, 900);
        centralwidget = new QWidget(GraphicalInterface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 891, 901));
        graph_visualizer = new QVBoxLayout(verticalLayoutWidget);
        graph_visualizer->setObjectName(QString::fromUtf8("graph_visualizer"));
        graph_visualizer->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(888, 0, 511, 899));
        interaction_panel = new QVBoxLayout(verticalLayoutWidget_2);
        interaction_panel->setObjectName(QString::fromUtf8("interaction_panel"));
        interaction_panel->setContentsMargins(0, 0, 0, 0);
        GraphicalInterface->setCentralWidget(centralwidget);

        retranslateUi(GraphicalInterface);

        QMetaObject::connectSlotsByName(GraphicalInterface);
    } // setupUi

    void retranslateUi(QMainWindow *GraphicalInterface)
    {
        GraphicalInterface->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class GraphicalInterface: public Ui_GraphicalInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICAL_INTERFACE_H
