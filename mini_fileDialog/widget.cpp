#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    //文件管理对话框，获取文件路径字符串
    QString path = QFileDialog::getOpenFileName(this, "选择文件", "D:\\AQtWorkSpace");
    //将路径字符串在lineEdit中展示
    ui->lineEdit_2->setText(path);

    //Qfile读文件
    //1、读入文件路径,创建file对象
    QFile file(path);
    //2、设置打开方式
    file.open(QIODevice::ReadOnly);
    //3、两种读入方式，readAll或者迭代readLine()
    //QByteArray array =  file.readAll();
    //逐行读直至结束.atEnd()
    QByteArray array;
    while(!file.atEnd())
    {
        array += file.readLine();   //按行读
    }
    //将读入的数据放入textEdit展示
    ui->textEdit->setText(array);
    //编码格式类Qt6没有codec注意学习一下
    //QTextCodec * codec = QTextCodec::codecForName("gbk");
    //ui->textEdit->setText( codec->toUnicode(array)  );
    //对文件对象进行关闭
    file.close();
    //进行写文件
    //file.open(QIODevice::Append); //用追加方式进行写
    //file.write("啊啊啊啊啊");
    //file.close();

    //QFileInfo 文件信息类qDebug直接输出到控制台
    QFileInfo info(path);

    qDebug() << "大小：" << info.size() << " 后缀名：" << info.suffix() << " 文件名称："<<info.fileName() << " 文件路径："<< info.filePath();
    qDebug() << "创建日期：" << info.birthTime().toString("yyyy/MM/dd hh:mm:ss");
    qDebug() << "最后修改日期："<<info.lastModified().toString("yyyy-MM-dd hh:mm:ss");
}

