# Effective c++ note learning

## 允许零个或一个对象

阻止某个class产出对象的最简单方法就是将构造函数private私有化。

```c++
class Count
{
private:
	Count();
    Count(const Count&);
}
```

如此每个人都无法构造对象，如果想设计只有一个对象，例如声明了一个打印机class，想要表示只有一台打印机存在的情况。

```c++
class PrintJob;
class Printer
{
public:
    void submitJob(const PrintJob& job);
    void reset();
    void performSelfTest();
    
    friend Printer& thePrinter();

private:
    Printer();
    Printer(const Printer&);
};

Printer& thePrinter()
{
    static Printer p;
    return p;
}
```

> 将构造函数的属性设为private，可以压制对象的诞生；
>
> 全局函数thePrinter被声明为class的一个friend，致使不受private限制，可以新建对象。
>
> thePrinter内含一个static对象，表示只有一个Printer对象会被产生出来。

```c++
class PrintJob
{
public:
    PrintJob(const string& whatToPrint);
};

string buffer;
thePrinter().reset();
thePrinter().submitJob(buffer);
```

有两个地方需要关注，第一，形成唯一一个Printer对象是**函数中的static对象**，而非**class中的static对象**。

> class拥有一个static对象的意思是：即使从未被使用到，他也会被构造（及析构）。
>
> 相反函数拥有一个static对象的意思是：此对象在函数第一次被调用时才产生。

使用function而非class的另一个关键是：他的**初始化时机无法确切知晓**。

thePrinter未被声明成inline。

inline的意思？

> 概念上，它意味着编译器应该将每一个调用动作以函数本身去掉，但对于non-member functions，他还意味着这个函数有内部连接。
>
> >函数如果带有内部连接，可能会在程序中被复制，对于local static对象，你的程序可能会拥有多份static对象的副本。**千万不要产生内含local static对象的inline non-member function。**（此问题可能已被编译器消除）

```c++
class Printer {
public:
    class TooManyObjects{};
    Printer();
    ~Printer();

private:
    static size_t numObjects;
    Printer(const Printer& rhs);
};
```

更换思路，利用numObjects对象来追踪记录目前存储多少个Printer对象。这个数值将在constructor中累加，在destructor中累减，如果外界企图构造太多Printer对象，就抛出一个类型为TooManyObjects的exception。

```c++
size_t Printer::numObjects = 0;
Printer::Printer() {
    if ( numObjects >= 1)
    {
        throw TooManyObjects();
    }
    ++numObjects;
}

Printer::~Printer() {
    --numObjects;
}
```

## 不同的对象构造状态

这种策略也存在问题。假设此时有一台彩色打印机，其class与一般打印机的class有许多共同点，所以通过继承机制。

```c++
class ColorPrinter : public Printer {
    
};

Printer p;
ColorPrinter p;
```

此时会提示我们请求打印机数量太多，派生类调用了基类的构造函数，导致数量不够。

或者当其他对象内含Printer对象时，类似问题再度发生。

```c++
class CPFMachine {
private:
    Printer p;
    FaxMachine f;
};

CPFMachine c1;
```

采用第一种方式可以很容易达成该约束，**因为构造函数为private，不能够用来当作base class，也无法内嵌于其他对象内**。