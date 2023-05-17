#include <iostream>
#include <memory>
#include <string>
#include <string.h>
#include <vector>


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
      printf("B 默认构造函数 m_data: %p", m_data);
      memcpy(m_data, data, sizeof(size * sizeof(int)));
    }
    
  }
  // 拷贝构造实现深拷贝
  B (const B& b) {
    m_len = b.m_len;
    if (b.m_data) {
      printf("B 拷贝构造函数 m_data: %p", m_data);
      if (m_data) {
        delete[] m_data;
        printf("delete[] m_data\n");
      }
      m_data = new int[m_len];
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
      printf("B 移动构造函数 m_data: %p", m_data);
      m_data = std::move(b.m_data); // 移动语义
      b.m_data = nullptr;
      // memcpy(m_data, b.m_data, m_len);
    }
  }
  virtual ~B() {
    if (m_data) {
      delete m_data;
      m_len = 0;
    }
  }
  void deleterptr() {
    if (m_data) {
      delete[] m_data;
      m_data = nullptr;
    }
  }
private:
  int* m_data;
  int m_len;
};

int main() {
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

  return 0;
}