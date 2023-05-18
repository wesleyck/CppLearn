#include <iostream>
#include <memory>
#include <string>
#include <string.h>
#include <vector>
#include "time_interval.h"


// 1. 左右值用法
void lr_change(int &&right_value) {
  right_value = 8;
}

int main1() {
  std::cout << "====== Test1 ======" << std::endl;
  int a = 5;
  int &left_ref = a;
  int &&right_ref = std::move(a); // move转为右值
  std::cout << "a: " << a << std::endl;
  std::cout << "left_ref: " << left_ref << std::endl;
  std::cout << "right_ref: " << right_ref << std::endl;

  std::cout << "====== Test2 ======" << std::endl;
  int &&right_ref1 = 6; // 右值
  right_ref1 = 7;

  // 报错，6为右值，左值引用无法指向，只有const int & 可以
  // int &left_ref2 = 6; 

  std::cout << "====== Test3 ======" << std::endl;
  int temp = 5;
  int &&right_ref2 = std::move(temp);
  right_ref2 = 6;
  std::cout << "temp is " << temp  << std::endl;
  std::cout << "right_ref2 is " << right_ref2  << std::endl;

  std::cout << "====== Test4 ======" << std::endl;
  int four = 4;
  int &left_ref_four = a;
  int &&right_ref_four = std::move(four);

  // 下面三个都编译不过，都在等号左边，都是左值，后面两个引用本身是左值
  // lr_change(four);
  // lr_change(left_ref_four);
  // lr_change(right_ref_four);

  // move 强制将左值转成右值
  lr_change(std::move(four));
  lr_change(std::move(left_ref_four));
  lr_change(std::move(right_ref_four));
  // 地址一样
  std::cout << &a << ' ';
  std::cout << &left_ref_four << ' ';
  std::cout << &right_ref_four << ' ';

  return 0;
}



// 2. 深浅拷贝 move
class A {
public:
  A() : m_ptr(new int(0)){
    std::cout << "constructor A" << std::endl;
  }
  // 不写的话，默认浅拷贝，会double free

  // 深拷贝，解决double free，但是会分配内存，某些大的临时对象拷贝浪费时空
  A(const A& a) : m_ptr(new int(*a.m_ptr)) {
    std::cout << "copy constructor A" << std::endl;
  }

  // 同时存在多构造函数，优先右值引用
  A(A&& a) : m_ptr(a.m_ptr) {
    a.m_ptr = nullptr;
    std::cout << "move copy constructor A" << std::endl;
  }
  ~A() {
    std::cout << "destructor A, mptr: " << m_ptr << std::endl;
    if (m_ptr) {
      delete m_ptr;
    }
  }

private:
  int *m_ptr;
};

A GetA(bool flag) {
  A a1;
  A a2;
  std::cout << "ready return " << std::endl;
  if (flag) {
    return a1;
  } else {
    return a2;
  }
}
int main2() {
  {
    printf("Get before\n");
    A a = GetA(false);
    printf("Get after\n");
  }
  std::cout << "main finish" << std::endl;
  return 0;
}



// 3. move实操
class MyString {
private:
  char* m_data;
  int m_len;
  void CopyData(const char *s) {
    m_data = new char[m_len + 1];
    memcpy(m_data, s, m_len);
    m_data[m_len] = '\0';
  }
public:
  MyString() {
    m_data = nullptr;
    m_len = 0;
    std::cout << "Default Constructor is called! m_data: null " << std::endl;
  }
  MyString(const char* s) {
    m_len = strlen(s);
    CopyData(s);
    std::cout << "Default Constructor is called! const char*: " << m_data << std::endl;
  }
  MyString(const std::string s) {
    m_len = s.size();
    CopyData(s.c_str());
    std::cout << "Default Constructor is called! m_data: " << m_data << std::endl;
  }
  MyString(const MyString& mystr) {
    m_len = mystr.m_len;
    CopyData(mystr.m_data);
    std::cout << "Copy Constructor is called! source: " << &mystr << std::endl;
  }
  MyString& operator=(const MyString& mystr){
    if (this != &mystr) {
      m_len = mystr.m_len;
      CopyData(mystr.m_data);
    }
    std::cout << "Copy Assigment is called! source: " << &mystr << std::endl;
    return *this;
  }
  MyString(MyString&& mystr) {
    m_len = mystr.m_len;
    m_data = mystr.m_data;
    mystr.m_len = 0;
    mystr.m_data = nullptr;
    std::cout << "Move Constructor is called! source: " << &mystr << std::endl;
  }
  MyString& operator=(MyString&& mystr){
    if (this != &mystr) {
      m_len = mystr.m_len;
      m_data = mystr.m_data;
      mystr.m_len = 0;
      mystr.m_data = nullptr;
    }
    std::cout << "Move Assigment is called! source: " << &mystr << std::endl;
    return *this;
  }

