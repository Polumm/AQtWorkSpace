## 新建项目

1、.pro = .sln

2、路径命名严格，请按照英文规范来

![image-20220127090625126](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220127090625126.png)

待学习：帮助文档的使用（done）

![image-20220127091732477](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220127091732477.png)

3、新增界面（建议添加**Qt设计器界面类**）

![image-20220127180021709](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220127180021709.png)

4.重构如果遇到问题，可以考虑

![image-20220128174543282](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220128174543282.png)

​		而如果他人的工程中需要资源文件构建，**还是老老实实shandow build，build directory填好工程文件所在路径就没问题**

5、有时会遇到Qt 5中的头文件\#include不到

一般都已经安装了Qt5 Compatibility Module了，所以原因往往是没有在.pro中添加

```c++
QT += core5compat
```

![image-20220128215143873](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220128215143873.png)

## 窗口

### **三大基类**：QWidget, QMainWindow, QDialog

> Qt一个类对应一个头文件，类名就是头文件名，且Qt系统提供的标准类名声明头文件没有.h后缀

#### 使用原则

- 如果需要嵌入到其他窗体中，则基于QWidget创建。
- 如果是顶级对话框，则基于QDialog创建。
- 如果是主窗体，则基于QMainWindow创建。（提供有菜单条、工具栏、状态条的主应用程序窗口）

> QWidget类是所有用户界面对象的基类，进而派生了QLabel、QPushButton、QCheckBox等等。
>
> 窗口部件是用户界面的一个原子：它从窗口系统接收鼠标、键盘和其它事件，并且将自己的表现形式绘制在屏幕上。每一个窗口部件都是矩形，并且它们按Z轴顺序排列。==**在ui设计过程中常常将控件拖入widget框中，然后进行合理布局。**==



1、QApplication应用程序类

- 管理图形用户界面应用程序的控制流和主要设置。

- 是Qt的整个后台管理的命脉它**包含主事件循环**，在其中来自窗口系统和其它资源的**所有事件处理和调度**。它也处理**应用程序的初始化和结束**，并且**提供对话管理**。

- 对于任何一个使用Qt的图形用户界面应用程序，都正好存在一个QApplication 对象，而不论这个应用程序在同一时间内是不是有0、1、2或更多个窗口。

  a.exec()：

​		**程序进入消息循环**，**等待对用户输入进行响应**。这里main()把控制权转交给Qt，Qt完成事件处理工作，当应用程序退出的时候exec()的值就会返回。**在exec()中，Qt接受并处理用户和系统的事件并且把它们传递给适当的窗口部件。**



## 布局管理

需求：

​		实现整体布局并自动对齐，标准化页面布局，**优化控件间距随父窗口大小的变化情况**

类型：

​		水平、垂直、栅格（网格型）

方法：

- 将控件拖入widget整体布局，使用弹簧调整内部布局（弹簧加不进来大概率因为布局类型选错了）

- 对于个别控件，sizePolicy可以选择expanding或者fixed

- 弹簧也可以在sizeHint里调整大小
- 对于QLabel，==alignment可以设置对齐方式==



## 项目实战：界面时钟程序

### 覆盖知识点

  - 接触Qtimer、QLCDNumber 等模块
  - **自定义槽函数**实现showTime()功能
  - connect()收发消息，联动QtDesigner工具快速设计界面
  - 界面设计的常用属性

### 实现思路

​	1、获取当前时间		Qtime.currentTime()

​	2、格式化字符串之后display展示		QString text = time.toString("hh:mm:ss");

​	3、定时器每秒触发timeout信号，实现定时刷新

```c++
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);
    showTime();
```

### 设计流程

​	1、定义槽函数showTime()	注意：头文件声明、源文件和include引用头文件对应好

```c++
void DigitalClock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    //冒号跳动效果
    if ((time.second() % 2) == 0)
        text[5] = ' ';
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    display(text);
}
```

​	2、源文件设计样式，connect关联，调用槽函数

```c++
DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setWindowTitle(tr("Digital Clock"));
    resize(300, 60);
    setSegmentStyle(Filled);//LCDNum的样式，ui设计中默认为filled
    setDigitCount(8);//注意留足展示位数

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);
    showTime();//这里最好先展示一下，否则会有信号等待延迟
}
```

### 知识整理

#### 1、QObject::connect()函数

**==实现了用信号触发执行槽函数的功能==**

