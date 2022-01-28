/********************************************************************************
** Form generated from reading UI file 'testwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIDGET_H
#define UI_TESTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testWidget
{
public:

    void setupUi(QWidget *testWidget)
    {
        if (testWidget->objectName().isEmpty())
            testWidget->setObjectName(QString::fromUtf8("testWidget"));
        testWidget->resize(400, 300);

        retranslateUi(testWidget);

        QMetaObject::connectSlotsByName(testWidget);
    } // setupUi

    void retranslateUi(QWidget *testWidget)
    {
        testWidget->setWindowTitle(QCoreApplication::translate("testWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testWidget: public Ui_testWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIDGET_H
