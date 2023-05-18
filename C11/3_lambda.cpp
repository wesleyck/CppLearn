#include <iostream>
#include <memory>

using namespace std;

// ->返回类型
void test1() {
  std::cout << "test1 " << std::endl;
  auto Add = [](int a, int b) -> int {
    return a + b;
  };
  std::cout << Add(1, 2) << std::endl;
}

// 一般能自动推理出来返回类型
void test2() {
  std::cout << "test2 " << std::endl;
  auto Add = [](int a, int b) {return a + b;};
  std::cout << Add(1, 2) << std::endl; // 3
  
}
// 拷贝只是当时的快照，而引用为到时实际查值
void test3() {
  std::cout << "test3 " << std::endl;
  int a = 2;
  int b = 3;
  int c = 4;
  auto Add = [a, b, &c](int d, int e) {
    std::cout << "b = " << b <<  std::endl;
    std::cout << "c = " << c << std:: endl;
    return d + e;
  };
  b = 6;
  c = 6;
  std::cout << Add(5, 5) << std::endl;
}

// 拷贝不能赋值
void test4() {
  std::cout << "test4" << std::endl;
  int c = 12;
  auto Add = [c](int a, int b) {
    // c = a; // 会报错，copy
    return c;
  };
  std::cout << Add(1, 2) << std::endl;
}

// 引用获取最新
void test5() {
  std::cout << "test5" << std::endl;
  int c = 12;
  int d = 0;
  auto Add = [&c, &d](int a, int b) {
    c = a;
    // d = 3;
    std::cout << "d = " << d << std::endl;
    return c;
  };
  d = 10;
  std::cout << Add(1, 2) << std::endl;
}

void test6() {

  std::cout << "test6" << std::endl;
  int c = 12;
  int d = 30;
  auto Add = [&c, &d](int &a, int &b)->int {
      a = 11;
      b = 12;
      std::cout << "d = " << d  << std::endl;
      return a + b;
  };
  d = 20;
  std::cout << Add(c, d) << std::endl;
  std::cout << "c = " << c  << std::endl;
  std::cout << "d = " << d  << std::endl;
  
}
  
void test7()
{
    std::cout << "test7" << std::endl;
    int c = 12;
    int d = 30;

    // 把捕获列表的&改成=再测试
    // [] 空值，不能使用外面的变量
    // [=] 传值，lambda外部的变量都能使用
    // [&] 传引用值，lambda外部的变量都能使用
    auto Add = [&](int a, int b)->int {
        c = a; // 编译对的
        cout << "d = " << d  << endl;
        return c;
    };
    d = 20;
    std::cout << Add(1, 2) << std::endl;
    std::cout << "c:" << c<< std::endl;
}


// 表达式捕获 C++14之后支持捕获右值，允许捕获的成员用任意的表达式进行初始化
void test8()
{
  cout << "test8" << endl;
  auto important = std::make_unique<int>(1);

  auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
      return x + y + v1 + (*v2);
  };

  std::cout << add(3,4) << std::endl;
}

void test9()
{
    cout << "test9" << endl;
    auto add = [](auto x, auto y) {
        return x+y;
    };

    std::cout <<  add(1, 2) << std::endl;
    std::cout <<  add(1.1, 1.2) << std::endl;
}

//混合使用隐式捕获和显式捕获

//要求捕获列表中第一个元素必须是隐式捕获（&或=）
//混合使用时，若隐式捕获采用 引用捕获 &，则显式捕获的变量必须采用值捕获的方式
//若隐式捕获采用值捕获 = ，则显式捕获的变量必须采用引用捕获的方式，即变量名前加&
void test10()
{
    cout << "test10" << endl;
    int c = 12;
    int d = 30;
    int e = 30;
    // &, d, e 代表除了d其他都是引用传递
    // =, &c 代表除了d其他都是引用传递
//    auto Add = [&, d, e](int a, int b)->int {
    auto Add = [=, &c](int a, int b)->int {
        c = a; // 编译对的
        cout << "d = " << d  << ", e:" << e << endl;
        return c;
    };
    d = 20;
    std::cout << Add(1, 2) << std::endl;
    std::cout << "c:" << c<< std::endl;
}

void test11() {
    cout << "test11" << endl;
    int v = 5;
    // 值捕获方式，使用mutable修饰，可以改变捕获的变量值
    auto ff = [v]() mutable {return ++v;};

    v = 0;
    auto j = ff();  // j为6
    cout << "j:" << j << endl;
}

void test12() {
    cout << "test12" << endl;
    int v = 5;
    // 采用引用捕获方式，可以直接修改变量值
    auto ff = [&v] {return ++v;};

    v = 0;
    auto j = ff();  // v引用已修改，j为1
    cout << "j:" << j << endl;
}


int main() {
  // test1();
  // test2();
  // test3();
  // test4();
  // test5();
  // test6();
  test12();

  return 0;
}
