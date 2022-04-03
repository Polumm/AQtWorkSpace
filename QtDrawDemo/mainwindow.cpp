#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("");
    ui->label_2->setText("");
    this->setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(menu == 7 || menu == 10) //初始化裁剪矩形框
    {
        init7();
    }
    if(count == 2)
    {
        switch (menu) //双击逻辑的事件
        {
        case 1: DDA_Line(); break;
        case 2: MPL(); break;
        case 3: Bresenham(); break;
        case 4: MPC(); break;
        case 7: Cohen_Sutherland(startX,startY,endX,endY,200,500,150,300); break;
        case 8: DDA_Circle(); break;
        case 9: Bresenham_Circle(); break;
        case 10:Liang_Barsky(startX,startY,endX,endY,200,500,150,300); break;
        }
    }
    if(menu == 5) //识别多边形，单击逻辑
    {
        IdentifyObject(mouse);
    }
    if(menu == 6) //填充算法，单击逻辑
    {
        FillAlgorithm(mouse);
    }
}

void MainWindow::init7() //初始化裁剪窗口
{
    QPainter painter(this);
    QPen pen(Qt::black,1);
    painter.setPen(pen);
    painter.drawRect(200, 150, 300, 150);
}

int MainWindow::encode(int x,int y,int XL,int XR,int YB,int YT)//Cohen_Sutherland编码
{
    int c=0;
    if(x<XL) c|=LEFT;
    if(x>XR) c|=RIGHT;
    if(y<YB) c|=BOTTOM;
    if(y>YT) c|=TOP;
    return c;
}

void MainWindow::Cohen_Sutherland(int x1,int y1,int x2,int y2,int XL,int XR,int YB,int YT)
{
    QPainter painter(this);
    int code1,code2,code,x,y;
    code1=encode(x1,y1,XL,XR,YB,YT);
    code2=encode(x2,y2,XL,XR,YB,YT);
    while((code1 != 0) || (code2 != 0))
    {
        if((code1 & code2) != 0)
        {
            QPen pen(Qt::green,2);
            painter.setPen(pen);
            painter.drawLine(x1,y1,x2,y2);//如果直线在裁剪窗口外就用绿色画出
            return;
        }
        if(code1 != 0) code=code1;
        else code=code2;
        if((LEFT & code) != 0)
        {
            x=XL;
            y=y1+(y2-y1)*(XL-x1)/(x2-x1);
        }
        else if((RIGHT & code) != 0)
        {
            x=XR;
            y=y1+(y2-y1)*(XR-x1)/(x2-x1);
        }
        else if((BOTTOM & code) != 0)
        {
            y=YB;
            x=x1+(x2-x1)*(YB-y1)/(y2-y1);
        }
        else if((TOP & code) != 0)
        {
            y=YT;
            x=x1+(x2-x1)*(YT-y1)/(y2-y1);
        }
        if(code == code1)
        {
            x1=x; y1=y; code1=encode(x,y,XL,XR,YB,YT);
        }
        else
        {
            x2=x; y2=y; code2=encode(x,y,XL,XR,YB,YT);
        }
    }
    QPen pen(Qt::red,2);
    painter.setPen(pen);
    painter.drawLine(x1,y1,x2,y2);//将裁减的直线用红色标注
    return;
}

void MainWindow::Liang_Barsky(float x1,float y1,float x2,float y2,float XL,float XR,float YB,float YT)
{
    QPainter painter(this);
    int dx = x2 - x1;
    int dy = y2 - y1;
    int q[5];
    int p[5];//q[0]、p[0]弃用

    p[1] = -dx; q[1] = x1 - XL;
    p[2] = dx; q[2] = XR - x1;
    p[3] = -dy; q[3] = y1 - YB;
    p[4] = dy; q[4] = YT - y1;

    //初始时，u1、u2分别表示(x1,y1)、(x2,y2)两个点的参数
    double u1 = 0, u2 = 1;
    for (int i = 1; i <= 4; i++) {
        if (p[i] < 0) {
            u1 = max(u1, ((double)q[i]) / p[i]);
        }
        else if (p[i] > 0) {
            u2 = min(u2, ((double)q[i]) / p[i]);
        }
        else if (p[i]==0&&q[i]<0) {
            return;
        }

        //判断是否舍弃
        if (u1 > u2) {
            return;
        }
    }
    //qRound即四舍五入取整
    int new_x1 = qRound(x1 + u1 * dx);
    int new_y1 = qRound(y1 + u1 * dy);
    int new_x2 = qRound(x1 + u2 * dx);
    int new_y2 = qRound(y1 + u2 * dy);
    x1 = new_x1;
    y1 = new_y1;
    x2 = new_x2;
    y2 = new_y2;

    //根据现在的x1,y1,x2,y2画线
    QPen pen(Qt::red,2);
    painter.setPen(pen);
    painter.drawLine(x1,y1,x2,y2);//将裁减的直线用红色标注
    return;
}



