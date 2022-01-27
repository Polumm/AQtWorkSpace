/********************************************************************************
** Form generated from reading UI file 'digitalclock.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIGITALCLOCK_H
#define UI_DIGITALCLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DigitalClock
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *lcdNumber;

    void setupUi(QDialog *DigitalClock)
    {
        if (DigitalClock->objectName().isEmpty())
            DigitalClock->setObjectName(QString::fromUtf8("DigitalClock"));
        DigitalClock->resize(222, 125);
        horizontalLayout = new QHBoxLayout(DigitalClock);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        widget = new QWidget(DigitalClock);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        horizontalLayout_2->addWidget(lcdNumber);


        horizontalLayout->addWidget(widget);


        retranslateUi(DigitalClock);

        QMetaObject::connectSlotsByName(DigitalClock);
    } // setupUi

    void retranslateUi(QDialog *DigitalClock)
    {
        DigitalClock->setWindowTitle(QCoreApplication::translate("DigitalClock", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DigitalClock: public Ui_DigitalClock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIGITALCLOCK_H