  virtual ~MyString() {
    std::cout << "Destructor MyString" << std::endl;
    if (m_data) free(m_data);
  }
};

int main3() {
  MyString a;
  a = MyString("Hello"); // 移动赋值
  MyString b = a; // 拷贝构造
  MyString c = std::move(a); // 移动构造
  std::vector<MyString> vec;
  vec.push_back(MyString("world")); // 移动构造
  return 0;
}



// 4. 完美转发 原来是左或右就转发过去
template<class T>
void Print(T& t) {
  std::cout << "left  value: " << t << std::endl;
}

template<class T>
void Print(T&& t) {
  std::cout << "right value: " << t << std::endl;
} 

template<class T>
void func(T&& t) {
  Print(t);
  Print(std::move(t));
  Print(std::forward<T>(t));
  // std::cout << "left  value: " << t << std::endl;
} 

class B {
public:
  B() : m_data(nullptr), m_len(0) {}
  B (const int* data, const int size) {
    m_len = size;
    m_data = new int[size];
    if (m_data) {
      printf("B 默认构造函数 m_data: %p\n", m_data);
      // sizeof ()对于new出来的取的是指针本身的地址，而对于数组名取得是数组所有元素的所占大小
      // printf("sizeof(arr) %lu , arr[0] size %lu\n", sizeof(data), sizeof(data[0]));
      memcpy(m_data, data, size * sizeof(int));
    }
    
  }
  // 拷贝构造实现深拷贝
  B (const B& b) {
    m_len = b.m_len;
    if (b.m_data) {
      printf("B 拷贝构造函数 m_data: %p\n", m_data);
      if (m_data) {
        delete[] m_data;
        printf("delete[] m_data\n");
      }
      m_data = new int[m_len];
      printf("sizeof(int)*m_len: %lu\nsizeof(sizeof(int) * m_len): %lu\n", sizeof(int) * m_len, sizeof(sizeof(int) * m_len));
      memcpy(m_data, b.m_data, sizeof(sizeof(int) * m_len));
    } else {
      if (m_data) {
        delete[] m_data;
      }
      m_data = nullptr;
    }
  }
  // 右值引用移动构造函数
  B (B&& b) {
    m_data = nullptr;
    m_len = b.m_len;
    if (b.m_data) {
      printf("B 移动构造函数 m_data: %p\n", m_data);
      m_data = std::move(b.m_data); // 移动语义
      b.m_data = nullptr;
      // memcpy(m_data, b.m_data, m_len);
    }
  }
  virtual ~B() {
    if (m_data) {
      delete[] m_data;
      m_len = 0;
    }
  }
  void deleterptr() {
    if (m_data) {
      std::cout << "now delete Addr: " << m_data << std::endl;
      delete[] m_data;
      m_data = nullptr;
      m_len = 0;
    }
  }

  int* m_data = nullptr;
  int m_len = 0;
};

int main4() {
  /*
  std::cout << "====== fun(1) ======" << std::endl;
  func(5);

  std::cout << "====== fun(x) ======" << std::endl;
  int x = 10;
  int y = 20;
  func(x);

  std::cout << "====== fun(x) ======" << std::endl;
  func(std::forward<int>(x));
  std::cout << "====== fun(&x) ======" << std::endl;
  func(std::forward<int&>(x));
  std::cout << "====== fun(&&x) ======" << std::endl;
  func(std::forward<int&&>(x));
  */

  int arr[] = {1, 2, 3};
  B b1(arr, sizeof(arr) / sizeof(arr[0]));
  std::cout << "m_data in b1 Addr: 0x " << b1.m_data << std::endl;
  B b2(b1);
  std::cout << "m_data in b2 Addr: 0x " << b2.m_data << std::endl;

  b2.deleterptr();
  // 完美转发
  B b3(std::forward<B>(b1));
  // B b3(std::move(b1)); 也可以
  std::cout << "m_data in b3 Addr: 0x" << b3.m_data << std::endl;
  b3.deleterptr();

  std::vector<int> vect{1, 2, 3, 4, 5};
  std::cout << "before move vect size: " << vect.size() << std::endl;
  std::vector<int> vect1 = std::move(vect);
  std::cout << "after move vect size: " << vect.size() << std::endl;
  std::cout << "new vect1 size: " << vect1.size() << std::endl;
  return 0;
}