void MainWindow::SetPixelColor(int x, int y, QColor new_color)
{
    QPainter painter(this);
    QPen pen(new_color,1);
    painter.setPen(pen);
    painter.drawPoint(x, y);
}


void MainWindow::mouseMoveEvent(QMouseEvent* e)
{
    QString text=QString("Mouse move :(%1 ,%2)").arg(e->x()).arg(e->y() - 22);
    ui->label->setText(text);
    update();
}


void MainWindow::DDA_Line()
{
   float length;
   float x, y, dx, dy;
   QPainter painter(this);
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


void MainWindow::Bresenham()
{
    QPainter painter(this);
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    int x = startX;
    int y = startY;
    int stepx = (startX < endX) ? 1 : -1;
    int stepy = (startY < endY) ? 1 : -1;
    int e;
    if (dx > dy) {
        e = dy * 2 - dx;
        for (int i = 0; i <= dx; i++) {
            painter.drawPoint(x,y);
            x += stepx;
            e += 2 * dy;
            if (e > 0) {
                e -= 2 * dx;
                y += stepy;
            }
        }
    }
    else {
        e = dx * 2 - dy;
        for (int i = 0; i <= dy; i++)
        {
            painter.drawPoint(x,y);
            y += stepy;
            e += 2 * dx;
            if (e > 0)
            {
                e -= 2 * dy;
                x += stepx;
            }
        }
    }
}



void MainWindow::complete_circle(int x, int y)
{
    QPainter painter(this);
    //以第一次点击的坐标为新的逻辑原点，坐标变换，相对位置不变
    painter.translate(startX, startY);
    painter.drawPoint(x, y);
    painter.drawPoint(x, -y);
    painter.drawPoint(-x, y);
    painter.drawPoint(-x, -y);
    painter.drawPoint(y, x);
    painter.drawPoint(-y, x);
    painter.drawPoint(y, -x);
    painter.drawPoint(-y, -x);
}

void MainWindow::MPL()
{
    QPainter painter(this);
    int x; int y;
       x = startX,
       y = startY;
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
           while (y != endY)
           {
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


void MainWindow::DDA_Circle()
{
    QPainter painter(this);
    float r = sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));
    QString text=QString("Radius :%1").arg(QString::number(r));
    QString text2=QString("center :(%1 ,%2)").arg(startX).arg(startY);
    ui->label_3->setText(text);
    ui->label_2->setText(text2);

    double i, steps;
    double da, radin;
    da = 1 / (r+1);
    radin = M_PI / 4;
    steps = radin / da;
    double x = 0;
    double y = r;
    painter.drawPoint(startX, startY);
    for (i = 0; i<= steps; i++)
    {
        complete_circle(x, y);
        x = x - y* da; y = y + x * da;
    }

}


void MainWindow::Bresenham_Circle()
{
    QPainter painter(this);
    float r = sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));
    QString text=QString("Radius :%1").arg(QString::number(r));
    QString text2=QString("center :(%1 ,%2)").arg(startX).arg(startY);
    ui->label_3->setText(text);
    ui->label_2->setText(text2);

    int x, y, delta, d1, d2, dir; x = 0; y = r;
    delta = 2 * (1 - r);
    while (y >= 0)
    {
        complete_circle(x, y);
        if (delta < 0)
        {
            d1 = 2 * (delta + y) - 1;
            if (d1 <= 0) dir = 1;
            else dir = 2;
        }
        else if (delta > 0)
        {
            d2 = 2 * (delta - x) - 1;
            if (d2 <= 0) dir = 2;
            else dir = 3;
        }
        else dir = 2;
        switch (dir)
        {
            case 1:
                x++;
                delta += 2 * x + 1;
                break;
            case 2:
                x++;
                y--;
                delta += 2 * (x - y + 1) + 1;
                break;
            case 3:
                y--;
                delta += -2 * y + 1;
                break;
        }
    }
}

