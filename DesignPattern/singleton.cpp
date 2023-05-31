#include <mutex>
#include <atomic>

// v1 没有释放、线程不安全
#if 0
class Singleton {
public:
    static Singleton * GetInstance() {
        if (_instance == nullptr) {
            _instance = new Singleton();
        }
        return _instance;
   }
private:
    Singleton() {}; //构造
    ~Singleton() {};
    Singleton(const Singleton &) = delete; //拷⻉构造
    Singleton& operator=(const Singleton&) = delete; //拷贝赋值构造
    Singleton(Singleton &&) = delete; //移动构造
    Singleton& operator=(Singleton &&) = delete; //移动拷贝构造
    static Singleton * _instance;
};
Singleton* Singleton::_instance = nullptr; // 静态成员需要初始化
#endif


// v2 还可以用智能指针来解决释放问题，但还有线程不安全，
#if 0
class Singleton {
public:
    static Singleton * GetInstance() {
        if (_instance == nullptr) {
            _instance = new Singleton();
            atexit(Destructor);
       }
        return _instance;
   }
private:
    static void Destructor() {
        if (nullptr != _instance) { //
            delete _instance;
            _instance = nullptr;
       }
   }
    Singleton(){}; //构造
    ~Singleton(){};
    Singleton(const Singleton &) = delete; //拷⻉构造
    Singleton& operator=(const Singleton&) = delete;//拷贝赋值构造
    Singleton(Singleton &&) = delete;//移动构造
    Singleton& operator=(Singleton &&) = delete;//移动拷贝构造
    static Singleton * _instance;
};
Singleton* Singleton::_instance = nullptr;//静态成员需要初始化
#endif

// v3 懒汉模式 lazy load
#if 0
class Singleton { 
public:
    static Singleton * GetInstance() {
        // std::lock_guard<std::mutex> std::lock(_mutex); // 3.1 切换线程
        if (_instance == nullptr) {
            std::lock_guard<std::mutex> lock(_mutex); // 3.2
            if (_instance == nullptr) {
                _instance = new Singleton();
                // new分为下面3个步骤，可能完成1 3 就出去了，此时另一个线程return回去并未构造完，会有问题
                // 1. 分配内存
                // 2. 调用构造函数
                // 3. 返回指针
                // 多线程环境下 cpu reorder操作
                atexit(Destructor);
           }
       }
        return _instance;
   }
private:
    static void Destructor() {
        if (nullptr != _instance) {
            delete _instance;
            _instance = nullptr;
       }
   }
    Singleton(){}; //构造
    ~Singleton(){};
    Singleton(const Singleton &) = delete; //拷⻉构造
    Singleton& operator=(const Singleton&) = delete;//拷贝赋值构造
    Singleton(Singleton &&) = delete;//移动构造
    Singleton& operator=(Singleton &&) = delete;//移动拷贝构造
    static Singleton * _instance;
    static std::mutex _mutex;
};

Singleton* Singleton::_instance = nullptr;//静态成员需要初始化
std::mutex Singleton::_mutex; //互斥锁初始化

#endif

// v4 懒汉最终版——volitile 到此解决多线程问题，懒汉式，需要的时候再创建，
#if 1
class Singleton {
public:
    static Singleton * GetInstance() {
        // 原子变量解决原子性、可见性、执行序
        Singleton* tmp = _instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);//获取内存屏障
        if (tmp == nullptr) {
            std::lock_guard<std::mutex>lock(_mutex);
            tmp = _instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new Singleton;
                std::atomic_thread_fence(std::memory_order_release);//释放内存屏障
                _instance.store(tmp, std::memory_order_relaxed);
                atexit(Destructor);
           }
       }
        return tmp;
   }
private:
    static void Destructor() {
        Singleton* tmp = _instance.load(std::memory_order_relaxed);
        if (nullptr != tmp) {
            delete tmp;
       }
   }
    Singleton(){}; //构造
    ~Singleton(){};
    Singleton(const Singleton &) = delete; //拷⻉构造
    Singleton& operator=(const Singleton&) = delete;//拷贝赋值构造
    Singleton(Singleton &&) = delete;//移动构造
    Singleton& operator=(Singleton &&) = delete;//移动拷贝构造
    static std::atomic<Singleton*> _instance;
    static std::mutex _mutex;
};
std::atomic<Singleton*> Singleton::_instance;//静态成员需要初始化
std::mutex Singleton::_mutex; //互斥锁初始化
// g++ Singleton.cpp -o singleton -std=c++11

#endif 

// c++11 magic static 特性：如果当变量在初始化的时候，并发同时进⼊声明语句，并发线程将会阻塞等待初始化结束。
// c++ effective
#if 0
class Singleton
{
public:
    static Singleton& GetInstance() {
        static Singleton instance;
        return instance;
   }
private:
    Singleton(){}; //构造
    ~Singleton(){};
    Singleton(const Singleton &) = delete; //拷⻉构造
    Singleton& operator=(const Singleton&) = delete;//拷贝赋值构造
    Singleton(Singleton &&) = delete;//移动构造
    Singleton& operator=(Singleton &&) = delete;//移动拷贝构造
};
// 继承 Singleton
// g++ Singleton.cpp -o singleton -std=c++11

#endif

// v6 饿汉式，在程序启动就创建
/*该版本具备 版本5 所有优点：
1. 利⽤静态局部变量特性，延迟加载；
2. 利⽤静态局部变量特性，系统⾃动回收内存，⾃动调⽤析构函数；
3. 静态局部变量初始化时，没有 new   操作带来的cpu指令 reorder操作；
4. c++11 静态局部变量初始化时，具备线程安全；
*/
#if 0 
template<typename T>
class Singleton {
public:
    static T& GetInstance() {
        static T instance; // 这⾥要初始化DesignPattern，需要调⽤DesignPattern 构造函数，同时会调⽤⽗类的构造函数。
        return instance;
   }
protected:
    virtual ~Singleton() {}
    Singleton() {} // protected修饰构造函数，才能让别⼈继承
private:
    Singleton(const Singleton &) = delete; //拷⻉构造
    Singleton& operator=(const Singleton&) =delete;//拷贝赋值构造
    Singleton(Singleton &&) = delete;//移动构造
    Singleton& operator=(Singleton &&) =delete;//移动拷贝构造
};
class DesignPattern : public Singleton<DesignPattern> {
    friend class Singleton<DesignPattern>; //friend 能让Singleton<T> 访问到 DesignPattern构造函数
private:
    DesignPattern() {}
    ~DesignPattern() {}
};
#endif 
