#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <math.h>
#define _USE_MATH_DEFINES
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMainWindow>
#include <Windows.h>
#include <winddi.h>
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

//#pragma comment  (lib, "User32.lib")
//#pragma comment  (lib, "gdi32.lib")

//#include <QColor>
//#include <QScreen>
//#include <QPixmap>
//#include <QScreen>
//#include <QApplication>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPointF mouse;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QPointF> already = {QPointF(439, 177)};
    int xxx = 0;
    bool IsPoint(QPointF center, QPointF mouse);//捕捉点，允许点击误差
    bool OnSegement(QPointF p1, QPointF p2, QPointF mouse);//捕捉线
    bool IsPointInPolygon(QPointF& vtPoint, QVector<QPointF>& vecPoints);//捕捉多边形

    void BoundarySeedFill(int x, int y, QColor new_color, QVector<QPointF>& vecPoints);

    void SetPixelColor(int x, int y, QColor new_color);

    //    QColor GetPixelColor(int x, int y){
    //        //QString text;
    //        QScreen *screen = QGuiApplication::primaryScreen();
    //        QPixmap p = screen->grabWindow();
    //        QImage image = p.toIzzzmage();
    //        QColor color = image.pixel(x, y);
    //        return color;
    //        //return text = QString("RGB: %1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
    //    }

    void init7(); //初始化裁剪矩形框

    int encode(int x,int y,int XL,int XR,int YB,int YT);//Cohen_Sutherland编码


    //绘制直线算法
    void DDA_Line();
    void Bresenham();
    void MPL();

    //绘制圆算法
    void MPC();
    void DDA_Circle();
    void Bresenham_Circle();

    //目标选中算法
    void IdentifyObject(QPointF mouse);
    void FillAlgorithm(QPointF mouse);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* e);
    void complete_circle(int x, int y);

    //裁剪算法
    void Cohen_Sutherland(int x1,int y1,int x2,int y2,int XL=200,int XR=500,int YB=150,int YT=300);
    void Liang_Barsky(float x1,float y1,float x2,float y2,float XL=200,float XR=500,float YB=150,float YT=300);
protected:
    QVector<QVector<int> > direction_8 = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
    int menu = 0;
    int count = 0;
    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;

    //DDA数据成员
    //length必须是浮点数，不然整数除以整数变成整除了，斜率就会出问题

private slots:
    void on_actionDDA_triggered();

    void on_action_MPL_triggered();

    void on_actionMPC_triggered();

    void on_actionIdentifyObjects_triggered();

    void on_actionBoundary_Fill_Algorithm_triggered();

    void on_actionCohen_Sutherland_triggered();

    void on_action_Bresenham_triggered();

    void on_actionDDA_2_triggered();

    void on_actionBresenham_triggered();

    void on_actionLiang_Barsky_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
