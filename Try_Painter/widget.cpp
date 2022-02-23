#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    //尝试用lamda表达式做
//    //点击移动按钮，移动图片
//    connect(ui->pushButton,&QPushButton::clicked,[=](){

//        posX+=20;
//        //如果要手动调用绘图事件 用update更新
//        update();
//    });

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter Painter1(this)  ;
      int x0=111,y0=222,x1=333,y1=55; //赋值
      float dy,dx,y,m,x;
      dx=x1-x0;
      dy=y1-y0;
      m=dy/dx; //斜率
      y=y0;
      for(x=x0;x<=x1;x++) //画点
      {
     Painter1.drawPoint(x,int(y+0.5)); //四舍五入
        y+=m;
      }

}
Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    posX+=20;
    //如果要手动调用绘图事件 用update更新
    update();
    QTimer * timer = new QTimer(this);
    timer->start(10);

    connect(timer,&QTimer::timeout,[=](){
        posX++;
        update();
    });
}

