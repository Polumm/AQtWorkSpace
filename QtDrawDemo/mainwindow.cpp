#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menu = 0;
    count = 0;
    startX = 0;
    startY = 0;
    endX = 0;
    endY = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //DDA
   if (menu == 1 && count == 2)
   {
       //判断哪个变量为增量
       if(abs(endX - startX) > (endY - startY))
           length = abs(endX - startX);
       else
           length = abs(endY - startY);
       //设置增量，一个为1，一个为k
       dx = (endX - startX) / length;
       dy = (endY - startY) / length;
       x = startX;
       y = startY;
       int i = 1;
       //画直线
       for(i; i < length; i++)
       {
         painter.drawPoint(int(x + 0.5), int(y + 0.5));
         x += dx;
         y += dy;
       }
   }
   //MPL
   if (menu == 2 && count == 2)
   {
       int x = startX, y = startY;
           int a = startY - endY;
           int b = endX - startX;
           int cx = (b >= 0 ? 1 : (b = -b, -1));
           int cy = (a <= 0 ? 1 : (a = -a, -1));
           painter.drawPoint(x, y);
           int d, d1, d2;
           if (-a <= b) // 斜率绝对值 <= 1
           {
               d = a + a + b;
               d1 = a + a;
               d2 = a + a + b + b;
               while (x != endX)
               {
                   if (d < 0)
                   {
                       y += cy;
                       d += d2;
                   }
                   else
                   {
                       d += d1;
                   }
                   x += cx;
           painter.drawPoint(x, y);
               }
           }
           else // 斜率绝对值 > 1
           {
               d = a + b + b;
               d1 = b + b;
               d2 = a + a + b + b;
               if (d < 0)
               {
                   d += d1;
               }
               else
               {
                   x += cx;
                   d += d2;
               }
               y += cy;
           painter.drawPoint(x, y);
           }
   }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(count == 2)
            count = 0;
        count++;
        if(menu == 1 && count == 1)
        {
            startX = event->position().x();
            startY = event->position().y();
        }
        if(menu == 1 && count == 2)
        {
            endX = event->position().x();
            endY = event->position().y();
        }
        update();
    }
}

void MainWindow::on_actionDDA_triggered()
{
    menu = 1;
}


void MainWindow::on_action_MiddlePoint_triggered()
{
    menu = 2;
}

