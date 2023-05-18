#include <iostream>
#include <thread>
#include <mutex>
#include <stdexcept>
#include<condition_variable>
#include <unistd.h>
#include <deque>
#include <string.h>
#include <queue>
#include <functional>
#include "Ho_Thread.h" // 封装好的线程
 
using namespace std;


// 1. 线程流转，流转后，之前的无法使用
void threadFun(int &a) // 引用传递
{
  std::cout << "this is thread fun !" << std::endl;
  std::cout <<" a = "<< (a += 10) << std::endl;
}
int main1()
{
  int x = 10;
  std::thread t1(threadFun, std::ref(x));
  std::cout << "got 1 \n" << std::endl; 
  // std::this_thread::sleep_for(std::chrono::seconds(2));
  std::thread t2(std::move(t1)); // t1 线程失去所有权
  std::cout << "got 2 \n" << std::endl; 
  std::thread t3;
  std::cout << "got 3 \n" << std::endl; 
  t3 = std::move(t2); // t2 线程失去所有权
  // t1.join(); // ？
  std::cout << "got 4 \n" << std::endl; 
  t3.join();
  std::cout << "got 5 \n" << std::endl; 
  std::cout<<"Main End "<<"x = "<<x<<std::endl;
  return 0;
}



// 2. thread用法演示
// 1 传入0个值
void func1()
{
  cout << "func1 into" << endl;
}
// 2 传入2个值
void func2(int a, int b)
{
  cout << "func2 a + b = " << a+b << endl;
}

void func2_1(int a, int b)
{
  cout << "func2_1 a + b = " << a+b << endl;
}
// 多态
int func2_1(string a, string b)
{
  cout << "func2_1 a + b = " << a << b<< endl;
  return 0;
}

// 3 传入引用
void func3(int &c) // 引用传递
{
  cout << "func3 c = " << &c << endl;
  c += 10;
}

class A
{
public:
//    4. 传入类函数
  void func4(int a)
  {
//        std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "thread:" << name_<< ", fun4 a = " << a << endl;

  }
  int func4(string str)
  {
//        std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "thread:" << name_<< ", fun4 str = " << str << endl;
    return 0;

  }
  void setName(string name) {
      name_ = name;
  }
  void displayName() {
      cout << "this:"  << this << ", name:" << name_ << endl;
  }
  void play()
  {
      std::cout<<"play call!"<<std::endl;
  }
private:
    string name_;
};

//5. detach
void func5()
{
    cout << "func5 into sleep " <<  endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "func5 leave " <<  endl;
}

// 6. move
void func6()
{
  cout << "this is func6 !" <<endl;
}

int main2() {
  // 1 传0参数
  // cout << "----------func1 --------- " << endl;
  // std::thread t1(func1);
  // this_thread::sleep_for(chrono::seconds(2));
  // void (*myfunc)() = &func1;
  // cout << "func1 name " << myfunc << endl;
  // cout << "func1 addr " << &myfunc << endl;
  // t1.join();

  // // 2 传2参数
  // cout << "----------func2 --------- " << endl;
  // int a = 10;
  // int b = 15;
  // std::thread t2(func2, a, b);
  // void (*myfunc1)(int, int) = &func2;
  // cout << "func2 name " << myfunc1 << endl;
  // cout << "func2 addr " << &myfunc1 << endl;
  // t2.join();
  // // 函数重载
  // std::thread t3((void(*)(int, int))func2_1, a, b);
  // std::thread t4((int(*)(std::string, std::string))func2_1, "Hello", "World");
  // t3.join();
  // t4.join();

  // 3 引用传参
  // int c = 5;
  // cout << "----------func3 --------- " << endl;
  // std::thread t5(func3, std::ref(c));
  // t5.join();
  // cout << "c after thread is " << c << endl;

  // 4 传入类参数
  // cout << "----------func4 --------- " << endl;
  // A *ptr = new A();
  // ptr->setName("kun");
  // std::thread t6(&A::displayName, ptr);
  // t6.join();
  // // 类函数重载
  // A* ptr1 = new A();
  // ptr1->setName("kun1");
  // std::thread t7((void(A::*)(int))&A::func4, ptr1, 1); // 重载
  // std::thread t8((int(A::*)(string))&A::func4, ptr1, "hello"); // 重载
  // t7.join();
  // t8.join();

  // 5 detach 
  cout << "----------func5 --------- " << endl;
  std::thread t9(&func5);
  t9.detach();
  cout << "pid: " << t9.get_id() << endl; // 脱离管理，无法获取
  cout << "joinable: " << t9.joinable() << endl;
  // std::this_thread::sleep_for(std::chrono::seconds(2)); // 如果不休眠，主线程会直接退出，导致detach的线程也会退出；
  
  // 6 move 
  cout << "----------func6 --------- " << endl;
  std::thread t10_1(&func6);
  std::thread t10_2(std::move(t10_1));
  t10_2.join();

  return 0;
}



