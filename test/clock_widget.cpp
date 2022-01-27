#include "clock_widget.h"
#include "ui_clock_widget.h"

clock_widget::clock_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clock_widget)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &clock_widget::showTime);
    timer->start(1000);
    showTime();
    setWindowTitle(tr("Digital Clock"));
    resize(150, 60);
}

clock_widget::~clock_widget()
{
    delete ui;
}

void clock_widget::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdNumber->display(text);
}

