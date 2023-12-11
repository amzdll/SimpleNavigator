/********************************************************************************
** Form generated from reading UI file 'interaction_panel.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERACTION_PANEL_H
#define UI_INTERACTION_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InteractionPanel
{
public:
    QPushButton *OpenGraph;
    QPushButton *pushButton_4;
    QPushButton *DFS;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;

    void setupUi(QWidget *InteractionPanel)
    {
        if (InteractionPanel->objectName().isEmpty())
            InteractionPanel->setObjectName(QString::fromUtf8("InteractionPanel"));
        InteractionPanel->resize(500, 900);
        OpenGraph = new QPushButton(InteractionPanel);
        OpenGraph->setObjectName(QString::fromUtf8("OpenGraph"));
        OpenGraph->setGeometry(QRect(12, 42, 471, 51));
        pushButton_4 = new QPushButton(InteractionPanel);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(200, 354, 100, 32));
        DFS = new QPushButton(InteractionPanel);
        DFS->setObjectName(QString::fromUtf8("DFS"));
        DFS->setGeometry(QRect(100, 140, 281, 32));
        pushButton_3 = new QPushButton(InteractionPanel);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(200, 250, 100, 32));
        pushButton_5 = new QPushButton(InteractionPanel);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(200, 458, 100, 32));
        pushButton_6 = new QPushButton(InteractionPanel);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(200, 562, 100, 32));
        pushButton_7 = new QPushButton(InteractionPanel);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(200, 666, 100, 32));
        pushButton_8 = new QPushButton(InteractionPanel);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(200, 770, 100, 32));

        retranslateUi(InteractionPanel);

        QMetaObject::connectSlotsByName(InteractionPanel);
    } // setupUi

    void retranslateUi(QWidget *InteractionPanel)
    {
        InteractionPanel->setWindowTitle(QCoreApplication::translate("InteractionPanel", "Form", nullptr));
        OpenGraph->setText(QCoreApplication::translate("InteractionPanel", "Open graph", nullptr));
        pushButton_4->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        DFS->setText(QCoreApplication::translate("InteractionPanel", "DFS", nullptr));
        pushButton_3->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        pushButton_7->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        pushButton_8->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InteractionPanel: public Ui_InteractionPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERACTION_PANEL_H
