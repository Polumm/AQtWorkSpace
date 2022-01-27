/********************************************************************************
** Form generated from reading UI file 'clock_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCK_WIDGET_H
#define UI_CLOCK_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clock_widget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdNumber;

    void setupUi(QWidget *clock_widget)
    {
        if (clock_widget->objectName().isEmpty())
            clock_widget->setObjectName(QString::fromUtf8("clock_widget"));
        clock_widget->resize(400, 300);
        verticalLayout = new QVBoxLayout(clock_widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(clock_widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setFrameShape(QFrame::Box);
        lcdNumber->setDigitCount(8);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(lcdNumber);


        verticalLayout->addWidget(widget);


        retranslateUi(clock_widget);

        QMetaObject::connectSlotsByName(clock_widget);
    } // setupUi

    void retranslateUi(QWidget *clock_widget)
    {
        clock_widget->setWindowTitle(QCoreApplication::translate("clock_widget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class clock_widget: public Ui_clock_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCK_WIDGET_H
