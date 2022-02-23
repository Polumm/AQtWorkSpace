#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPainter>
#include<QMouseEvent>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int menu;
    int count;
    int startX;
    int startY;
    int endX;
    int endY;
    //length必须是浮点数，不然整数除以整数变成整除了，斜率就会出问题
    float length;
    float x, y, dx, dy;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);

private slots:
    void on_actionDDA_triggered();

    void on_action_MiddlePoint_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