void MainWindow::MPC()
{
    QPainter painter(this);
    float r = sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));
    QString text=QString("Radius :%1").arg(QString::number(r));
    QString text2=QString("center :(%1 ,%2)").arg(startX).arg(startY);
    ui->label_3->setText(text);
    ui->label_2->setText(text2);
    int x = 0;
    int y = r;
    int d = 1 - r;
    painter.drawPoint(startX, startY);
    while(x < y)
    {
        complete_circle(x, y);
        if(d < 0)
        {
            d += 2 * x + 3;
            x++;
        }
        else
        {
            d += 2 * (x - y) + 5;
            x++;
            y--;
        }
    }
}

void MainWindow::IdentifyObject(QPointF mouse)//捕捉点线面，并高亮显示
{
    QPainter painter(this);
    QPen pen(Qt::lightGray,1);
    QBrush brush(Qt::yellow);
    pen.setWidth(1);
    QPoint p1(40, 40);
    QPoint p2(220, 220);
    QPointF p3(157, 419);
    painter.setPen(pen);

    painter.drawEllipse(p3, 3, 3);//把点化成圆,为了便于观察以及实现允许一定的点击误差
    painter.drawLine(p1,p2);//画直线
    static const QPointF points[6] = {QPointF(439, 177), QPointF(625, 191), QPointF(610, 291), QPointF(667, 409), QPointF(447, 387), QPointF(531, 256)};
    QVector<QPointF> vector = {QPointF(439, 177), QPointF(625, 191), QPointF(610, 291), QPointF(667, 409), QPointF(447, 387), QPointF(531, 256)};
    painter.drawPolygon(points, 6);
    ui->label_2->setText("");

    if(IsPoint(p3, mouse))
    {
        ui->label_2->setText("Catched Point!");
        painter.setBrush(brush);
        painter.drawEllipse(p3, 3, 3);
    }
    if(OnSegement(p1, p2, mouse))
    {
        ui->label_2->setText("Catched Line!");
        pen.setWidth(5);
        pen.setColor(Qt::yellow);
        painter.setPen(pen);
        painter.drawLine(p1,p2);
    }
    if(IsPointInPolygon(mouse, vector))
    {
        ui->label_2->setText("Catched Polygon!");
        painter.setBrush(brush);
        painter.drawPolygon(points, 6);
    }
}

bool MainWindow::IsPoint(QPointF center, QPointF mouse)//捕捉点，允许点击误差
{
    if( sqrt((mouse.x() - center.x()) * (mouse.x() - center.x()) + (mouse.y() - center.y()) * (mouse.y() - center.y())) <= 3)
        return true;
    return false;
}
bool MainWindow::OnSegement(QPointF p1, QPointF p2, QPointF mouse)//捕捉线
{
    if((mouse.x()-p1.x())*(p2.y()-p1.y())==(p2.x()-p1.x())*(mouse.y()-p1.y())&&qMin(p1.x(),p2.x())<=mouse.x()&&mouse.x()<=qMax(p1.x(),p2.x())&&qMin(p1.y(),p2.y())<=mouse.y()&&mouse.y()<=qMax(p1.y(),p2.y()))
        return true;
    return false;
}
bool MainWindow::IsPointInPolygon(QPointF& vtPoint, QVector<QPointF>& vecPoints)//捕捉多边形
{
    /*
    射线法：
        从目标点出发引一条射线，看这条射线和多边形所有边的交点数目。
            如果有奇数个交点，则说明在内部
            如果有偶数个交点，则说明在外部
    */
    bool bResult = false; //判断结果（true；点落在多边形内；false:点未落在多边形内）
    int nSize = vecPoints.size();
    int j = nSize - 1;//nSize -1 是多边形的最后一个顶点
    for (int i = 0; i < nSize; i++)
    {
        //判断点是否在线段的两侧
        if ((vecPoints[i].y() < vtPoint.y() && vecPoints[j].y() >= vtPoint.y()) || (vecPoints[j].y() < vtPoint.y() && vecPoints[i].y() >= vtPoint.y()))
        {
            //根据两点式方程计算出过点P且平行于X轴的直线与线段的交点，两点式方程：x = x1 +  (y - y1) * (x2 - x1) / (y2 - y1);
            if (vecPoints[i].x() + (vtPoint.y() - vecPoints[i].y()) * (vecPoints[j].x() - vecPoints[i].x()) / (vecPoints[j].y() - vecPoints[i].y()) < vtPoint.x())
                bResult = !bResult;
        }

        //进行下一线段判断
        j = i;
    }

    return bResult;
}


