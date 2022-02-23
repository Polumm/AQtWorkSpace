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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDDA;
    QAction *action_MiddlePoint;
    QAction *action_Bresenham;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuDrawDemo;
    QMenu *menuDrawLine;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionDDA = new QAction(MainWindow);
        actionDDA->setObjectName(QString::fromUtf8("actionDDA"));
        action_MiddlePoint = new QAction(MainWindow);
        action_MiddlePoint->setObjectName(QString::fromUtf8("action_MiddlePoint"));
        action_Bresenham = new QAction(MainWindow);
        action_Bresenham->setObjectName(QString::fromUtf8("action_Bresenham"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        menuDrawDemo = new QMenu(menubar);
        menuDrawDemo->setObjectName(QString::fromUtf8("menuDrawDemo"));
        menuDrawLine = new QMenu(menuDrawDemo);
        menuDrawLine->setObjectName(QString::fromUtf8("menuDrawLine"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDrawDemo->menuAction());
        menuDrawDemo->addAction(menuDrawLine->menuAction());
        menuDrawLine->addAction(actionDDA);
        menuDrawLine->addAction(action_MiddlePoint);
        menuDrawLine->addAction(action_Bresenham);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionDDA->setText(QCoreApplication::translate("MainWindow", "DDA", nullptr));
        action_MiddlePoint->setText(QCoreApplication::translate("MainWindow", "MPL", nullptr));
        action_Bresenham->setText(QCoreApplication::translate("MainWindow", " Bresenham", nullptr));
        menuDrawDemo->setTitle(QCoreApplication::translate("MainWindow", "DrawDemo", nullptr));
        menuDrawLine->setTitle(QCoreApplication::translate("MainWindow", "DrawLine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
