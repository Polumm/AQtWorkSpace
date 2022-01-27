#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "digitalclock.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MyFirstPro");
    //this->setFixedSize(600,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->label1->setStyleSheet("color : blue");
    ui->label1->setText("HelloWorld");
    DigitalClock c;
    c.show();
    c.exec();
}

