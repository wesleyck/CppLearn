#include <iostream>
#include <thread>
#include <mutex>
#include <stdexcept>
#include<condition_variable>
#include <unistd.h>
#include <deque>
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

int main() {
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

// 1. 演示10个线程
std::mutex mtx;

void print_even(int x) {
  if (x % 2 == 0) {
    std::cout << x << " is even" << std::endl;
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
    std::cout << "[exception caught]\n";
    // std::cerr << e.what() << '\n';
  }
}

int main100() {
  std::thread thread[10];
  for (int i = 0; i < 10; i++) {
    thread[i] = std::thread(print_thread_id, i + 1);
  }
  for (auto &th : thread) {
    th.join();
  }
  return 0;
}

// 2. 多线程
std::deque<int> q;
std::mutex mu;
std::condition_variable cond;
int count = 0;

void func1000() {
  while (true) {
    {
      std::unique_lock<std::mutex> locker(mu);
      std::cout << "func1 lock" << std::endl;
      q.push_back(count ++);
      // locker.unlock();
      cond.notify_one();
    }
    sleep(1);
  }
}

void func20() {
  while (true) {
    {
      std::unique_lock<std::mutex> locker(mu);
      std::cout << "func2 lock" << std::endl;
      std::cout << "func2 wait into" << std::endl;
      cond.wait(locker, [](){return !q.empty();});
      std::cout << "func2 wait leave" << std::endl;
      auto data = q.back();
      q.pop_back();
      std::cout << "thread 2 get value from thread " << data << std::endl;
    }
  }
}

int main10() {
  std::thread t1(func1);
  std::thread t2(func20);
  t1.join();
  t2.join();
  return 0;
}
