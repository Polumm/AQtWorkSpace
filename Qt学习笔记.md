## 新建项目

1、.pro = .sln

2、路径命名严格，请按照英文规范来

![image-20220127090625126](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220127090625126.png)

待学习：帮助文档的使用（done）

![image-20220127091732477](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220127091732477.png)

3、新增界面（建议添加**Qt设计器界面类**）

![image-20220127180021709](https://cdn.jsdelivr.net/gh/Polumm/PicGoo/image-20220127180021709.png)



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



## Qpainter绘图与展示



## 文件系统与文件读写



## 常用控件



## 消息机制和事件



## 对象树



## 信号槽



## lamda



## Qwindow



## QDialog



## 资源文件

