void MainWindow::FillAlgorithm(QPointF mouse)//填充算法
{
    QPainter painter(this);
    QPen pen(Qt::lightGray,1);
    painter.setPen(pen);
    pen.setWidth(1);
//    static const QPointF points[3] = {QPointF(280, 253), QPointF(259, 295), QPointF(361, 296)};
//    QVector<QPointF> vector = {QPointF(280, 253), QPointF(259, 295), QPointF(361, 296)};
    static const QPointF points[3] = {QPointF(280, 213), QPointF(259, 295), QPointF(361, 296)};
    QVector<QPointF> vector = {QPointF(280, 213), QPointF(259, 295), QPointF(361, 296)};
    painter.drawPolygon(points, 3);
    ui->label_2->setText("");


    if(IsPointInPolygon(mouse, vector))
    {
        already.clear();
        xxx = 0;
        BoundarySeedFill(mouse.rx(), mouse.ry(), Qt::green, vector);
    }
    QString text2=QString("Seeds Number :%1").arg(xxx);
    ui->label_2->setText(text2);
    qDebug() << xxx;
}

void MainWindow::BoundarySeedFill(int x, int y, QColor new_color, QVector<QPointF>& vecPoints)
{
    QPointF CurPoint(x,y);
    if(IsPointInPolygon(CurPoint, vecPoints) && xxx < 6000 && !already.contains(CurPoint))
    {
        qDebug() << CurPoint.x() <<" "<< CurPoint.y();
        already.append(CurPoint);
        SetPixelColor(x,y,Qt::green);
        xxx++;
        for (int i = 0; i < 8; ++i)
        {
            BoundarySeedFill(x + direction_8[i][0], y + direction_8[i][1], new_color, vecPoints);
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
        if(menu != 0 && count == 1)
        {
            startX = event->position().x();
            startY = event->position().y();
        }
        if(menu != 0 && count == 2)
        {
            endX = event->position().x();
            endY = event->position().y();
        }
        if(menu == 5){
            mouse.setX(event->position().x());
            mouse.setY(event->position().y());
            qDebug() << event->position().x() <<" "<< event->position().y();
        }
        if(menu == 6){
            mouse.setX(event->position().x());
            mouse.setY(event->position().y());
        }
        update();//mousepressMoves时刷新就够了
    }
}

void MainWindow::on_actionDDA_triggered()
{
    menu = 1;
}


void MainWindow::on_action_MPL_triggered()
{
   menu = 2;
}

void MainWindow::on_action_Bresenham_triggered()
{
    menu = 3;
}

void MainWindow::on_actionMPC_triggered()
{
    menu = 4;
}


void MainWindow::on_actionIdentifyObjects_triggered()
{
    menu = 5;
}


void MainWindow::on_actionBoundary_Fill_Algorithm_triggered()
{
    menu = 6;
}


void MainWindow::on_actionCohen_Sutherland_triggered()
{
    menu = 7;
}


void MainWindow::on_actionDDA_2_triggered()
{
    menu = 8;
}


void MainWindow::on_actionBresenham_triggered()
{
    menu = 9;
}


void MainWindow::on_actionLiang_Barsky_triggered()
{
    menu = 10;
}

