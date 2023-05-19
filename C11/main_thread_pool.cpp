#include "Ho_threadpool.h"
#include <iostream>

void func1() {
  std::cout << "======func1 test======" << std::endl;
}

void func2(int a) {
  std::cout <<  "\n======func2 test======" << std::endl;
  std::cout << "a = " << a << std::endl;
}

void func3(int b, std::string s) {
  std::cout <<  "\n======func3 test======" << std::endl;
  std::cout << "b = " << b << "string  = " << s << std::endl;
}

int func1_future(int a) {
  std::cout << "a = " << a << std::endl;
  return a;
}

std::string func2_future(int a, std::string b) {
  std::cout << "a = " << a <<  ", string = " << b << std::endl;
  return b;
}

void test1() {
  ZERO_ThreadPool threadpool;
  threadpool.init(3);
  threadpool.start();
  threadpool.exec(func1);
  threadpool.exec(func2, 5);
  threadpool.exec(func3, 6, "kun");
  threadpool.waitForAllDone();
  threadpool.stop();

}

void test2() {
  ZERO_ThreadPool threadpool;
  threadpool.init(2);
  threadpool.start(); // 启动线程池
  // 假如要执行的任务
  std::future<decltype (func1_future(0))> result1 = threadpool.exec(func1_future, 10);
  std::future<string> result2 = threadpool.exec(func2_future, 20, "kun");
  // auto result2 = threadpool.exec(func2_future, 20, "darren");
  std::cout << "result1: " << result1.get() << std::endl;
  std::cout << "result2: " << result2.get() << std::endl;
  threadpool.waitForAllDone();
  threadpool.stop();

}

int main() {
  // test1();
  test2();

  std::cout << "Hello World!" << std::endl;

  return 0;
}