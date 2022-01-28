#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置行数列数。必要操作！
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(11);

    //设置水平表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别");

    //设置正文
    QStringList nameList;
    nameList<< "亚瑟"<< "赵云"<< "张飞"<< "关羽" << "花木兰";
    QList<QString> sexList;
    sexList << "男"<< "男"<< "男"<< "男"<< "女";

    for(int i = 0 ; i < 5 ;i ++)
    {//setItem(行号，列号，文本)
        int col = 0;
        ui->tableWidget->setItem(i,col++, new QTableWidgetItem(nameList[i]));
        ui->tableWidget->setItem(i,col++, new QTableWidgetItem(sexList.at(i)));
        //int 转 QString
        ui->tableWidget->setItem(i,col++, new QTableWidgetItem( QString::number(i+18)));
    }
}

Widget::~Widget()
{
    delete ui;
}