// 3. thread封装
class A_thr : public Ho_Thread {
public:
  void run () {
    while (running_)
    {
      std::cout << " A_thr id:  " << CURRENT_THREADID << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    std::cout << "------Leave A----" << std::endl;
  }
};

class B_thr : public Ho_Thread {
public:
  void run () {
    while (running_)
    {
      std::cout << " B_thr id:  " << CURRENT_THREADID << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "------Leave B----" << std::endl;
  }
};

int main3() {
  {
    A_thr a;
    a.start();
    B_thr b;
    b.start();
    sleep(2);
    b.stop();
    b.join();
    a.join();
    // a.stop();
    // b.stop();
  }
  std::cout << "Hello World!" << std::endl;
  return 0;
}



// 4. lock 演示
std::mutex mtx;

void print_even(int x) {
  if (x % 2 == 0) {
    // std::cout << x << " is even" << std::endl;
    printf("%d is even\n", x);
  } else {
    throw (std::logic_error("not even"));
  }
}

void print_thread_id(int id) {
  try
  {
    std::unique_lock<std::mutex> lc(mtx);
    // std::lock_guard<std::mutex> lc(mtx);
    print_even(id);
  }
  catch(const std::exception& e)
  {
    printf("[exception caught] %d\n", id);
    // std::cout << "[exception caught] " << id << std::endl;;
    // std::cerr << e.what() << '\n';
  }
}

int main4() {
  std::thread thread[10];
  for (int i = 0; i < 10; i++) {
    thread[i] = std::thread(print_thread_id, i + 1);
  }
  for (auto &th : thread) {
    th.join();
  }
  return 0;
}



// 5. Mutex 不加锁情况下，++运算非原子操作，多线程会同时读写有问题，可能取的是中间变量
volatile int counter(0);
void increse_10k() {
  for (int i = 0; i < 10000; i++) {
    // 当前没上锁才叠加，显然不对
    // if (mtx.try_lock()) { 
    //   counter ++;
    //   mtx.unlock();
    // }
    // 加锁即可解决
    // mtx.lock();
    // counter ++;
    // mtx.unlock();

    // std::lock_guard<std::mutex> lck(mtx);
    counter++; // 出现数据竞争无法解决
  }
}

int main5() {
  std::thread threads[10];
  for (int i = 0; i < 10; i++) {
    threads[i] = std::thread(increse_10k);
  }
  for (auto &thread : threads) {
    thread.join();
  }
  std::cout << "successful increase of counter " << counter << std::endl;
  return 0;
}



// 6. 死锁, 可以使用递归互斥量解决，但是不推荐使用它
struct Complex
{
    // std::mutex mutex;
    std::recursive_mutex mutex;
    int i;

    Complex() : i(0){}

    void mul(int x)
    {
        // std::lock_guard<std::mutex> lock(mutex);
        std::lock_guard<std::recursive_mutex> lock(mutex);
        i *= x;
    }

    void div(int x)
    {
        // std::lock_guard<std::mutex> lock(mutex);
        std::lock_guard<std::recursive_mutex> lock(mutex);

        i /= x;
    }

    void both(int x, int y)
    {
        //lock_guard 构造函数加锁， 析构函数释放锁
        // std::lock_guard<std::mutex> lock(mutex);

        std::lock_guard<std::recursive_mutex> lock(mutex);

        mul(x); // 若mutex互斥量则获取不了锁
        div(y);
    }

    void init()
    {
        //lock_guard 构造函数加锁， 析构函数释放锁
        // std::lock_guard<std::mutex> lock(mutex);
        std::lock_guard<std::recursive_mutex> lock(mutex);

        sub_init();
    }
    void sub_init()
    {
        // std::lock_guard<std::mutex> lock(mutex);
        std::lock_guard<std::recursive_mutex> lock(mutex);

    }
};

int main6() {
  Complex complex;
  complex.both(2, 3);
  // complex.init();
  std::cout << "main finish \n";
  return 0;
}

// 7. unique_lock 集合条件变量
std::deque<int> q;
std::mutex mu;
std::condition_variable cond;
int count = 0;

void func_mux1() {
  while (true) {
    {
      std::unique_lock<std::mutex> locker(mu); // 换成lock_guard也可以
      std::cout << "func1 lock" << std::endl;
      q.push_back(count ++);
      // locker.unlock();  // notify之后没有括号出去的话，必须等作用域结束, wait才会获取到锁
      cond.notify_one();
    }
    sleep(1);
  }
}

void func_mux2() {
  while (true) {
    {
      // 这里只能用unique_lock,wait只接收unique
      std::unique_lock<std::mutex> locker(mu);
      std::cout << "func2 lock" << std::endl;
      std::cout << "func2 wait into" << std::endl;
      cond.wait(locker, [](){return !q.empty();}); // 表示 true才唤醒，即非空唤醒，空则sleep，释放锁
      std::cout << "func2 wait leave" << std::endl;
      auto data = q.back();
      q.pop_back();
      std::cout << "thread 2 get value from thread " << data << std::endl;
    }
  }
}

int main7() {
  std::thread t1(func_mux1);
  std::thread t2(func_mux2);
  t1.join();
  t2.join();
  return 0;
}




// 8. u 
class Buffer
{
public:
    Buffer(const char *str) {
        size_t size = strlen(str);
        ptr_ = new char[size + 1];
        memcpy(ptr_, str, size);
        ptr_[size] = '\0';
        cout << "Buffer Constructor, ptr:" << ptr_  << endl;
    }

