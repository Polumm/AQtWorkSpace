/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDDA;
    QAction *action_Bresenham;
    QAction *action_MPL;
    QAction *actionMPC;
    QAction *actionIdentifyObjects;
    QAction *actionBoundary_Fill_Algorithm;
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menuDrawDemo;
    QMenu *menuDrawLine;
    QMenu *menu_DrawCircle;
    QMenu *menuInteractDemo;
    QMenu *menuFill_Algorithm;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionDDA = new QAction(MainWindow);
        actionDDA->setObjectName(QString::fromUtf8("actionDDA"));
        action_Bresenham = new QAction(MainWindow);
        action_Bresenham->setObjectName(QString::fromUtf8("action_Bresenham"));
        action_MPL = new QAction(MainWindow);
        action_MPL->setObjectName(QString::fromUtf8("action_MPL"));
        actionMPC = new QAction(MainWindow);
        actionMPC->setObjectName(QString::fromUtf8("actionMPC"));
        actionIdentifyObjects = new QAction(MainWindow);
        actionIdentifyObjects->setObjectName(QString::fromUtf8("actionIdentifyObjects"));
        actionBoundary_Fill_Algorithm = new QAction(MainWindow);
        actionBoundary_Fill_Algorithm->setObjectName(QString::fromUtf8("actionBoundary_Fill_Algorithm"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(550, 10, 211, 181));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        menuDrawDemo = new QMenu(menubar);
        menuDrawDemo->setObjectName(QString::fromUtf8("menuDrawDemo"));
        menuDrawLine = new QMenu(menuDrawDemo);
        menuDrawLine->setObjectName(QString::fromUtf8("menuDrawLine"));
        menu_DrawCircle = new QMenu(menuDrawDemo);
        menu_DrawCircle->setObjectName(QString::fromUtf8("menu_DrawCircle"));
        menuInteractDemo = new QMenu(menubar);
        menuInteractDemo->setObjectName(QString::fromUtf8("menuInteractDemo"));
        menuFill_Algorithm = new QMenu(menubar);
        menuFill_Algorithm->setObjectName(QString::fromUtf8("menuFill_Algorithm"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDrawDemo->menuAction());
        menubar->addAction(menuInteractDemo->menuAction());
        menubar->addAction(menuFill_Algorithm->menuAction());
        menuDrawDemo->addAction(menuDrawLine->menuAction());
        menuDrawDemo->addAction(menu_DrawCircle->menuAction());
        menuDrawLine->addAction(actionDDA);
        menuDrawLine->addAction(action_Bresenham);
        menuDrawLine->addAction(action_MPL);
        menu_DrawCircle->addAction(actionMPC);
        menuInteractDemo->addAction(actionIdentifyObjects);
        menuFill_Algorithm->addAction(actionBoundary_Fill_Algorithm);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionDDA->setText(QCoreApplication::translate("MainWindow", "DDA", nullptr));
        action_Bresenham->setText(QCoreApplication::translate("MainWindow", "Bresenham", nullptr));
        action_MPL->setText(QCoreApplication::translate("MainWindow", "MPL", nullptr));
        actionMPC->setText(QCoreApplication::translate("MainWindow", "MPC", nullptr));
        actionIdentifyObjects->setText(QCoreApplication::translate("MainWindow", "IdentifyObjects", nullptr));
        actionBoundary_Fill_Algorithm->setText(QCoreApplication::translate("MainWindow", "Boundary Fill Algorithm", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        menuDrawDemo->setTitle(QCoreApplication::translate("MainWindow", "DrawDemo", nullptr));
        menuDrawLine->setTitle(QCoreApplication::translate("MainWindow", "DrawLine", nullptr));
        menu_DrawCircle->setTitle(QCoreApplication::translate("MainWindow", "DrawCircle", nullptr));
        menuInteractDemo->setTitle(QCoreApplication::translate("MainWindow", "InteractDemo", nullptr));
        menuFill_Algorithm->setTitle(QCoreApplication::translate("MainWindow", "Fill Algorithm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
