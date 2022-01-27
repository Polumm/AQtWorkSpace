#ifndef CLOCK_WIDGET_H
#define CLOCK_WIDGET_H
#include <QWidget>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>

namespace Ui {
class clock_widget;
}

class clock_widget : public QWidget
{
    Q_OBJECT

public:
    explicit clock_widget(QWidget *parent = nullptr);
    ~clock_widget();
    void showTime();

private slots:

private:
    Ui::clock_widget *ui;
};




#endif // CLOCK_WIDGET_H
