## 要求（或禁止）对象产生与heap之中

### 要求对象产生与heap之中

将构造函数和析构函数声明为private，可以限制对象构造在heap外，但是太过严苛，将析构函数置于private，就可以起到相同的效果。

```c++
class UPNumber {
public:
    UPNumber();
    UPNumber(int initValue);
    UPNumber(double initValue);
    UPNumber(const UPNumber& initValue);
    void destroy() const { delete this; }
private:
    ~UPNumber();
};

UPNumber n; //编译器提示has private dtor
UPNumber * p1 = new UPNumber();
delete p1; //错误！企图调用private dtor
p1->destroy(); //correct
```

限制dtor和ctor也会存在问题，他限制了继承和内含。继承和内含都无法通过编译，因为调用了声明为private的ctor或dtor。

解决方式可以通过，将dtor函数声明为protected，此时，**继承问题得以解决**，对于内含问题，可以通过定义指针指向该对象解决。

```c++
class Asset
{
public:
    Asset(int initValue);
    ~Asset();
private:
    UPNumber* value;
};

Asset::Asset(int initValue) : value(new UPNumber(initValue))
{
}

Asset::~Asset() {
    value->destroy();
}
```

### 判断某个对象是否位于heap内

```c++
bool onHeap(const void* address)
{
    char onTheStack;
    return address < &onTheStack;
}
```

> 程序的地址空间以线性序列组织而成，其中stack（栈）高地址往低地址成长，heap（堆）由低地址往高地址成长。但是，此方法存在一定问题，即static objects的地址位于Heap之下，这就导致了一个问题，无法判断static对象和heap对象都是True。

```c++
void allocateSomeObjects()
{
    char* pc = new char;
    bool res = onHeap(pc);
    std::cout << res << std::endl; //True
    char c;
    res = onHeap(&c);
    std::cout << res << std::endl; //False
    static char sc;
    res = onHeap(&sc);
    std::cout << res << std::endl; //True
}
```
