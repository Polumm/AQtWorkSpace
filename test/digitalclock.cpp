#include "digitalclock.h"
#include "ui_digitalclock.h"
#include <QTime>
#include <QTimer>
#include <QLCDNumber>

DigitalClock::DigitalClock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DigitalClock)
{
    //用当前窗口指针创建ui对象
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //当前窗口自身(整体)的设置可以不用this
    setFixedSize(350,125);
    setWindowTitle(tr("Digital Clock"));
    //ui文件中设计的控件务必记得用ui对象调用！！！
    ui->lcdNumber->setFixedSize(300,60);
    ui->lcdNumber->setDigitCount(8);//注意留足展示位数
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);
    showTime();//这里最好先展示一下，否则会有信号等待延迟
}

void DigitalClock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if ((time.second() % 2) == 0)
        text[5] = ' ';
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdNumber->display(text);
}

DigitalClock::~DigitalClock()
{
    delete ui;
}
