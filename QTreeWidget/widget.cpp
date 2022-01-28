#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置水平头
    ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄介绍");

    //载入根节点
    QTreeWidgetItem* liItem = new QTreeWidgetItem(QStringList()<<"力量");
    QTreeWidgetItem* minItem = new QTreeWidgetItem(QStringList()<<"敏捷");
    QTreeWidgetItem* zhiItem = new QTreeWidgetItem(QStringList()<<"智力");
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(minItem);
    ui->treeWidget->addTopLevelItem(zhiItem);

    //载入子节点
    QTreeWidgetItem* hero1 = new QTreeWidgetItem(QStringList()<<"邱诚"<<"是个渣男");
    liItem->addChild(hero1);
}

Widget::~Widget()
{
    delete ui;
}

