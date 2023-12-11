/********************************************************************************
** Form generated from reading UI file 'interaction_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERACTION_PANEL_H
#define UI_INTERACTION_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InteractionPanel
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;

    void setupUi(QWidget *InteractionPanel)
    {
        if (InteractionPanel->objectName().isEmpty())
            InteractionPanel->setObjectName(QString::fromUtf8("InteractionPanel"));
        InteractionPanel->resize(500, 900);
        widget = new QWidget(InteractionPanel);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 0, 461, 901));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        verticalLayout->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(widget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        verticalLayout->addWidget(pushButton_8);


        retranslateUi(InteractionPanel);

        QMetaObject::connectSlotsByName(InteractionPanel);
    } // setupUi

    void retranslateUi(QWidget *InteractionPanel)
    {
        InteractionPanel->setWindowTitle(QCoreApplication::translate("InteractionPanel", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("InteractionPanel", "PushButton", nullptr));
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