// 5.emplace_back string
int main5() {
  std::vector<std::string> v;
  int count = 1000000;
  v.reserve(count);
  {
    TIME_INTERVAL_SCOPE("push_back string :");
    for (int i = 0; i < count; i++) {
      std::string temp("test");
      v.push_back(temp);
    }
  }
  v.clear();

  {
    TIME_INTERVAL_SCOPE("push_back move (string):");
    for (int i = 0; i < count; i++) {
      std::string temp("test");
      v.push_back(std::move(temp));
    }
  }
  v.clear();

  {
    TIME_INTERVAL_SCOPE("push_back forawrd (string):");
    for (int i = 0; i < count; i++) {
      std::string temp("test");
      v.push_back(std::forward<std::string>(temp));
    }
  }
  v.clear();

  {
    TIME_INTERVAL_SCOPE("push_back(string):");
    for (int i = 0; i < count; i++) {
      v.push_back(std::string ("test"));
    }
  }
  v.clear();

  {
    TIME_INTERVAL_SCOPE("push_back(string):");
    for (int i = 0; i < count; i++) {
      v.push_back("test");
    }
  }
  v.clear();

  {
    TIME_INTERVAL_SCOPE("emplace_back(string):");
    for (int i = 0; i < count; i++) {
      v.emplace_back("test"); // 一次构造，不调用拷贝构造函数
    }
  }
  return 0;
}


class Foo {
public:
  Foo(std::string name) : m_name(name) {
    std::cout << "Default construction" << std::endl;
  }
  Foo(const Foo& foo) {
    std::cout << "Copy construction" << std::endl;
    m_name = foo.m_name;
  }
  Foo(Foo&& foo) {
    std::cout << "Move copy construction" << std::endl;
    m_name = std::move(foo.m_name);
  }
  ~Foo() {
    std::cout << "Default destruction" << std::endl;
  }
private:
  std::string m_name;
};
// 6.emplace_back T
int main() {

  std::vector<Foo> v;
  int count = 100000;
  v.reserve(count);
  {
      TIME_INTERVAL_SCOPE("push_back T:");
      Foo temp("test");
      v.push_back(temp);// push_back(const T&)，参数是左值引用
      //打印结果：
      //constructor
      //copy constructor
  }
  std::cout << " ---------------------\n" << std::endl;
  v.clear();
  {
      TIME_INTERVAL_SCOPE("push_back move(T):");
      Foo temp("test");
      v.push_back(std::move(temp));// push_back(T &&), 参数是右值引用
      //打印结果：
      //constructor
      //move constructor
  }
  std::cout << " ---------------------\n" << std::endl;
  v.clear();
  {
      TIME_INTERVAL_SCOPE("push_back(T&&):");
      v.push_back(Foo("test"));// push_back(T &&), 参数是右值引用
      //打印结果：
      //constructor
      //move constructor
  }
  std::cout << " ---------------------\n" << std::endl;
  v.clear();
  {
      std::string temp = "test";
      TIME_INTERVAL_SCOPE("push_back(string):");
      v.push_back(temp);// push_back(T &&), 参数是右值引用
      //打印结果：
      //constructor
      //move constructor
  }
  std::cout << " ---------------------\n" << std::endl;
  v.clear();
  {
      // std::string temp = "test";
      TIME_INTERVAL_SCOPE("emplace_back(T):");
      // Foo temp("test");
      // v.emplace_back(temp);// 只有一次构造函数，不调用拷贝构造函数，速度最快
      //打印结果：
      //constructor
      v.emplace_back(Foo("test"));
  }



  return 0;
}