connect()函数有且只能在QObject类里面和QObject派生类里面使用（如：widget，mainwindow，dialog），**自定义类里无效**。

```c++
static QMetaObject::Connection connect(const QObject *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);
```

函数参数详解：

- 参数1：消息发送对象
- 参数2：**来自**消息发送对象的一个信号（注意是指针，所以要**&** 注意标明**作用域**） e.g.  &QTimer::timeout
- 参数3：接收对象
- 参数4：接收对象的槽函数（用信号激活它）

#### 2、Qtime vs. Qtimer

最大的区别：

- QTime计时器不需要自己定义对象（类似于简单数据类型QTime time即可创建）而Qtimer需要定义对象，要new出来

  形如：QTimer *timer = new QTimer(this);

- QTime便于获取系统时间： QTime time = QTime::currentTime();

  而QTimer不断触发的是timeout信号，结合connect() 适合作为定时触发器：

  ```c++
  QTimer *timer = new QTimer(this);
      connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
  ```





## QListWidget

简单，略

## QTreewidget

QTreewidget样例如下：

![image-20220128180104542](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220128180104542.png)

所以设计流程如下：

1、设置（set）水平头（Header**Labels**）

```c++
//设置水平头
ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄介绍");
```

注：**QStringList**相当与集成度更高的List\<String\>

- 常规两行，简单声明 + 输入流式初始化

  ```c++
  QStringList heroL1;
  heroL1 << "刚被猪" << "前排坦克，能在吸收伤害的同时造成可观的范围输出";
  ```

  

- 辅助其他对象构造，只负责**快速、格式化打入(分栏效果)**文本的话：

  ```c++
  ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄介绍");
  ```

**注意：载入节点分两步，先==用new构建==QTreeWidgetItem对象，再用方法==将对象载入==**

​		(载入的一定是**QTreeWidgetItem对象**！！！)

2、**载入**根节点(AddTopLevelItem)和子节点(根节点对象->addChild(子节点对象))

略

完整代码

```c++
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


```



## QTableWidget

1、**设置行数和列数为必要操作！**

```c++
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(11);
```

2、载入单元格数据的方法为：setItem(行号, 列号, 文本)

```c++
 ui->tableWidget->setItem(i,col++, new QTableWidgetItem(nameList[i]));
```

完整代码

```c++
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


```

![image-20220128204640693](C:/Users/Songchujia/AppData/Roaming/Typora/typora-user-images/image-20220128204640693.png)



##  Text&FileOpen读写

![image-20220128232929497](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220128232929497.png)

代码如下

```c++
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


```

知识点待整理

## Qpainter绘图与展示

分号删除，shift + 左括号 tab

painterEvent自动调用

ellipse椭圆

```c++
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


```

知识点待整理

## 文件系统TreeWeidget遍历

学习中





## CSV联动TableWidget





## 数据库表单展示（类似于datagridview in C#）





## 教务系统爬虫完善





## 我的项目——微博超话数据分析

分析：评论区情感分析，评论区用户年龄、性别、地区、活跃程度分析……

### python

爬虫：**通用 + 聚集**

文件读写csv

python **连接 SQLserver读写数据库或者以csv为媒介读写csv**

python**数据分析可视化**

-  pandas dataframe matplotlib——基本数据的分析与展示

- 能不能用python在**地图绘制**，展示区域数据情况

  类似于：![image-20220127230447366](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220127230447366.png)

### Qt

表单数据展示：**文件管理系统**打开csv/采用datagridview类似的方法

**Qt连接Sqlserver**展示分析情况



### git版本控制与Python项目管理



### 试试endNote写报告？



## 图形学？



## 计算器



## 扫雷



## 五子棋



## 常用控件



## 消息机制和事件



## 对象树

**在创建QObject对象时，可以提供一个其父对象，我们创建的这个QObject对象会自动添加到其父对象的children()列表。**

**当父对象析构的时候，这个列表中的所有对象也会被析构。（注意，这里的父对象并不是继承意义上的父类！）**

## 信号槽



## lamda



## Qwindow



## QDialog



## 资源文件



```C++public:
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
    
    
        ui->setupUi(this);
    //初始化鼠标位置和菜单项变量
    menu = 0;
    count = 0;
    startX = 0;
    startY = 0;
    endX = 0;
    endY = 0;
    
    
    
     QPainter painter(this);
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
    
    
    menu = 1;
```



