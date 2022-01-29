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
    //构造画家对象，同时指定绘图设备
    QPainter paint(this);

    //构造画笔,构造画刷 注意借助提示+帮助文档选择合适的样式
    QPen pen(Qt::darkGray, 3, Qt::DashLine, Qt::FlatCap);
    QBrush brush(Qt::green, Qt::DiagCrossPattern);

    //将画笔、画刷给画家
    paint.setPen(pen);
    paint.setBrush(brush);

    //几何绘制
    //画线
    paint.drawLine(0, 0, 100, 100);
    //画椭圆
    paint.drawEllipse(100, 100, 70, 50);
    //画矩形
    paint.drawRect(20, 20, 50, 50);
    paint.brush();

    QPainter painter(this);
    QPixmap pix = QPixmap(":/Image/Luffy.png");

   //如果超出屏幕 从0开始
    if(posX >= this->width())
    {
        posX = -pix.width();
    }

    painter.drawPixmap(posX,0,pix);


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