    const char *get() {
        return ptr_;
    }
    ~Buffer() {
        cout << "Buffer Destructor, ptr:" << ptr_  << endl;
        if(ptr_) {
            delete [] ptr_;
        }
    }


private:
    char* ptr_ = nullptr;
    size_t size = 0;
};

// 封装一个线程
class Thread
{
public:
    Thread(string name) : name_(name) {
         cout << "Thread Constructor" << endl;
    }
    virtual ~Thread()
    {
        cout << "Thread Destructor" << endl;
        if(!IsTerminate()) {
            this->Stop();
        }

    }

    void Start() {
        std::thread thr(std::bind(&Thread::Run, this));
        thread_ = std::move(thr);  // mov语义
    }
    std::thread::id GetId() {
        return thread_.get_id();
    }
    void Stop() {
        { // 注意这里加 {}的作用， 是为了能释放mutex_的占用
            unique_lock<mutex> lock(mutex_);
            terminate_ = true;
            condition_.notify_one();
        }

        if(thread_.joinable()) {
            thread_.join();
        }
    }
    bool IsTerminate() {
        return terminate_;
    }

    virtual void Run() = 0;

protected:
    string name_;
    bool terminate_ = false;
    std::thread thread_;
    mutex mutex_;
    condition_variable condition_;
};

class MyThread :
    public Thread
{
public:
    MyThread(string name) : Thread(name) {
        cout << "Thread name: " << name_ << std::endl;
    }
    virtual ~MyThread() {

    }

    void Push(shared_ptr<Buffer> buf) {
        unique_lock<mutex> lock(mutex_);
        buf_queue_.push(buf);
        condition_.notify_one();
    }

    virtual void Run() override{
        while (!IsTerminate())
        {
           // 处理具体的业务
            shared_ptr<Buffer> buf;
            bool ok = get(buf);
            if(ok) {
                cout << name_ << " handle " << buf->get() << endl; // 处理具体事情，这里只是模拟不同的业务处理同样的数据
            }
        }
    }

    bool get(shared_ptr<Buffer>& buf)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (buf_queue_.empty())
        {
//            cout <<" wait into" << endl;
            // 它会去检查谓词对象的bool返回值是否是true, 如果是true才真正唤醒，否则继续block
            condition_.wait(lock, [this] {
//                cout <<" wait check terminate_:" << terminate_ << ", queue:" << !buf_queue_.empty() << endl;
                return terminate_ || !buf_queue_.empty();
            });
//            cout <<" wait leave" << endl;
        }

        if (terminate_)
            return false;

        if (!buf_queue_.empty())
        {
            buf = std::move(buf_queue_.front());  // 使用了移动语义
            buf_queue_.pop();
            return true;
        }

        return false;
    }

private:
    queue<shared_ptr<Buffer>> buf_queue_;
};

int main()
{
  {
    MyThread thread_a("Thread A");
    MyThread thread_b("Thread B");

    shared_ptr<Buffer> buf1 = make_shared<Buffer>("01234");
    shared_ptr<Buffer> buf2 = make_shared<Buffer>("56789");
    shared_ptr<Buffer> buf3 = make_shared<Buffer>("abcde");
  //  逻辑上来说，a b 交叉打印完全有可能，不过本机由于线程调度可能先a处理完再b，但是单线程内部，由于条件变量结合FIFO必须顺序打印即可 0  5 a大的顺序不变
    thread_a.Start();
    thread_b.Start();
    thread_a.Push(buf1);
    thread_b.Push(buf1);
    thread_a.Push(buf2);
    thread_b.Push(buf2);
    thread_a.Push(buf3);
    thread_b.Push(buf3);
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << "sleep_for end" << endl;
//        thread_a.Push(buf1);
//        thread_b.Push(buf1);
//        this_thread::sleep_for(std::chrono::seconds(1));
    thread_a.Stop();
    thread_b.Stop();
  }
    cout << "main end" << endl;
    return 0;
}

